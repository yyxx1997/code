# -*- coding: utf-8 -*- 
# @Time : 2021/5/21 16:42 
# @Author : yx
# @File : checkinwiki.py

import requests
from lxml import etree

input_file='./output/allNoun.txt'
output_file='./output/checkedNoun.txt'
base_url = 'https://www.hk.jwchfzu.top/wiki/{}'
sessions = requests.session()
sessions.headers['User-Agent'] = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.131 Safari/537.36'

def checkWikiDict(sessions,word):
    url = base_url.format(word)
    print(url)
    resp = sessions.get(url)
    eroot = etree.HTML(resp.text)
    element = eroot.xpath('//*[@id="noarticletext"]/p/b/text()')
    if element and  ('目前还没有与上述标题相同' in element[0]):
        return False
    return True

if __name__ == '__main__':
    with open(input_file, 'r', encoding='utf-8') as f:
        content = f.readlines()
    result=[]
    for i in content:
        wait_check=i.replace('\n', '')
        try:
            if checkWikiDict(sessions,wait_check):
                result.append(wait_check)
        except:
            continue
    print(result)
    with open(output_file,'w',encoding='utf-8') as f:
        for w in result:
            f.write(w+'\n')

