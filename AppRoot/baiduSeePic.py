# -*-coding:utf-8-*-  
import requests  
import os  
import json  
import re  
import sys
from contextlib import closing

filepath=os.getcwd() 
#imagepath=sys.argv[1]
rawtext=sys.argv[1]

#下载图片
#print(re.findall(r'\[CQ:image,file=(.*?png)\]',rawtext)[0])
imagename=re.findall(r'\[CQ:image,file=(.*?)\]',rawtext)[0]+'.cqimg'
#print(imagename)
cqimgfile=open(filepath+'/data/image/'+imagename,'r')
lines=cqimgfile.readlines()[5]
#print(lines)
#print(re.findall(r'url=(.*?)\n',lines))
image_url=re.findall(r'url=(.*?)\n',lines)[0]
#print(image_url)
cqimgfile.close()

isjpg=re.findall('jpg',imagename)
ispng=re.findall('png',imagename)
isgif=re.findall('gif',imagename)

if len(isgif)!=0:
    pic=u"/data/image/baiduseepic.gif" 
elif len(ispng)!=0:
    pic=u"/data/image/baiduseepic.png"
else:
    pic=u"/data/image/baiduseepic.jpg"

response = requests.get(image_url, stream = True)
with closing(requests.get(image_url, stream = True)) as response:
    # 这里打开一个空的文件，相当于创建一个空的txt文件,wb表示写文件
    with open(filepath+pic, 'wb') as imagefile:
        # 每128个流遍历一次
        for data in response.iter_content(128):
            # 把流写入到文件
            imagefile.write(data)



#识图
headers={  
'User-Agent':'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36',  
}  
source='http://image.baidu.com'  
#得到vs  
vs_url=source+'/?fr=shitu'  
vs_page=requests.get(vs_url,headers=headers).text  
vs_id=re.findall('window.vsid = "(.*?)"',vs_page)[0]  
  
url='/pcdutu/a_upload?fr=html5&target=pcSearchImage&needJson=true'  

#files={'file':(pic,open(pic,'rb'),'image/jpeg'),'pos':(None,'upload'),'uptype':(None,'upload_pc'),'fm':(None,'home')}  
files={'file':(pic,open(filepath+pic,'rb'),'image/jpeg'),'pos':(None,'upload'),'uptype':(None,'upload_pc'),'fm':(None,'home')}  
#files={'file':("https://gchat.qpic.cn/gchatpic_new/1091484024/570216513-2962576202-0BB49CC1F5D210632B46BFDBC8E066A6/0?vuin=2799314467&term=2",'image/jpeg'),'pos':(None,'upload'),'uptype':(None,'upload_pc'),'fm':(None,'home')}  
r=requests.post(source+url,headers=headers,files=files)  
tmp=r.text  
#print(tmp)
tmp_json=json.loads(tmp)  
queryImageUrl=tmp_json['url']  
querySign=tmp_json['querySign']  
simid=tmp_json['simid']  
url2=source+'/pcdutu?queryImageUrl='+queryImageUrl+'&querySign='+querySign+'fm=index&uptype=upload_pc&result=result_camera&vs='+vs_id
#print(url2)
r2=requests.get(url2,headers=headers).text  
#print(r2)
gussword=re.findall("'guessWord': '(.*?)'",r2)[0] 
#imagesource=re.findall(r'"fromURL":".*?html"',r2)
imagesource=re.findall('"fromURL":"(.*?)"',r2)
print('猜测：',end='')
print(gussword)
print('来源：')
for i in imagesource:
    print(i)