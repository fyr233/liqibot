import requests
import re
import sys

language=sys.argv[1]
filename=sys.argv[2]

filepath='othercode/'+filename

file=open(filepath,'r')
code=file.read()
file.close()
#print(code)
mutiltry=False;

url='https://run.w3cschool.cn/runcode'

if language=='php' :
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=php'
    langu='php'
elif language=='java' :
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=java'
    langu='java'
elif language=='cpp' :
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=cpp'
    langu='cpp'
elif language=='ruby' :
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=ruby'
    langu='ruby'
elif language=='python2' :
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=python'
    langu='python'
elif language=='perl' :
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=perl'
    langu='perl'
elif language=='objectivec' :
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=objectivec'
    langu='objectivec'
    mutiltry=True
elif language=='csharp' :
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=csharp'
    langu='csharp'
    mutiltry=True
elif language=='assembly' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=assembly'
    langu='assembly'
    mutiltry=True
elif language=='ats' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=ats'
    langu='ats'
    mutiltry=True
elif language=='bash' :
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=bash'
    langu='bash'
    mutiltry=True
elif language=='clojure' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=clojure'
    langu='clojure'
    mutiltry=True
elif language=='coffeescript' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=coffeescript'
    langu='coffeescript'
    mutiltry=True
elif language=='crystal' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=crystal'
    langu='crystal'
    mutiltry=True
elif language=='d' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=d'
    langu='d'
    mutiltry=True
elif language=='elixir' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=elixir'
    langu='elixir'
    mutiltry=True
elif language=='elm' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=elm'
    langu='elm'
    mutiltry=True
elif language=='erlang' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=erlang'
    langu='erlang'
    mutiltry=True
elif language=='fsharp' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=fsharp'
    langu='fsharp'
    mutiltry=True
elif language=='go' :
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=go'
    langu='go'
elif language=='groovy' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=groovy'
    langu='groovy'
    mutiltry=True
elif language=='haskell' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=haskell'
    langu='haskell'
    mutiltry=True
elif language=='idris' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=idris'
    langu='idris'
    mutiltry=True
elif language=='julia' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=julia'
    langu='julia'
    mutiltry=True
elif language=='kotlin' :
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=kotlin'
    langu='kotlin'
    mutiltry=True
elif language=='lua' :
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=lua'
    langu='lua'
elif language=='nim' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=nim'
    langu='nim'
    mutiltry=True
elif language=='ocaml' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=ocaml'
    langu='ocaml'
    mutiltry=True
elif language=='perl6' :#新增/
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=perl6'
    langu='perl6'
elif language=='rust' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=rust'
    langu='rust'
    mutiltry=True
elif language=='scala' :
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=scala'
    langu='scala'
    mutiltry=True
elif language=='swift' :
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=swift'
    langu='swift'
    mutiltry=True
elif language=='typescript' :#新增/
    url='https://www.w3cschool.cn/tryrun/mutiltry'
    referer='https://www.w3cschool.cn/tryrun/runcode?lang=typescript'
    langu='typescript'
    mutiltry=True


headers={
'Accept': 'application/json, text/javascript, */*; q=0.01',
'Accept-Encoding': 'gzip, deflate, br',
'Accept-Language': 'zh-CN,zh;q=0.9',
'Connection': 'keep-alive',
'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
'Host': 'www.w3cschool.cn',
'Origin': 'https://www.w3cschool.cn',
'Referer': referer,
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36',
'X-Requested-With': 'XMLHttpRequest',
}

formdata={
'lang': langu,
'language': langu,
'code': code,
'classname':'',
}
if mutiltry :
    formdata={
    'mode': langu,
    'content': code,
    }

r=requests.post(url,headers=headers,data=formdata)
#print(' ')
#print(r.text)
result=re.findall('"stdout":"(.*?)"',r.text,0)
errors=re.findall('"error":"(.*?)"',r.text,0)
#print(len(errors))
if not mutiltry :
    print(r.text)
else :
    if len(result[0]) :
        print(result[0])
    else :
        print(errors[0])