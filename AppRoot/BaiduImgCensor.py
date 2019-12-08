from aip import AipImageCensor
import sys
import requests

imgurl = sys.argv[1]
imgname = sys.argv[2]#后缀

def saveImg(url):
    r = requests.get(url)
    with open('data/image/setu/'+ imgname, 'wb') as f:
        f.write(r.content)

APP_ID = '15708523'
API_KEY = '6USQY453ZVSjxYYej1F195IZ'
SECRET_KEY = 'r0rtrpRj8eHRnkPCfEhjOPRh2eO997Uv'

client = AipImageCensor(APP_ID, API_KEY, SECRET_KEY)
result = client.imageCensorUserDefined(imgurl)

if 'data' in result:
    for each in result['data']:
        if each['type']==1 and each['probability']>0.8:
            saveImg(imgurl)
            print('色图！', end='')
            break
        if each['type']==2 and each['probability']>0.9:
            saveImg(imgurl)
            print('色图！', end='')
            break
