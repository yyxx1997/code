# -*- coding: utf-8 -*- 
# @Time : 2021/9/2 11:53 
# @Author : yx
# @File : get_content.py

import requests
from lxml import etree
import re

url = 'http://www.gov.cn/zhengce/content/2020-11/10/content_5560234.htm'
headers = {"User-Agent": "Mozilla/5.0 (Windows NT 6.0 x64;en-US;rv:1.9pre) Gecko/2008072421 Minefield/3.0.2pre"}
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

with open('test.txt', 'w', encoding='utf-8') as f:
    for line in contents:
        if '\n' not in line:
            f.writelines(line+'\n')
        else:
            f.writelines(line)