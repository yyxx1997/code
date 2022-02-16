# -*- coding: utf-8 -*- 
# @Time : 2021/9/2 11:14 
# @Author : yx
# @File : public_urls.py

import requests
from lxml import etree
import re

base_url = 'http://sousuo.gov.cn/column/30469/{}.htm'
base_url="http://sousuo.gov.cn/column/31421/{}.htm"
base_url="http://sousuo.gov.cn/column/30900/{}.htm"
base_url="http://sousuo.gov.cn/column/40521/{}.htm"
base_url="http://sousuo.gov.cn/column/40403/{}.htm"
pagenum=133
urls = [base_url.format(i) for i in range(pagenum)]
print(urls)
ulists=[]
for url in urls:
    try:
        resp = requests.get(url=url)
        eroot = etree.HTML(resp.text)
        elements = eroot.xpath('/html/body/div[2]/div/div[2]/div[2]/ul/li')
        for ele in elements:
            title = ele.xpath('./h4/a/text()')[0]
            uname= ele.xpath('./h4/a/@href')[0]
            ulists.append((title,uname))
            print(title,uname)
    except:
        continue
with open('serve.txt', 'w', encoding='utf-8') as f:
    for name,url in ulists:
        f.writelines(name+'\t'+url+'\n')
