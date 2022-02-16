# -*- coding: utf-8 -*- 
# @Time : 2021/5/11 18:18 
# @Author : yx
# @File : getUrls.py

import requests
from lxml import etree
import re

base_url = 'https://pinyin.sogou.com/dict/cate/index/{0}/default/{1}'
max_category_number = 403
check=re.compile(r'\“(.*)\”')
for catenum in range(1, max_category_number + 1):
    url = base_url.format(catenum, 1)
    print(url)
    firstresp = requests.get(url=url)
    firsteroot = etree.HTML(firstresp.text)
    try:
        epage = firsteroot.xpath('//*[@id="dict_page_list"]/ul/li')[-2]
        epagenum = epage.xpath('./span/a/text()')[0]
        category_elem=firsteroot.xpath('//*[@id="dict_detail_list"]/div[1]/div[1]')[0]
        category_txt=category_elem.xpath('text()')[0]
        catename=check.findall(category_txt)[0]
    except Exception as err:
        continue
    for pagenum in range(2, int(epagenum) + 1):
        url = base_url.format(catenum, pagenum)
        print(url)
        resp = requests.get(url=url)
        eroot = etree.HTML(resp.text)
        element = eroot.xpath('//*[@id="dict_detail_list"]/div')
        elements = eroot.xpath('//*[@id="dict_detail_list"]/div/div[1]/div/a')
        elements2 = eroot.xpath('//*[@id="dict_detail_list"]/div/div[2]/div[2]/a')
        for ele in element:
            name = ele.xpath('./div[1]/div/a/text()')
            dic_url = ele.xpath('./div[2]/div[2]/a/@href')
            if name and dic_url:
                txt_line = catename + ':' + name[0] + ':' + dic_url[0] + '\n'
                with open('urlists.txt'.format(catename), 'a', encoding='utf-8') as f:
                    f.writelines(txt_line)
