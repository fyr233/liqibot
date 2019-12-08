import asyncio
from pyppeteer import launch
from quart import Quart
from quart import request
import time
import threading
import logging

pyppeteer_level = logging.WARNING
logging.getLogger('pyppeteer').setLevel(pyppeteer_level)
logging.getLogger('websockets.protocol').setLevel(pyppeteer_level)

app = Quart(__name__)

class Room:

    @classmethod
    def __init__(self):
        pass

    '''
    @classmethod
    async def __new__(cls):
        self = super().__new__(cls)
        self.page = await browser.newPage()
        self.result = 'raw'
        return self
    '''

    @classmethod
    async def start(self):
        self.page = await browser.newPage()
        self.result = 'raw'
        self.updatetime = time.time()
        return self

    @classmethod
    async def evalua(self, expr):
        self.updatetime = time.time()
        #print('1', self.result)
        self.result = await self.page.evaluate(expr)
        '''
        try:
            self.result = await self.page.evaluate(expr)
            #print(2)
        except:
            self.result = 'error occured in evaluating'
        '''
        #print('2', self.result)
        return self.result

    @classmethod
    async def close(self):
        #print('being closed')
        await self.page.close()

    '''
    @classmethod
    async def __del__(self):
        print('being closed')
        await self.page.close()
    '''


@app.route('/new', methods=['POST'])
async def newroom():
    form = await request.form
    roomid = form['roomid']
    if roomid in roomlist:
        roomlist[roomid].updatetime = time.time()
        await CheckTimeOut()
        return 'room already running'
    else:
        roomlist[roomid] = Room()
        await roomlist[roomid].start()
        await CheckTimeOut()
        return 'new room is ready'

@app.route('/eval', methods=['POST'])
async def eva():
    form = await request.form
    roomid = form['roomid']
    expr = form['expr']
    if roomid in roomlist:
        roomlist[roomid].updatetime = time.time()
        return str(await roomlist[roomid].evalua(expr))
    else:
        return 'no such room, write \'ijs new\' to create a room, or \'ijsg new\' to create a public room'

@app.route('/close', methods=['POST'])
async def dele():
    form = await request.form
    roomid = form['roomid']
    if roomid in roomlist:
        await roomlist[roomid].close()
        del roomlist[roomid]
        #print(str(roomlist))
        #roomlist.pop(roomid)
        await CheckTimeOut()
        return 'success'
    else:
        await CheckTimeOut()
        return 'room not found'

#asyncio.get_event_loop().run_until_complete(main())

async def main():
    global roomlist, browser
    roomlist = {}
    browser = await launch({
        'executablePath': 'C:/Users/ADD/Documents/chrome-win32/chrome.exe',
        #'devtools': 'true',
        #'headless': 'false',
    })

    #await browser.close()

'''    
roomlist = {}
browser = launch({
    # Windows 和 Linux 的目录不一样，情换成自己对应的executable文件地址
    'executablePath': 'C:/Users/ADD/Documents/chrome-win32/chrome.exe',
    #'devtools': 'true',
    #'headless': 'false',
})'''

async def CheckTimeOut():
    #print('begin checking')
    del_list = []
    for roomid in roomlist:
        if time.time() - roomlist[roomid].updatetime > 20*60:
            print(roomid + 'being closed')
            #asyncio.get_event_loop().run_until_complete(roomlist[roomid].close())
            try:
                await roomlist[roomid].close()
            except:
                pass
            del_list.append(roomid)
    for roomid in del_list:
        del roomlist[roomid]
        
    
asyncio.get_event_loop().run_until_complete(main())
app.run(host='0.0.0.0', port=1960)