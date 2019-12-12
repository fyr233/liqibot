from aip import AipImageCensor
#from aip import AipImageClassify
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

censor_APP_ID = '15708523'
censor_API_KEY = '6USQY453ZVSjxYYej1F195IZ'
censor_SECRET_KEY = 'r0rtrpRj8eHRnkPCfEhjOPRh2eO997Uv'

#classify_APP_ID = '17981247'
#classify_API_KEY = '3HuleW8fwIPymQcRM1DNhigp'
#classify_SECRET_KEY = 'LcClAOmKwGSIXR2st8ishMXUPXkiLaaI'

censor_client = AipImageCensor(censor_APP_ID, censor_API_KEY, censor_SECRET_KEY)
censor_result = censor_client.imageCensorUserDefined(imgurl)

print(censor_result)
if 'data' in censor_result:
    for each in censor_result['data']:
        #print('type', each['type'], 'prob', each['probability'])
        if each['type']==1 and each['msg']=='存在一般色情不合规' and each['probability']>0.9:
            saveImg(imgurl)
            print('色图！', end='')
            break
        elif each['type']==1 and each['msg']=='存在卡通色情不合规' and each['probability']>0.5:
            saveImg(imgurl)
            print('色图！', end='')
            break
        elif each['type']==1 and each['msg']=='存在卡通女性性感不合规' and each['probability']>0.4:
            saveImg(imgurl)
            print('色图！', end='')
            break
        elif each['type']==1 and each['msg']=='存在女性性感不合规' and each['probability']>0.85:
            saveImg(imgurl)
            print('色图！', end='')
            break
        if each['type']==2 and each['probability']>0.9:#性感
            saveImg(imgurl)
            print('色图！', end='')
            break
