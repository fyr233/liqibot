import requests
import re
import sys

ip=sys.argv[1]
url='https://www.ipip.net/ip.html'
da={'ip':ip,}
headers={'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
'Accept-Encoding': 'gzip, deflate, br',
'Accept-Language': 'zh-CN,zh;q=0.9',
'Cache-Control': 'max-age=0',
'Connection': 'keep-alive',
'Content-Length': '16',
'Content-Type': 'application/x-www-form-urlencoded',
'Cookie': '__jsluid=c93f926ff2352732468234d498f8f400; _ga=GA1.2.1946021558.1530039179; LOVEAPP_SESSID=5147fec8034ff7eb0bf3ac95a458a89425ed7de7; Hm_lvt_123ba42b8d6d2f680c91cb43c1e2be64=1538197364,1539880459; Hm_lvt_d7682ab43891c68a00de46e9ce5b76aa=1539880992; Hm_lpvt_d7682ab43891c68a00de46e9ce5b76aa=1539881097; Hm_lpvt_123ba42b8d6d2f680c91cb43c1e2be64=1539881100',
'Host': 'www.ipip.net',
'Origin': 'https://www.ipip.net',
'Referer': 'https://www.ipip.net/ip.html',
'Upgrade-Insecure-Requests': '1',
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'}

r=requests.post(url,headers=headers, data=da)

#position=re.findall(r'<td>地理位置</td>\r\n                    <td style="clear: both">\r\n                        <span style="display: inline-block;text-align: center;width: 720px;float: left;line-height: 46px;height: 46px;">(.*?)</span>',r.text,0)
position=re.findall(r'<span style="display: inline-block;text-align: center;width: 720px;float: left;line-height: 46px;height: 46px;">(.*?)</span>',r.text,0)
earthposition=re.findall(r'<span style="display: inline-block;text-align: center;width: 720px;float: left;line-height: 46px;">(.*)</span></td>',r.text,0)
#relatedinfomation=re.findall(r'相关信息</td>\r\n            <td colspan="6"><span style="margin-left: -200px;">(.*)</span></td>',r.text,0)
operator=re.findall(r'<span style="display: inline-block;text-align: center;width: 720px;float: left;line-height: 46px;">(.*)</span>',r.text,0)

print('ip:'+ip)
print(position[0])
print('经纬度:',earthposition[1])
print('运营商:',operator[0])
