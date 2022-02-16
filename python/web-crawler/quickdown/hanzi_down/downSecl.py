# -*- coding: utf-8 -*- 
# @Time : 2021/5/11 19:33 
# @Author : yx
# @File : downSecl.py

import requests
import os



urlists = {}
with open('urlists.txt', encoding='utf-8') as f:
    while True:
        text_line = f.readline()
        if text_line:
            cate,name, url = text_line.split(':',2)
            urlists[name] = (cate,url.rstrip())
        else:
            break

for name, (cate,url) in urlists.items():
    print(cate,'--',name, '——', url)
    out_path_dir = './categorys/{}'.format(cate)
    if not os.path.exists(out_path_dir):
        os.makedirs(out_path_dir)
    try:
        r = requests.get(url)
        with open(out_path_dir + "/{}.scel".format(name), "wb") as code:
            code.write(r.content)
    except Exception as err:
        print('{}\t的下载失败了！原因是：{}'.format(name, err))
        continue
