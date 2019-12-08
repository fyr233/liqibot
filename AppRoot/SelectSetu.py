#coding:ANSI
import os
import random

if random.random()<0.2:
    print('你看太多色图了',end='')
else:
    filenames = os.listdir('data/image/setu')
    index = random.randint(0, len(filenames)-1)
    print('[CQ:image,file=setu/' + filenames[index] + ']',end='')