import requests
import sys

#输入格式
#python jsclient.py new 12345
#python jsclient.py del 12345
#python jsclient.py eval 12345 1+2

url = 'http://localhost:1960/'

if sys.argv[1]=='eval':
    roomid = sys.argv[2]
    expr = ''
    for each in sys.argv[3:]:
        expr = expr + each + ' '
    expr = expr
    r = requests.post(url + 'eval', data={'roomid':roomid, 'expr':expr})
    print(r.text, end='')
elif sys.argv[1]=='new':
    roomid = sys.argv[2]
    r = requests.post(url + 'new', data={'roomid':roomid})
    print(r.text, end='')
elif sys.argv[1]=='del':
    roomid = sys.argv[2]
    r = requests.post(url + 'close', data={'roomid':roomid})
    print(r.text, end='')
