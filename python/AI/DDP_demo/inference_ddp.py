import torch
from torch.utils.data import Dataset, DataLoader, DistributedSampler
import torch.distributed as dist
from tqdm import tqdm
from transformers import BartTokenizer
from model import BartOutline2Story
from utils import load_data
import argparse
from transformers import logging
import re
import json

# 设置transformers模块的日志等级，减少不必要的警告，对训练过程无影响，请忽略
logging.set_verbosity_error()


class BartDataset(Dataset):
    def __init__(self, tokenizer, dataset, max_len=512):
        self.dataset = dataset
        self.data_size = len(dataset)
        self.tokenizer = tokenizer
        self.max_len = max_len
        self.ignore_index = -100

    def __len__(self):
        return self.data_size

    def __getitem__(self, index):
        return self.dataset[index]

    def add_padding_data(self, inputs):
        if len(inputs) < self.max_len:
            pad = [self.tokenizer.pad_token_id] * (self.max_len - len(inputs))
            inputs += pad
        else:
            inputs = inputs[:self.max_len]
        return inputs

    def add_ignored_data(self, inputs):
        if len(inputs) < self.max_len:
            pad = [self.ignore_index] * (self.max_len - len(inputs))
            inputs += pad
        else:
            inputs = inputs[:self.max_len]
        return inputs

    def coffate_fn(self, examples):
        all_inputs = {}
        inputs, dec_inputs, labels = [], [], []
        for outlines, story in examples:
            input = self.tokenizer.mask_token.join(outlines)
            dec_input = self.tokenizer.eos_token + story
            label = story + self.tokenizer.eos_token
            input_ids = self.tokenizer.encode(input)
            input_ids = self.add_padding_data(input_ids)
            dec_input_ids = self.tokenizer.encode(dec_input)
            dec_input_ids = self.add_padding_data(dec_input_ids)
            label_ids = self.tokenizer.encode(label)
            label_ids = self.add_ignored_data(label_ids)

            inputs.append(input_ids)
            dec_inputs.append(dec_input_ids)
            labels.append(label_ids)

        all_inputs['input_ids'] = torch.tensor(inputs)
        all_inputs['decoder_input_ids'] = torch.tensor(dec_inputs)
        all_inputs['labels'] = torch.tensor(labels)
        all_inputs['attention_mask'] = all_inputs['input_ids'].ne(
            self.tokenizer.pad_token_id).float()
        all_inputs['decoder_attention_mask'] = all_inputs[
            'decoder_input_ids'].ne(self.tokenizer.pad_token_id).float()
        return all_inputs, examples


parser = argparse.ArgumentParser()
parser.add_argument('--local_rank',
                    default=-1,
                    type=int,
                    help='node rank for distributed training')
parser.add_argument('--n_gpus',
                    default=2,
                    type=int,
                    help='world size for distributed training')
args = parser.parse_args()

local_rank = args.local_rank
n_gpus = args.n_gpus

print(local_rank, n_gpus)

dist.init_process_group(backend="nccl", world_size=n_gpus, rank=local_rank)
torch.cuda.set_device(local_rank)

batch_size = 16
data_path = "test.jsonl"  # 数据所在地址
train_ratio = 0  # 训练集比例

bart_base = 'facebook/bart-base'
tokenizer = BartTokenizer.from_pretrained(bart_base)
model = BartOutline2Story(tokenizer, bart_base)

model.cuda(local_rank)
model = torch.nn.parallel.DistributedDataParallel(model,
                                                  device_ids=[local_rank])

_, test_data = load_data(data_path=data_path, train_ratio=train_ratio)

test_dataset = BartDataset(tokenizer, test_data)

test_sampler = DistributedSampler(test_dataset)

test_dataloader = DataLoader(test_dataset,
                             batch_size=batch_size,
                             collate_fn=test_dataset.coffate_fn,
                             sampler=test_sampler)


model.eval()
results = []
for inputs, origin in tqdm(test_dataloader, desc=f"Evaluate:"):

    for k, v in inputs.items():
        inputs[k] = v.cuda(local_rank)

    bart_output = model.module.model.generate(inputs["input_ids"],
                                              max_length=512)
    for pred, ori in zip(bart_output, origin):
        sent = re.sub("<.+?>", "", tokenizer.decode(pred))
        results.append({"story": ori[1], 'outline': ori[0], 'predict': sent})

with open("./eval/infer_ddp_{}.jsonl".format(local_rank), 'w',
          encoding="utf8") as file:
    file.write(json.dumps(results, ensure_ascii=False))
