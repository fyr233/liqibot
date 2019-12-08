import requests
import re
import sys

language=sys.argv[1]
filename=sys.argv[2]

url='https://m.runoob.com/api/compile.php'
filepath='othercode/'+filename

file=open(filepath,'r')
code=file.read()
file.close()
#print(code)

if language=='php' :
    referer='https://c.runoob.com/compile/1'
    langu='3'
    fileext='php'
elif language=='python2' :
    referer='https://c.runoob.com/compile/6'
    langu='0'
    fileext='py'
elif language=='java' :
    referer='https://c.runoob.com/compile/10'
    langu='8'
    fileext='java'
elif language=='cpp' :
    referer='https://c.runoob.com/compile/12'
    langu='7'
    fileext='cpp'
elif language=='ruby' :
    referer='https://c.runoob.com/compile/13'
    langu='1'
    fileext='rb'
elif language=='csharp' :
    referer='https://c.runoob.com/compile/14'
    langu='10'
    fileext='cs'
elif language=='scala' :
    referer='https://c.runoob.com/compile/15'
    langu='5'
    fileext='scala'
elif language=='objectivec' :
    referer='https://c.runoob.com/compile/16'
    langu='12'
    fileext='oc'
elif language=='perl' :
    referer='https://c.runoob.com/compile/17'
    langu='14'
    fileext='pl'
elif language=='bash' :
    referer='https://c.runoob.com/compile/18'
    langu='11'
    fileext='sh'
elif language=='vb' :
    referer='https://c.runoob.com/compile/19'
    langu='9'
    fileext='vb'
elif language=='swift' :
    referer='https://c.runoob.com/compile/20'
    langu='16'
    fileext='swift'
elif language=='go' :
    referer='https://c.runoob.com/compile/21'
    langu='6'
    fileext='go'
elif language=='node.js' :
    referer='https://c.runoob.com/compile/22'
    langu='4'
    fileext='node.js'
elif language=='lua' :
    referer='https://c.runoob.com/compile/66'
    langu='17'
    fileext='lua'
elif language=='pascal' :
    referer='https://c.runoob.com/compile/73'
    langu='18'
    fileext='pas'
elif language=='kotlin' :
    referer='https://c.runoob.com/compile/2960'
    langu='19'
    fileext='kt'

headers={
'Accept': '*/*',
'Accept-Encoding': 'gzip, deflate, br',
'Accept-Language': 'zh-CN,zh;q=0.9',
'Connection': 'keep-alive',
'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
'Host': 'm.runoob.com',
'Origin': 'https://c.runoob.com',
'Referer': referer,
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36',
}

formdata={
'code': code,
'stdin': '',
'language': langu,
'fileext': fileext,
}

r=requests.post(url,headers=headers,data=formdata)
#print(r.text)
result=re.findall('"output":"(.*?)"',r.text,0)
errors=re.findall('"errors":"(.*?)"',r.text,0)
#print(len(errors))
if len(result[0]) :
    print(result[0])
else :
    print(errors[0])