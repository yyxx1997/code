import json
import torch
import os

def read_json2dict(filepath):
    with open(filepath,'r',encoding="utf8") as file:
        for line in file:
            line=line.strip()
            yield json.loads(line)

def read_json(filepath):
    with open(filepath,'r',encoding="utf8") as file:
        return json.load(file)

def load_data(data_path, train_ratio=0.8):
    all_data = []
    for dct in read_json2dict(data_path):
        story=' '.join(dct['story'])
        title=dct['outline'][0]
        outlines=[]
        for pairs in dct['outline'][1]:
            outlines.extend(pairs)
        all_data.append((outlines,story))
    length = len(all_data)
    train_len = int(length * train_ratio)
    train_data = all_data[:train_len]
    test_data = all_data[train_len:]
    return train_data, test_data

def save_pretrained(model, path):
    # 保存模型，先利用os模块创建文件夹，后利用torch.save()写入模型文件
    os.makedirs(path, exist_ok=True)
    torch.save(model, os.path.join(path, 'model.pth'))

if __name__=="__main__":
    # gen=read_json2dict("/data1/yx/suda/learn_NLP/bart_test/train1000.jsonl")
    # train,test=load_data("/data1/yx/suda/learn_NLP/bart_test/wp_data/train100.jsonl")
    # count=0
    # for i in gen:
    #     print(i)
    #     count+=1
    #     if count>10:
    #         break
    res=read_json('prediction.jsonl')

    pass