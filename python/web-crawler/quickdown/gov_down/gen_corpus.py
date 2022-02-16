# -*- coding: utf-8 -*- 
# @Time : 2021/9/8 12:09 
# @Author : yx
# @File : gen_corpus.py

import os
import re

regex="[\t\n ]"

def ishan(text):
    # for python 3.x
    # sample: ishan('一') == True, ishan('我&&你') == False
    return all('\u4e00' <= char <= '\u9fff' for char in text)


dirpath='./补充/'
filenames=os.listdir(dirpath)
print(filenames)
corpus=[]
for filename in filenames:
    file=open(dirpath+filename,encoding='utf8')
    while True:
        sent=file.readline()
        if sent:
            sent=re.sub(regex,'',sent)
            sent=sent.replace('\n','')
            sent=sent.strip()
            sent = sent.replace(' ', '')
            sents=sent.split('。')
            for s in sents:
                if len(s)<20:
                    continue
                if ishan(s[-1]):
                    corpus.append(s+'。')
                else:
                    corpus.append(s)
        else:
            break
    file.close()



with open('新加数据.txt','w',encoding='utf8') as f:
    for sent in corpus:
        f.write(sent+'\n')