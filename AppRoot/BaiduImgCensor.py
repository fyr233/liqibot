from aip import AipImageCensor
import sys
import requests

imgurl = sys.argv[1]
imgname = sys.argv[2]#后缀

def saveImg(url):
    r = requests.get(url)
    with open('data/image/setu/'+ imgname, 'wb') as f:
        f.write(r.content)

def downloadImg(url):
    r = requests.get(url)
    return r.content

APP_ID = '15708523'
API_KEY = '6USQY453ZVSjxYYej1F195IZ'
SECRET_KEY = 'r0rtrpRj8eHRnkPCfEhjOPRh2eO997Uv'

client = AipImageCensor(APP_ID, API_KEY, SECRET_KEY)
result = client.antiPorn(downloadImg(imgurl))
#print(result)
if result['conclusion'] == '色情':
    saveImg(imgurl)
    print('色图！', end='')
