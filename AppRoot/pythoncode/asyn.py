# -*- coding: ANSI -*-
# -*- coding: ANSI -*-
import Msg
import sys
import re
import random
import jieba
import logging

msg = Msg.Msg(sys.argv)

b = True
for i in range(len(msg.text)-1):
    if (msg.text[i]==' ')==(msg.text[i+1]==' '):
        b = False
if b and len(msg.text)>2:
    print('你 打 字 带 空 格',end='')

elif msg.text[:3] == 'ddl':
    print(random.choice(msg.text[3:].split()),end='')

elif random.random() < 0.05:
    print(msg.text + '嗷', end='')

elif random.random() < 0.05:
    jieba.setLogLevel(logging.INFO)
    s2=''
    l=list(jieba.cut(msg.text))
    random.shuffle(l)
    for i in l:
        s2=s2+i
    print(s2,end='')

elif msg.q=='1518350122' and  random.random()<0.02:
    print('zm教我画色图',end='')
