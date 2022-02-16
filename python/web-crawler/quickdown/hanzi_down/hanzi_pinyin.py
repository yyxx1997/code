# -*- coding: utf-8 -*- 
# @Time : 2021/6/19 10:22 
# @Author : yx
# @File : hanzi_pinyin.py

from bs4 import BeautifulSoup
import requests

headers = {"User-Agent": "Mozilla/5.0 (Windows NT 6.0 x64;en-US;rv:1.9pre) Gecko/2008072421 Minefield/3.0.2pre"}
url_root = 'http://xh.5156edu.com/'
url_fontpage = url_root + 'pinyi.html'
response = requests.get(url_fontpage)
response.encoding = 'gbk'
html = response.text
soup = BeautifulSoup(html, 'html.parser')

tags = soup.find_all('a', class_="fontbox")
pinyin = {}
for tag in tags:
    value = tag.next.strip()
    link = tag.get('href')
    pinyin[value] = link
result = {}
for py,link in pinyin.items():
    url = url_root+link
    print(url)
    response = requests.get(url)
    response.encoding = 'gb18030'
    html = response.text
    soup = BeautifulSoup(html, 'html.parser')
    # title=soup.find('title').next[0]
    # if title=='无':
    #     valid.append(url)
    #     continue
    tags=soup.find_all('a',class_="fontbox")
    words=[]
    for tag in tags:
        value =tag.next
        words.append(value)
    result[py]=words


with open('pinyin.txt','w',encoding='gb18030') as file:
    for title,words in result.items():
        file.write("{}\t{}\n".format(title,''.join(words)))
