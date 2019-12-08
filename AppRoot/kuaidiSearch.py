import requests
import re
import sys
import random

kdid = sys.argv[1]
print(sys.argv[1])

url1 = 'https://www.kuaidi100.com/autonumber/autoComNum?resultv2=1&text=' + kdid
#print(url1)

headers1 = {'Accept': 'application/json, text/javascript, */*; q=0.01',
'Accept-Encoding': 'gzip, deflate, br',
'Accept-Language': 'zh-CN,zh;q=0.9',
'Connection': 'keep-alive',
'Content-Length': '0',
'Cookie': 'WWWID=WWW0A8EB7885DF48C91769448191D2F2F54; Hm_lvt_22ea01af58ba2be0fec7c11b25e88e6c=1542169266; Hm_lpvt_22ea01af58ba2be0fec7c11b25e88e6c=1542169266',
'Host': 'www.kuaidi100.com',
'Origin': 'https://www.kuaidi100.com',
'Referer': 'https://www.kuaidi100.com/',
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36',
'X-Requested-With': 'XMLHttpRequest'}

r1 = requests.post(url1, headers = headers1)
#print(r1.text)

kdtype = re.findall('"comCode"\:"(.*?)"', r1.text)
#print(kdtype)

url2 = 'https://www.kuaidi100.com/query?type=' + kdtype[1] + '&postid=' + kdid + '&temp=' + str(random.random())
#print(url2)

headers2 = {'Accept': 'application/json, text/javascript, */*; q=0.01',
'Accept-Encoding': 'gzip, deflate, br',
'Accept-Language': 'zh-CN,zh;q=0.9',
'Connection': 'keep-alive',
'Cookie': 'WWWID=WWW0A8EB7885DF48C91769448191D2F2F54; Hm_lvt_22ea01af58ba2be0fec7c11b25e88e6c=1542169266; Hm_lpvt_22ea01af58ba2be0fec7c11b25e88e6c=1542169266',
'Host': 'www.kuaidi100.com',
'Referer': 'https://www.kuaidi100.com/',
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36',
'X-Requested-With': 'XMLHttpRequest'}

r2 = requests.get(url2, headers = headers2)
#print(r2.text)

kdmessage = re.findall('"message":"(.*?)"', r2.text)
kdftime = re.findall('"ftime":"(.*?)"', r2.text)
kdcontext = re.findall('"context":"(.*?)"', r2.text)

if kdmessage[0] == 'ok' :
    for i in range(len(kdftime)):
        print(kdftime[i])
        print(kdcontext[i])
else :
	print(kdmessage[0])