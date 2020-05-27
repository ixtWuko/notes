# Python 文档阅读

目标是成为 Python 使用专家。

#### 数据类型

```python
# int, float, complex

# list[]
# append, pop(2) / del lst[2],
# remove, insert, extend, clear / a[:] = [], copy / b = a[:],
# count, index, reverse, sort(ker=f)

# tuple()

# set(), frezonset() <-无重复的项
# union, intersection, difference

# dict{}
{x: x**3 for x in range(10)}
# update, fromkeys, clear, copy, get, setdefault, pop, popitem,
# items, keys, values

# string ''
# center(40), find, replace, join, split, strip <-去除空白

# str() 转换为字符串
# repr() 不进行转义字符的转换
# r'C:\Program Files\' <-原始字符串
# b'hello' <-bytes对象，不是字符串，是字符串的编码结果。
# format
f"{first}, {second} and {third}."
"{0}, {1} and {2}.".format(first, second, third)
"{num:<10.2f}".format(math.pi) # <为左对齐, 10为字符串宽度，.2为保留两位小数，f为浮点数。

# class
# issubclass, isinstance <-是否为实例, hasattr <-是否有接口
# self, super()
# @staticmethod, @classmethod
# __iter__(self), __next__(self), __contains__(self), yeild 用于定义迭代器
# python类还不够熟悉，还需继续学习和练习
```

#### 语法

```python
# 解包
a, b, *rest = [1,2,3,4,5]
# 收集参数
def f(a, *b, **c) # b为元组，c为字典
# 匿名函数
lambda x, y: x + y

# 测试
# assert
# raise errorType
# try: ... except [errorType]: ... finally: ...
```

#### 内建函数

```python
dir(), type()
round() # 不只是四舍五入，半值取偶数
hash()

all(iter), any(iter) # ->全为True，存在True
len(iter), sum(iter), max(iter), min(iter)
sorted(iter, key=f), reversed(iter)

zip(iter1, iter2, ...) # -> (ele1, ele2, ...)
enumerate(iter)   # -> (index, ele)

# 迭代工具
# [f(ele) for ele in iter]
map(f, iter)      # -> f(ele)
filter(f, iter)   # -> ele if f(ele)
reduce(f, iter)   # f(...f(f(ele0, ele1), ele2)...)

# 更多内容请查看：https://docs.python.org/zh-cn/3/library/functions.html
```