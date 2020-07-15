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
- time：提供时间
  ```python
  time.time()
  time.sleep()
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
- logging：日志
  ```python
  logging.log(logging.DEBUG, "This is a debug log.")
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
- json：处理json文件
  ```python
  json.dumps() # ->str
  json.loads() # from string -> dict
  ```

- multiprocessing：多进程
  ```python
  import multiprocessing as mp
  import os

  # 定义进程的执行内容
  def target_function(args):
      pass

  if __name__ == '__main__':
      # 使用Process类的实例。如果自定义类，则在子类中重载run方法。
      p = mp.Process(target=target_function, args=args, name=p_name)
      p.start()
      p.is_alive() # 进程是否存活
      p.join() # 阻塞当前进程，直至p执行结束。
      # p.close()

  # 使用Queue和Pipe，以及Lock
  def target_function(queue, pipe, lock):
      value = 'message'

      lock.acquire()
      try:
          queue.put(value)
          pipe.send(value), pipe.close()
      finally:
          lock.release()

  if __name__ == '__main__':
      # 初始化Queue
      queue = mp.Queue()
      # 初始化Pipe
      parent_conn, child_conn = mp.Pipe()
      # 初始化lock
      lock = mp.Lock()

      p = mp.Process(target=target_function, args=(queue, child_conn, lock,))
      p.start()

      # 输出结果
      print(queue.get())
      print(parent_conn.recv())

      p.join()

  # 使用共享状态
  def target_function(v, a):
      v.value = 10
      for i in range(len(a)):
          a[i] = -a[i]

  if __name__ == '__main__':
      v = mp.Value('d', 0.0)
      a = mp.Array('i', range(10))
      p = Process(target=target_function, args=(a,v,))
      p.start()
      p.join()

  # 使用进程池
  def target_function(args):
      return value

  if __name__ == '__main__':
      # 创建进程池
      pool = mp.Pool(processes=10)
      # 单个进程
      # 阻塞主进程 apply(func, args, kwds)
      # 不阻塞主进程 apply_async(func, args, kwds, callback)
      res = pool.apply_async(func=target_function, args=args)
      print(res.get(timeout=10))
      # 多个进程 map, map_async, imap, imap_unordered
      res = pool.map(func=target_function, iterable=[1,2,3])
      print(res) # type(res) -> list
  ```