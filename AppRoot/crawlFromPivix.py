#encoding:UTF-8
import urllib.request
import urllib
import re
import time
import os
import sys

mode=int(sys.argv[1])
amount=int(sys.argv[2])
isr18=int(sys.argv[3])
exportpath=sys.argv[4]
print(mode)
print(amount)
print(exportpath)
print(isr18)

#注意更改cookies
cookies='PHPSESSID=31791391_d98ed06a4f6c9bee5b3ef8cb425b9a62;__gads=ID=2987901f419bba9e:T=1526733951:S=ALNI_MZQixwuE3L4ftrWPpYqZKTFEUdbXw;__utma=235335808.1260876779.1526732760.1526753438.1526824175.6;__utmc=235335808;__utmv=;235335808.|2=login%20ever=yes=1^3=plan=normal=1^5=gender=male=1^6=user_id=31791391=1^9=p_ab_id=1=1^10=p_ab_id_2=9=1^11=lang=zh=1;__utmz=235335808.1526732760.1.1.utmcsr=blog.csdn.net|utmccn=(referral)|utmcmd=referral|utmcct=/h_WuLingFei/article/details/62041986;_ga=GA1.2.1260876779.1526732760;_gid=GA1.2.1243436022.1526732786;a_type=0;b_type=1;c_type=19;device_token=6304444ff490fe445429a2a8bacb7878;login_bc=1;module_orders_mypage=%5B%7B%22name%22%3A%22sketch_live%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22tag_follow%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22recommended_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22showcase%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22everyone_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22following_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22mypixiv_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22fanbox%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22featured_tags%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22contests%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22user_events%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22sensei_courses%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22spotlight%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22booth_follow_items%22%2C%22visible%22%3Atrue%7D%5D;p_ab_id=1;p_ab_id_2=9;tag_view_ranking=0xsDLqCEW6~BU9SQkS-zU~y8GNntYHsi~F_kcrJcD1D~fREG1CeBxV~7srA70_QLo~f3hJPB804M~xZ6jtQjaj9~RTJMXD26Ak~iFcW6hPGPU~hXWLeOE6t9~kym2Z4vnZu~EGefOqA6KB~emNf5ejWtw~P8RilRYqZw~CiSfl_AE0h~KN7uxuR89w~ueeKYaEKwj~MhuNMsFpmN~vxGWQFnciU~TZGb7mWeXE~RokSaRBUGr~bdsHaxGhC9~b0hlLjX6ec~ajUVarCYub~H6lk0ujEdQ~QRGsAC7TD3~w8ffkPoJ_S~_RfiUqtsxe~jH0uD88V6F~Kxau5pnIZ1~1-Y5jOSDux~kqk67x-lhD~gN6l1iwCPS~cLc_d0LDhp~NpsIVvS-GF~4srBJYeR5-~_hSAdpN9rx~LJo91uBPz4~q303ip6Ui5~-FRvO3TDIZ~ZnmOm5LdC3~jPLPUvvEiQ~YuIxJMq4Ls~AauDVIJZFs~NKIsEMOZT5~EyEzlEct2T~Lt-oEicbBr~pYlUxeIoeg~awaHCpDX3f~uW5495Nhg-~b1s-xqez0Y~099gnvyNFT~m5A6MfklNr~eK9vnMvjjT'
'''
函数名:findImgUrl
功能:找到图片地址
传入参数:p站图片页面地址
传出参数:图片地址
'''
def findImgUrl(url):
    try:
        req=urllib.request.Request(url)
        req.add_header('User-Agent','Mozilla/5.0')
        req.add_header('Cookie',cookies)
        res=urllib.request.urlopen(req)
    except:
        print('图片页加载失败')
        return 0
    html=res.read().decode('utf8')
    #print(html)
    #imgUrls=re.findall( r'data-src=".*?" class="original-image"', html, 0)
    imgUrls=re.findall( r'https://i.pximg.net/c/600x600/.*jpg', html, 0)
    #print(len(imgUrls))
    if len(imgUrls)!=1:
            return['imgUrl ERROW']
    for imgUrl in imgUrls:
        #imgUrl=re.sub(r'data-src="',"",imgUrl)
        #imgUrl=re.sub(r'" class="original-image"',"",imgUrl)
        print(imgUrl)
        return imgUrl
'''
函数名:downlownImg
功能:下载图片
传入参数:p站图片地址,图片所在页面地址,文件名(不含文件格式)
传出参数:1成功,0失败
'''   
def downlownImg(imgUrl,imgPageUrl,name):
    try:
        req=urllib.request.Request(imgUrl)
        req.add_header('Referer',imgPageUrl)
        req.add_header('User-Agent','Mozilla/5.0')
        req.add_header('Cookie',cookies)
        res=urllib.request.urlopen(req)
    except:
        print(imgPageUrl)
        print(imgUrl)
        print('ERROR')
        return 0
    postfix=re.findall(r'\.\w{2,4}$',imgUrl,0)
    name=name+postfix[0]
    print(name)
    print("downlownding")
    f=open(name,'wb')
    f.write(res.read())
    f.close()
    return 1
'''
函数名:findIdfromSerch
功能:从搜索中找到id并转化为地址
传入参数:p站搜索地址
传出参数:id地址
'''
def findIdfromSerch(searchUrl):
    try:
        req=urllib.request.Request(searchUrl,headers={'User-Agent':'Mozilla/5.0'})
        res=urllib.request.urlopen(req)
        html=res.read().decode('utf8')
    except:
        print('搜索页打开失败')
        return 0
    #正则匹配
    x=0
    ids = re.findall( r'illust_id=\d{5,12}">', html, 0)
    for id in ids:
        id=re.sub(r'illust_id=',"",id)
        id=re.sub(r'">',"",id)
        id='http://www.pixiv.net/member_illust.php?mode=medium&illust_id='+id
        print(id)
        x=x+1
    print(x)
    return [ids]
'''
函数名:downlodeFromImgpage
功能:从图片网页中下载图片
传入参数:图片网页地址,保存文件路径名(不含后缀名)
传出参数:无
'''
def downlodeFromImgpage(imgPageUrl,fileName):
    imgUrl=findImgUrl(imgPageUrl)
    if(1==downlownImg(imgUrl,imgPageUrl,fileName)):
        print("succees")

'''
函数名:findImgUrlFromRSS
功能:从排行榜抓取图片页面地址
传入参数:p站图片页面地址
传出参数:图片页面地址
'''
def findImgUrlFromRSS(RSSUrl):
    try:
        req=urllib.request.Request(RSSUrl)
        #req=req.encode("utf-8").decode("latin1")
        #req.add_header('User-Agent','Mozilla/5.0')
        req.add_header('Cookie',cookies)
        res=urllib.request.urlopen(req)
        html=res.read().decode('utf8')
    except:
        print("RSS加载出现问题")
        return 0
    imgUrls=re.findall( r'<link>.*?\d{2,8}</link>', html, 0)
    '''
    for imgUrl in imgUrls:
        imgUrl=re.sub(r'<link>',"",imgUrl)
        imgUrl=re.sub(r'</link>',"",imgUrl)
        print(imgUrl)
    ''' 
    #print(html)
    print(len(imgUrls))
    return imgUrls
'''
函数名:getFilePath
功能:输入存储文件路径
传入参数:无
传出参数:存储文件路径
'''
def getFilePath():
    #while(True):
        #print("请输入文件存储路径(c:\example\):")
        #filePath=re.findall( r'^((?:[a-zA-Z]:)?\\(?:[^\\\?\/\*\|<>:"]+\\)*?)$', input(), 0)
        #if(len(filePath)==1):
        #break
        #print("文件路径存储错误,请重新输入")
        #print("例: c:\example\\")
    print(exportpath)
    return exportpath# filePath[0]
'''
函数名:modeChoose
功能:模式选择
传入参数:无
传出参数:rss地址
'''
def modeChoose():
    while(True):
        print("请选择模式(1-6):")
        print("1.本日排行\n2.本周排行\n3.本月排行\n4.原创排行\n5.新人排行\n6.男性向排行\n7.女性向排行\n")
        print(mode)
        #i=input()
        #filePath=re.findall( r'^[1-7]$', i, 0)
        #if(len(filePath)==1):
        break
        #print("模式输入错误,请重新输入")
    address=('daily','weekly','monthly','original','rookie','male','female')
    while(True):
        print("请选择数量(1-5):")
        print("1.10\n2.20\n3.30\n4.40\n5.50\n")
        print(amount)
        #j=input()
        #filePath=re.findall( r'^[1-5]$', j, 0)
        #if(len(filePath)==1):
        break
        #print("数量输入错误,请重新输入")
    if(isr18):
        rssUrl='http://rakuen.thec.me/PixivRss/'+address[mode-1]+'_r18'+'-'+str(amount)+'0'
    else:
        rssUrl='http://rakuen.thec.me/PixivRss/'+address[mode-1]+'-'+str(amount)+'0'
    #rssUrl='https://www.pixiv.net/ranking.php?mode='+address[int(i)-1]+'_r18'
    print(rssUrl)
    return rssUrl


if(cookies=='请更改此处'):
    print("请更改cookies")
    os._exit()
rssUrl=modeChoose()
#print(rssUrl)
filePith=getFilePath()
imgUrls=findImgUrlFromRSS(rssUrl)
i=1;
if(os.path.exists(filePith)==False):
    try:
        os.makedirs(filePith)
    except:
        print("文件夹创建失败")
        os._exit()
for imgUrl in imgUrls:
    if(isr18):
        fileName=filePith+'pixivimage'+str(i)+'r18'
    else:
        fileName=filePith+'pixivimage'+str(i)
    imgUrl=re.sub(r'<link>',"",imgUrl)
    imgUrl=re.sub(r'</link>',"",imgUrl)
    print(i)
    print(imgUrl)
    downlodeFromImgpage(imgUrl,fileName)
    i=i+1;
    time.sleep(3)
print('end')
