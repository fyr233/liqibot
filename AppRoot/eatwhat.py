import random

inplace = ['东区学生食堂', '东苑', '风味', '东区教工', '星座', '茶餐厅', '美广', '糕点厂', '南区', '桃李苑', '西区学生食堂', '金桔园', '西三', '芳华', '西区教工', '西苑', '正阳楼']
outplace = ['无锡汤包', '老卤面', '湘渝人家', '冒菜', '太和板面', '王仁和米线', '艾比克', '庐州太太', '张亮麻辣烫', '牛牛', '肥叔锅贴', '杨国福麻辣烫', '沙县', '兰州拉面', '淮南牛肉汤', '重庆小面', '胖姐拌面', '黄焖鸡米饭']

a = random.random()
if a > 0.8 :
    a = int(len(outplace) *random.random())
    print(outplace[a],end='')
else :
    a = int(len(inplace) *random.random())
    print(inplace[a],end='')