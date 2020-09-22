# 文字处理

## 字符串
字符串也是标准库中提供的，可以参考 [String](https://zh.cppreference.com/w/cpp/string/basic_string) 。

#### 字符串使用的细节
- 字符串的实现：一个保存字符串长度的int，和一个指向 char[] 的指针。
- 字符串提供了 `+=` 可以连接字符串和字符，但是 `+` 只能连接两个字符串。
- 可以使用类似于 C 字符串的形式，使用指针访问，`&str[0]`。
- 字符串的成员函数与其它容器的不同，有些往往只需要提供下标值就可以，不需要迭代器。

## 正则表达式
标准库中的 regex 提供了正则表达式的功能。
```c++
regex pattern("[a-z]+");
smatch res;    // 存放结果的迭代器
bool ret = regex_match("hello,world", res, pattern);    // 匹配整个字符串
bool ret = regex_search("hello, world", res, pattern);  // 匹配子串
res = regex_replace("hello, world", pattern, alter)
```

## IO
C++ 的 IO 库内的 iostream, fstream, sstream 可以用来处理输入输出、字符串流以及读写文件，对于文件和目录的操作，也有对应的 filesystem 库。

对于特定的文件格式，使用对应的封装好的第三方库是更加方便的选择。