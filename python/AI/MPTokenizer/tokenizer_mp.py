from transformers import BertTokenizer
from MpUtil import MpUtil,data_generator,mp
import time
tokenizer = None
 
 
def job(line):
    # print(mp.current_process().name)
    return " ".join(tokenizer.convert_ids_to_tokens(tokenizer(line)["input_ids"]))
 
 
def init():
    # 在这里初始化分词器等需要全局使用的变量，通过current_process可以获取当前进程的唯一ID，从而设置环境变量
    global tokenizer
    tokenizer = BertTokenizer.from_pretrained("bert-base-chinese", mirror="tuna")
    print(mp.current_process().name,id(tokenizer))

def tokenize_single(input,output):
    init()
    dataset=data_generator(input)
    with open(output,'w',encoding="utf8") as f:
        for line in dataset:
            f.write(job(line)+'\n')
        
 
if __name__ == '__main__':

    s=time.time()
    tokenize_single('input.txt','out.txt')
    e=time.time()
    print(e-s)

    s=time.time()
    MpUtil()('input.txt', 'out.txt', job, initializer=init,worker=3, initargs=())
    e=time.time()
    print("cost time is ",e-s)