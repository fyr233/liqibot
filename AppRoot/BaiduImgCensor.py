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
censor_result = censor_client.antiPorn(downloadImg(imgurl))

print(censor_result)
if 'result_fine' in censor_result:
    for each in censor_result['result_fine']:
        #print('type', each['type'], 'prob', each['probability'])
        if each['class_name']=='一般色情' and each['probability']>0.9:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='卡通色情' and each['probability']>0.55:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='SM' and each['probability']>0.65:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='艺术品色情' and each['probability']>0.9:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='儿童裸露' and each['probability']>0.9:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='低俗' and each['probability']>0.85:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='性玩具' and each['probability']>0.7:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='女性性感' and each['probability']>0.85:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='卡通女性性感' and each['probability']>0.65:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='男性性感' and each['probability']>0.95:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='自然男性裸露' and each['probability']>0.95:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='亲密行为' and each['probability']>0.90:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='卡通亲密行为' and each['probability']>0.65:
            print('色图！', end='')
            saveImg(imgurl)
            break
        elif each['class_name']=='特 殊类' and each['probability']>0.95:
            print('色图！', end='')
            saveImg(imgurl)
            break
