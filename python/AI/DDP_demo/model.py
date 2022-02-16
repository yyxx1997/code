import torch.nn as nn
from transformers import BartForConditionalGeneration


class BartOutline2Story(nn.Module):
    def __init__(self, tokenizer, pretrain_name="bart-base"):
        super(BartOutline2Story, self).__init__()
        self.model = BartForConditionalGeneration.from_pretrained(
            pretrain_name)
        self.tokenizer = tokenizer

    def forward(self, inputs):
        bart_output = self.model(
            input_ids=inputs['input_ids'],
            attention_mask=inputs['attention_mask'],
            decoder_input_ids=inputs['decoder_input_ids'],
            decoder_attention_mask=inputs['decoder_attention_mask'],
            labels=inputs['labels'],
            return_dict=True)
        return bart_output