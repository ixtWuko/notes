## 迭代器
迭代器用于遍历容器。迭代器比较重要的一点是 end() 对应的迭代器并不指向结尾元素，而是结尾元素的后面一个，是无法解引用的。
虽然都是通过相同的接口获得迭代器，但是不同的容器返回的迭代器是有差别的。
- 前向迭代器：无序容器返回的迭代器类型， 只能使用 `++` 前进。
- 双向迭代器：关联容器返回的迭代器类型，可以使用 `++` 和 `--` 前进和回退。
- 随机访问迭代器：序列容器返回的迭代器类型，不仅有双向迭代器的能力，还可以使用 `+=n` 和 `-=n` 的双向偏移。

#### 迭代器辅助函数
- `advance(iter, n)` ：原地修改，相当于 `+=n` 三种迭代器都支持，但不检查是否越界。
- `next(iter)`, `prev(iter)` ：非原地修改，相当于 `+1` 与 `-1`，但不检查越界。这两个函数也有移动多个位置的版本。
- `distance(iter1, iter2)`

此外还要注意一些容器不支持反向迭代器。

那些操作会使迭代器失效？
对于 vector，引发扩容会导致迭代器失效，插入或删除中间元素会导致之后的迭代器失效。对于 deque 插入元素会导致迭代器失效，插入或删除中间元素会导致迭代器失效。对于 unordered_set 插入后重哈希会导致迭代器失效。

容器 vector 使用 erase 删除一个元素后，会返回下一个迭代器。

为了避免错误，对于不修改迭代器指向内容的，使用 const iterator 更好。

## 范围 for
范围 for 可以方便地迭代容器，只要操作的对象满足以下条件之一：
1. 有 `begin()`, `end()` 成员函数；
2. 可以作为全局性的 `begin()`, `end()` 函数的实参；
3. 是 `initializer_list`，也即使用 `{}` 包围而数据；
4. 是一个数组。

就可以使用范围 for。注意灵活地使用 `&` 避免不必要的拷贝。

## 函数作为参数
普通函数、函数对象 和 Lambda 都可以作为函数参数。
#### Lambda
```c++
[<capture>](<parameter>){<statements>}
// parameter:   参数传递
// statmements: 执行语句
// capture:     指明与外部作用域的关系
// [=] lambda 内部可以读取所有外部作用域的数据；
// [&] lambda 内部可以读写所有外部作用域的数据；
// [x, &y] lambda 内部可以读取外部的 x，但不能修改；可以读写外部的 y
// (x, &y) 此时的 x, y 都是形参，在 lambda 内部修改 x 不会对外部的实参产生影响，但是修改 y 实际是修改外部的实参。

//  一些使用 lambda 的方法
auto cmp = [] (int x, int y) { return x < y; };
bool result = [](int x, int y) { return x < y; } (100, 50); // lambda 直接调用
sort(vec.begin(), vec.end(), [](auto& e1, auto& e2){ return e1.size() < e2.size(); });
```
#### 使用 lambda
```c++
auto cmp = [](int a, int b){ return a < b; };
sort(v.begin(), v.end(), cmp);
```

#### 使用普通函数
```c++
bool cmp(int a, int b) { return a < b; }
sort(v.begin(), v.end(), cmp);
```

#### 使用普通对象
```c++
struct cmp {
    bool operator()(int a, int b) { return a < b; }
};
sort(v.begin(), v.end(), cmp()); // 注意这里多加了一个括号，实例化一个对象
```

## 算法库
算法库中包含许多不同功能的函数，涵盖比较广， 可以参考 [C++ Reference / Algorithm](https://zh.cppreference.com/w/cpp/algorithm)。仅仅阅读文档可能无法弄清楚这些成员函数的具体表现，需要在实践中多累积经验。
