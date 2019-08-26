# python 标准库 

需要更新，根据使用到的来添加。

## os

```python
import os
os.name #操作系统名称
os.uname() #更详细的系统名称等，在windows上无法使用

os.environ #环境变量
os.environ.get('path')
os.getenv() #获取环境变量
os.putenv() #设置环境变量

os.getcwd() #获取当前工作路径
os.path.abspath('.') #查看当前目录的绝对路径
os.path.dirname() #获取路径
os.path.join(dirname, filename) #将两个参数合并成一个完整路径
os.path.split(path) #分离为dirname和filename
os.path.splitext(filename) #分离文件名和扩展名
os.path.basename(path) #返回文件名
os.walk() #遍历目录
os.chdir(path) #改变当前路径

os.path.isdir(dirname) #是否是一个目录
os.path.isfile(filename) #是否是一个文件
os.path.exists(name) #是否存在该目录或文件
os.path.getsize(name) #获得文件大小

os.listdir() #当前目录的目录和文件列表
os.mkdir(path) #创建目录
os.rmdir(path) #删除目录

os.rename(oldname, newname)
os.remove(filename)
os.fchmod(filename, mode) #更改权限
os.fchown(filename, uid, gid) #更改所有权

os.system(command) #运行shell命令

os.getpid() #返回进程id
pid = os.fork() #创建子进程，windows下无法使用

os.getlogin() #返回当前用户名
```



## shutil

```python
import shutil
shutil.copyfile('data.db', 'archive.db') #复制文件
shutil.move('/build/executables', 'installdir') #移动文件
```



## glob

```python
import glob
glob.glob('*.py') #以通配符搜索文件
```



## datetime

```python
from datetime import datetime
dt = datetime(year, month, day, hour, minute, second)
now = date.now()

#now.date() .time() 
#.year .month .day .hour .minute .second .weekday

dt.timestamp() #以秒记的时间
dt = datetime.fromtimestamp(t) #将以秒记的时间转换为datetime
dt = datetime.utcfromtimestamp(t)

cday = datetime.strptime('2015-6-1 18:19:59', '%Y-%m-%d %H:%M:%S')
now.strftime('%Y %m %d %H:%M:%S') #以格式化的字符串输出时间

now + datetime.timedelta(hours = 10) #增加和减少
```

## time

```python
import time
time.time() #以秒记的时间
time.ctime()

time.clock() #返回cpu时间，用于对程序计时

time.sleep(seconds) #暂停进程一段时间
```

## multiprocessing

```python
from multiprocessing import Process #导入Process类
from multiprocessing import Pool #导入Pool类，进程池
import multiprocessing as mp #或者直接导入整个模块

def target_function(args):
    pass
if __name__ == '__main__':
    p = Process(target=target_function, args=(args,))
    p.start()
    p.join() #等待当前子进程结束之后再向下运行，用于进程间同步
# Process类的其它方法

def target_function(args):
    pass
if __name__ == '__main__':
    with Pool(5) as p:
        p.map(target_function, iter)
```

## threading

```python
import threading
def target_function(args):
    pass
if __name__ == '__main__':
    t = threading.Thread(target=target_function, args=(args,), name = 'threading name')
    t.start()
    t.join() 
    
# Lock
from threading import Thread Lock
def f(lock, args):
    lock.acquire()
    try:
        pass
    finally:
        lock.release()
if __name__ == '__main__':
    lock = Lock
    t = Thread(target=f, args=(lock,args))
    t.start()
```

## itertools

```python
import itertools
cnt = itertools.counter(start, step = 1) # 生成一个无限的迭代器
c = itertools.cycle('abc') # --> a b c a b c a b c...
rp = itertools.repeat('a', 5) # --> a a a a a
ch = itertools.chain('abc', 'def', 'ghi') # --> a b c d e f g h i
```

## enum

```python
from enum import Enum # 枚举类
month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))
```

## collections

```python
# Counter
from collections import Counter
cnt = Counter()
for word in ['red', 'blue', 'red', 'green', 'blue', 'blue']:
    cnt[word] += 1
# cnt为{'blue':3, 'red': 2, 'green': 1}
cnt = Counter('helloworld')
cnt.element() #返回一个iterable的对象，包含所有的元素
cnt.most_common(n) #返回前n个最多的元素
cnt.update(iterable) #更新叠加

# deque
from collections import deque
q = deque(iterable) #产生一个deque实例
# q.append(item) q.appendleft(item)
# q.pop() q.popleft() q.remove(item) q.insert(index, item)
# q.extend(iterable) q.extentleft(iterable)
# q.clear() q.copy() q.index(item) q.count(item)
# q.reverse() q.rotate(n)

# namedtuple 
from collections import namedtuple
Point = namedtuple('Point', ['x', 'y'])
p = Point(1,2)
# p.x, p.y 分别为x, y

# defaultdict
from collections import defaultdict
dd = defaultdict(lambda:'none')
dd['key'] = 'hello'
# dd['key']为'hello'，但是其它的dd['otherkey']为'none'

# OrderedDict 可以保持字典中的key为有序的状态
from collections import OrderedDict
od = OrderedDict([('a', 1), ('b', 2), ('c', 3)])
# 会保持key的顺序
```

## struct

```python
import struct
struct.pack('>I', 10240099)
# '>'为big-endian，对应的'<'为little-endian
# I为无符号整数，4字节；H为2字节，c为1字节

struct.unpack('>IH', b'\xf0\xf0\xf0\xf0\x80\x80')
# 注意这里前面的参数每一个字符对应后面的一部分，这样可以对一串字节采用不同的编码
# 可以用于读取二进制文件的文件头，获取文件的一些属性
```

## base64

Base64是一种任意二进制到文本字符串的编码方法，常用于在URL、Cookie、网页中传输少量二进制数据。

```python
import base64
base64.b64encode(text)
base64.b64decode(code)

base64.urlsafe_b64encode(url)
base64.urlsafe_b64decode(code)
```

## hashlib hmac

```python
import hashlib
md5 = hashlib.md5('hello, world'.encode('utf-8'))
md5.update('hello, world'.encode('utf-8'))
# 使用update()一段一段地计算
print(md5.hexdigest())

sha1 = hashlib.sha1('hello, world'.encode('utf-8'))
sha1.update('hello, world'.encode('utf-8'))
print(sha1.hexdigest())

#另外的两个属性 .digest_size 和 .block_size
```

##  hmac

```python
import hmac
message = b'hello, world!' #只有使用byte类型作为输入
key = b'keyword'
h = hmac.new(key, message, digestmod = 'MD5') 
#可以为hash增加一个keyword防止被暴力破解
print(h.hexdigest())
```
