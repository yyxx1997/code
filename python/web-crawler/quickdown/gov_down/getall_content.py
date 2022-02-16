# -*- coding: utf-8 -*- 
# @Time : 2021/9/2 12:40 
# @Author : yx
# @File : getall_content.py

import requests
from lxml import etree


headers = {"User-Agent": "Mozilla/5.0 (Windows NT 6.0 x64;en-US;rv:1.9pre) Gecko/2008072421 Minefield/3.0.2pre"}

ulists=[]
with open('补充.txt','r',encoding='utf8') as f:
    while True:
        content= f.readline()
        if not content:
            break
        ulists.append(tuple(content.replace('\n','').split('\t')))

print(ulists)

for title,url in ulists[::-1]:
    try:
        print(url)
        resp = requests.get(url=url,headers=headers)
        resp.encoding='utf-8'
        eroot = etree.HTML(resp.text)
        elements = eroot.xpath('//*[@id="UCAP-CONTENT"]/p')
        contents=[]
        for ele in elements:
            span=ele.xpath('./span/text()')
            p=ele.xpath('text()')
            contents.extend(p+span)
        print(len(contents),contents)
        title=title.replace('"','')
        with open('./补充/{}.txt'.format(title), 'w', encoding='utf-8') as f:
            for line in contents:
                if '\n' not in line:
                    f.writelines(line+'\n')
                else:
                    f.writelines(line)
    except Exception as err:
        with open('errorlog.txt','a') as f:
            f.write(str(err))