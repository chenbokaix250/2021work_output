import asyncio, random

async def rich(q, total):
    """任性的富豪，随机撒钱"""
    
    while total > 0:
        money = random.randint(10,100)
        total -= money
        await q.put(money) # 随机生成[10,100]之间的整数
        print('富豪潇洒地抛了%d块钱'%money)
        await asyncio.sleep(3*random.random()) # 在0-3秒之间随机延时

async def lucky(q, name):
    """随时可以捡到钱的幸运儿"""
    
    while True:
        money = await q.get()
        q.task_done()
        print('%s捡到了%d块钱！'%(name, money))

async def run():
    q = asyncio.Queue(1)

    producers = [asyncio.create_task(rich(q, 300))]
    consumers = [asyncio.create_task(lucky(q, name)) for name in 'ABC']
    
    await asyncio.gather(*producers,)
    await q.join()
    
    for c in consumers:
        c.cancel()

if __name__ == '__main__':
    asyncio.run(run())



