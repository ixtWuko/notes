# python 基础

## 1 数据类型

- 基本数据类型：`int`, `float`, `complex`, `str`, `bool`, `complex.real`, `complex.imag`，共轭`complex.conjugate()`。

- 前缀：`0b` `0B` 二进制；`0o` `0O` 八进制；`0x` `0X` 十进制

- 算术运算：`+`, `-`, `*`, `/`, `//`, `%`, `**`。字符串可以使用`+` `*`。

- 逻辑运算`and`, `or`, `not`，位操作：`&`, `|`, `~`, `^`, `<<`, `>>` 

- `is`是判断两个对象指向同一存储空间，`==`指两个对象值相等

- `int.bit_length()` 返回所需最少二进制位数的表示；

    `int.to_bytes(length,byteorder,signed)` 用length长度的自己表示，byteorder为字节序，有big和little两种，sighed是否用补码。

- `float.as_integer_ratio()` 返回一对整数，比值为该浮点数。

    `float.is_integer()` 如果是整数返回True。

- 字符串 `'string'`, `"string"`, `'''string'''`, `"""string"""`，其中三引号的可以换行。`r'string'`不会对 `\`后的字符转义，可以用于文件路径。

- `''' long long string can change line'''`

    除了用于文本，还有package和function的文档说明。

- `del`语句可以析构对象。

### str

```python
str.format(*args,**kwargs) #格式化字符串
str.capitalize() #返回首字母大写，其他都小写的同样的字符串
str.title() #将字符串转换成一个标题，每个单词首字母大写
str.lower() #全改为小写
str.upper()
str.swapcase() #大小写互换
str.center(width, fillchar=' ') #将字符串调整至width宽度，居中对齐，以fillchar填充
str.ljust(width, fillchar=' ') #将字符串调整至width宽度，左对齐，以fillchar填充
str.rjust(width, fillchar=' ')
str.zfill(width) #将一个数填充到width宽度

str.find(sub) #返回第一个子串位置，找不到返回-1
str.rfind(sub)
str.index(sub) #类似find，但找不到报错
str.rindex(sub)
str.replace(old,new[,count]) #替换，如果count没有给出，替换所有
str.count(sub) #子串出现的次数

str.join(iterable) #合成一个字符串
str.partition(sep) #以第一个sep分割字符串，返回3元组(sep前，sep，sep后)
str.rpartition(sep)
str.split(sep) #用sep分割，返回一个列表
str.rsplit(sep)
str.lstrip(char=' ') #删除字符串前面的符合char的字符
str.rstrip(char=' ')
str.strip(char=' ') #lstrip()加rstrip()的效果
str.encode(encoding='utf-8',errors='strict') #返回以utf-8编码的字符串

str.isalnum() #全是字母和数字
str.isalpha()
str.islower()
str.isupper()
str.isspace()
str.isdigit() #全是数字
str.isnumeric() #全是数字字符
str.isdecimal() #全是十进制数字
str.isprintable() #空或者可打印的
str.startswith(prefix) #如果字符串以prefix开头，返回True，否则返回False
str.endswith(suffix) #如果字符串以suffix结尾，返回True，否则返回False
```

### byte

使用`b'abc'`生成一个bytes类型的数据，使用bytearray()生成一个bytearray类型的数据。可以用于处理ascii编码的字符串。其方法和str类似。

### 基本数据结构

-   `list`, `tuple`, `dict`, `set`， `list()`, `tuple()`, `dict()`, `set()`
-   `list`使用`[]`生成，`tuple`使用`()`生成，`dict`使用`{}`生成，`set`只能用`set()`函数生成。
-   生成`list`的一种方法：`[x for x in range(1,9) if x%2 == 0]`
-   生成`dict`的一种方法：`[x: x**2 for x in range(1,9)]`
-   切片：`[start : end : step]`
-   判断一个元素是否在序列中`in` `not in`。求最值`max(s)` `min(s)`。
-   不是单个元素的数据类型，如`list`，用`a = b`只是将两个变量名绑定在同一存储区域上，使用`.copy()`是可以复制一份，但是二维的不能复制第二维，可以使用`copy`模块里面的`a = deepcopy(b)`复制高维的。

### list 

其他的结构参考这个，有不同的地方。

```python
list.append(element) #在最后添加一个元素
list.extend(anthor_list) #在最后添加一个list
list.insert(index, element) #在index处插入元素
list.remove(element) #删除第一个值为element的元素，没有则报错
list.pop(index = -1) #删除index处的元素并返回它，默认是最后一个
list.clear() #删除所有元素
list.index(element) #返回第一个值为element的index
list.count(element) #返回element出现的次数
list.sort(key=None, reverse=False) #默认从小到大。key是一个函数，输入为元素，输出为元素的某个属性
list.reverse() #元素按位置反转
list.copy() #返回list的一个浅拷贝

#此外的
sorted(list, key=None, reverse=False) #排序
del list[start:end] #del语句不是一个函数
```

### dict

```python
dict.get(key, default=None) #如果有key，则返回key的值；没有key，返回default
dict.pop(key, default=None) #如果有key，则弹出key的值；没有key，返回default
dict.popitem() #随机弹出一个
dict.clear()
```

### set frozenset

frozenset创建后不可更改。

```python
set.isdisjoint(other) #不相交返回True
set.issubset(other) #set是other的子集，返回True
set.issuperset(other) #other是set的子集，返回True

set.union(other,...) #返回set | other
set.intersection(other,...) #返回set & other
set.difference(other,...) #返回set - other
set.symmetric_difference(other,...) #返回在set ^ other
set.copy()
set.update(other,...) #set = set | other
set.intersection_update(other,...) #set = set & other
set.difference(other,...) #set = set - other
set.symmetric_difference(other,...) #set = set ^ other

set.add(elem)
set.remove(elem) #不存在则报错
set.discard(elem) #如果存在则删除
set.pop() #弹出随机的一个
set.clear() #清空
```

### 控制流

-   `if condiction: ... elif condiction: ... else: ...`
-   `while condiction: ... else: ...`
-   `for ... in ...: ... else: ... `
-   `break` `continue` `pass` 

### 常用内建函数

```python
abs(x) #绝对值或虚数的模
round(number, ndigits) #舍入到ndigits位，但是不是四舍五入
hash(x) #哈希值
complex(real,imag) #返回一个复数对象
sum(iterable) #求和

bool(x) #x对应True还是False
all(iterable) #所有元素都为True，返回True，否则返回False
any(iterable) #至少有一个元素为True，返回True，否则返回False

int() float() str()
repr() #返回的字符串是给python看的，而str()返回的字符串给人看的
bin(x) #int->binary
oct(x) #int->octal
hex(x) #int->hexadecimal
chr(i) #unicode码->字符，如chr(8364)输出为欧元符号
ord(c) #与chr()相反的过程

list() tuple() dict() set() #构建相应对象
len(s) #返回元素数量
next(iterable) #返回迭代器的下一个元素
range(object) #返回的并不是list，需要使用list()来转换
sorted(iterable, key=None, reverse=False) #key指定排序的属性
reversed(seq) #翻转顺序

iter(object) #返回一个迭代器
enumerate(iterable) #返回一个元素为 (index, element) 结构的迭代器
zip(*iterable) #输入多个iterable，如a、b，返回一个元素为 (a[i],b[i]) 结构的迭代器，停止在最短的iterable上
filter(function, iterable) #过滤，function的输入是iterable的一个元素，输出是布尔值，filter使用function过滤整个iterable
map(function, iterable) #对iter中的每个元素执行function操作

help()  返回一些描述
type() #返回类型
id(object) #返回内存地址
dir(module) #返回模块中定义了多少名字，不带参数时返回本地作用域的名称列表
globals() #返回当前的全局符号表的字典
locals() #返回当前的本地符号表的字典

str = input('input here: ') #输入
print(*args, sep='', end='\n')
eval('code') #返回参数中的表达式的计算结果
exec('code') #执行参数中的代码
open(file, mode, encoding=None) #打开文件

hasattr(object, name) #object是否有名为name的属性
delattr(object, name) #删除object的名为name的属性
```

## 2 模块与包

### 导入模块或包

```python
import packagename
import packagename as pn
from random import choice
```

### 构建模块

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

' a test module '

__author__ = 'Michael Liao'

import sys

def test():
    args = sys.argv
    if len(args)==1:
        print('Hello, world!')
    elif len(args)==2:
        print('Hello, %s!' % args[1])
    else:
        print('Too many arguments!')

if __name__=='__main__':
    test()
```
##3 函数

```python
#function of python
def function(*args) #调用时对应的参数打包成一个名为args的list送入函数
def function(**kwargs) #调用时对应的参数打包成一个名为kwargs的dict送入函数
def function(args='default') #默认参数

def function():
    'this is a function docstring'
    pass
def function():
    ''' this is a function docstring's first line;
    this is a function docstring's second line.'''
    pass

print(function.__doc__) #输出函数的文档
print(function.__name__) #输出函数的名字

def func_a():
    pass
def func_b(func_a): #函数是一级公民，函数名可以作为变量名
    func_a()
    
def outer():
    def inner(): #函数内部定义函数
        pass
    
#闭包 用一个函数定义生成一组类似的函数
def write_log(error_type):
    def print_log():
        return 'error type is: ' + error_type
    return print_log
a = write_log('disk error')
b = write_log('memory error')
#a,b是不同的函数

#匿名函数
def print_result(result, function):
    for number in result:
        print(function(number))
#example
result = [1,2,3,4,5]
print_result(result, lambda number: number ** 5)
#这里lambda产生一个没有名字的函数，因为我们不需要函数名字，但是需要一个固定的函数来生成一系列新的函数

#生成器
def my_range(start, end, step):
    number = first
    while number < end:
        yield number #使用yield实现
        number += step
a = my_range(1,5,1)
#a的类型是生成器，和range()返回的结果类似

#修饰器
def document_it(func):
    def new_function(*args, **kwargs):
        print('Running function:', func.__name__)
        print('Positional arguments:', args)
        print('Keyword arguments:', kwargs)
        result = func(*args, **kwargs)
        print('Result:', result)
        return result
    return new_function
@document_it
def add_int(a, b):
    return a+b
#等价于
add_int = document_it(lambda a,b: a+b)
```
## 4 对象


```python
#class of python
class Car():
    def __init__(self, color): #初始化
        self.color = color
class Yugo(Car): #继承
    pass
#继承可以得到父类的方法，但是也可以重写此方法进行重载
#在子类的定义中，super()是指父类，以此使用父类中的定义
#在定义某个以父类作为参数的函数之后，其对子类使用这个函数（由于多态）

#直接定义的属性不够安全,没有进行检查
class Car():
    def __init__(self, value):
        self.color = value
    @property #通过property修饰，定义访问car.color时的行为
    def color(self):
        return 'the color is: ' + self._color
    @color.setter #通过setter修饰，定义对car.color赋值时的行为
    def color(self,value):
        self._color = value

class Car():
    def __init__(self, value):
        self.__color = value #__color是无法直接访问的私有变量

class Car():
    n = 0
    def __init__(self):
        n += 1
    @classmethod #使用classmethod修饰，定义一个类方法
    def counter(cls): #这里的例子是一个计数器，记录用Car生成了多少实例
        return cls.n

#定义类的特殊方法
#__init__(self) 初始化
#__del__(self) 析构
#__eq__, __ne__, __lt__, __gt__, __le__, __ge__(self, other)
#__add__, __sub__, __mul__, __truediv__, __floordiv__, __mod__, __pow__ (self, other)
#__str__(self) print()时的输出及str()函数的行为 __repr__ __bool__
#__len__(self)
#__iter__, __next__ 用于for ... in ...循环时的行为
#__getitem__, 用于切片时的行为
#__call__, 用于定义调用该实例时的行为
```

## 5 文件


```python
fileobj = open('path/filename', 'mode')
#mode为两个字符，前一个为rwxa中的一个，为只读、写入、新建文件并写入、在结尾增添；后一个为bt中的一个，表示二进制文件和文本文件
    
fileobj.close()
with open('path/filename', 'mode') as f: #自动关闭文件，无需进行f.close()
    f.dosomething
    
fileobj.write(things)
print(things, file = fileobj)
    
text = fileobj.read(position) #读取position之后的所有内容
text = fileobj.readline() #读取一行
    
position = fileobj.tell() #获取文件指针的位置
fileobj.seek(offset, origin) #设置文件指针到origin之后offset处
```
## 6 异常与错误

```python
try:
    pass
except ErrorType as a:
    print('there is a ',a)
finally:
    pass #cleanup

#抛出错误
raise ErrorType(text)

#自定义异常，均继承自Exception

#断言，用于调试
assert n!=0, 'n is zero' #如果为假，则输出后面的文本
```

## 7 虚拟环境

使用pyvenv管理虚拟环境。

```shell
$ pyvenv envname #创建虚拟环境
$ envname/Scripts/activate #windows下激活虚拟环境
$ source envname/bin/activate #unix/macos下激活虚拟环境
#激活虚拟环境之后可以使用pip安装包了
$ pip install requests==2.6.0 #安装特定版本的包
#可以使用requirements.txt文件描述需要的包，格式为 packagename==version，每个包一行
$ pip install -r requirements.txt #requirements文件安装包
```