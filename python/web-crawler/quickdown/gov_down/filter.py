# -*- coding: utf-8 -*- 
# @Time : 2021/9/15 9:54 
# @Author : yx
# @File : filter.py

from lxml import etree
import re
with open('国务院办公厅.html','r',encoding='utf8') as file:
    resp=file.read()

eroot = etree.HTML(resp)

xp='//*[@class="c-result result"]'

results=eroot.xpath(xp)

urlists=[]

for res in results:
    # urlists.append(res.xpath("./@data-log"))
    urlists.append(res.xpath(".//@href"))

words=re.sub(u"\<.*?\>", "",resp)
print(words)
# for i in urlists:
#     print(i[:2])