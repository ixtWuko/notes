# Python 常用标准库

- math：数学函数
  ```python
  # 常量 pi, e, inf
  # ceil, floor, isinf
  # sqrt, exp, log, gcd, 三角函数
  # degrees, radians
  # factorial -> 阶乘
  # prod(iter) -> 积
  # dist(iter1, iter2) -> 欧氏距离
  ```
- cmath：提供到复数的支持
  ```python
  # phase(c) -> phi
  # polar(c) ->(r, phi) 转为极坐标
  # rect(r, phi) -> c 转为复数
  ```
- random：随机数
  ```python
  random.seed(time.time())
  random.randrange(start, stop, step)
  random.randint(a,b)
  random.random() # -> [0.0, 1.0)
  random.uniform(a,b) # ->[a,b]
  random.shuffle(seq) # 打乱
  random.sample(seq, k)
  # random还提供了各种分布的随机方法
  ```
- re：正则表达式
- datetime：基本时间和日期
  ```python
  # date, time, datetime, timedelta
  dt = datetime.date.today()
  print(dt.year, dt.month, dt.day, dt.weekday())
  dtt = datetime.datetime.now()
  print(dtt.year, dtt.month, dtt.day, dtt.hour, dtt.minute, dtt.second, dtt.microsecond)
  print(dtt.timestamp())
  ```
- copy：提供深拷贝
  ```python
  copy.deepcopy(iter)
  ```
- itertools：为迭代器提供的功能
  ```python
  # count(2.5, 0.5) -> 2.5 3.0 3.5 ... inf
  # cycle('ABCD') --> A B C D A B C D A B C D ...
  # repeat(10, 3) --> 10 10 10
  # accumulate([1,2,3,4,5]) --> 1 3 6 10 15
  # chain('ABC', 'DEF') --> A B C D E F
  # compress('ABCDEF', [1,0,1,0,1,1]) --> A C E F
  # dropwhile(lambda x: x<5, [1,4,6,4,1]) --> 6 4 1
  # takewhile(lambda x: x<5, [1,4,6,4,1]) --> 1 4
  # filterfalse(lambda x: x%2, range(10)) --> 0 2 4 6 8
  # [k for k, g in groupby('AAAABBBCCDAABBB')] --> A B C D A B
  # starmap(pow, [(2,5), (3,2), (10,3)]) --> 32 9 1000
  # product('ABCD', 'xy') --> Ax Ay Bx By Cx Cy Dx Dy
  # permutations(range(3)) --> 012 021 102 120 201 210
  # combinations(range(4), 3) --> 012 013 023 123
  # combinations_with_replacement('ABC', 2) --> AA AB AC BB BC CC
  ```
- functools：高阶函数工具
  ```python
  # partial(f, args)
  # reduce(f, iter)
  ```

- csv：处理csv文件
  ```python
  with open('a.csv', 'r', newline='') as csvfile:
    # reader = csv.reader(csvfile)
    reader = csv.DictReader(csvfile)
    for row in reader:
      pass
  with open('a.csv', 'a', newline='') as csvfile:
    # writer = csv.writer(csvfile)
    writer = csv.DictWriter(csvfile)
    writer.wirteheader()
    writer.writerow()
    writer.writerows()
  ```