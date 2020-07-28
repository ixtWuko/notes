# C++
cpp是语言的联邦，可以分成四个层次：
* 以c为基础的基本内容；
* 面向对象的cpp；
* 模板编程，元编程；
* 标准模板库。


## 类型

### 基本类型
```cpp
bool, char, wchar_t, int, float, double
short, long
// int 默认为有符号的，使用无符号的整数 unsigned。
// float 在图形学的程序中使用比较多，其他时候使用更高精度的 double 比较好。

// 类型转换，使用隐式类型转换比较好，不推荐用显示的强制类型转换。
double a = 3.1415926;
int b = a; // b = 3
// 强制类型转换
cast_name<type>(var);
// cast_name: static_cast, dynamic_cast, const_cast, reinterpret_cast

// 字面值与变量
// 字面值就是数值，字符串这些确定的值。
// 变量：声明 -> 定义 -> 初始化
// 声明是告知变量名的使用；
// 定义是为变量分配实体（可以理解为分配内存）；
// 初始化是为变量第一次赋值。
extern int a; // 只声明不定义，作用是通知编译器此处使用的这个变量是外部定义的。
extern C // 声明该函数是 C 的函数
// 默认情况下const常量仅在文件内有效，在分离式编译时如果想在其他文件中使用这些常量，在头文件和源文件中都使用 extren const，告知编译器该常量在文件外也有效。

// 默认初始化：基本类型的变量在函数外的会被初始化为0，在函数内的不被初始化。
// 列表初始化：C++11中引入的。使用 () 也可以进行初始化，但是阅读困难，推荐使用 {}。
// 列表初始化会检查类型，不能进行类型转换；括号/等号的赋值则可以进行类型转换等。
int a{10};

// 作用域
using namespace std;
```

### 复合类型
```cpp
// 引用
int& ref = a;
// 主要用在函数定义中，避免对参数的拷贝。对于基本类型，使用拷贝参数比较好，对于自定义的类型，使用引用比较好。
void func(const Mytype& var)

// 指针
int* p = &a;
*p = b; // * 用来解引用； & 用来取地址。
p = nullptr;
// 指针也是迭代器

// 引用，指针与const的组合效果。
const int& ref = a; // 不能通过ref修改a，底层const
const int* p = &a; // 不能通过p修改a，底层const
int* const p = &a; // 不能修改p，顶层const
```

### 顺序容器
vector, deque, list, forward_list, array, string
* 头文件与类型名相同。
* vector, deque, string 的存储空间连续，不适合在中间或删除插入元素；
* list, forward_list 使用链表构建，不适合随机访问，适合插入和删除元素。
* array是固定大小的,可以认为是一种更好的数组。

```cpp
// c 代表一个顺序容器
// 默认构造, 拷贝构造, 列表初始化

c.size();
c.max_size();
c.empty();

swap(c1, c2);

// array 没有的功能
c.push_back(ele);
c.emplace_back(Argos);
c.pop_back();
// forward_list 不支持

c.push_front(ele);
c.emplace_front(args);
c.pop_front();
// vector, string 不支持

c.insert(iter, ele);
c.emplace(iter, args);
// 也有插入多个元素的函数
c.erase();

c.clear();
c.resize(n);

//上述改变容器结构的操作可能会使迭代器失效。

c.back(); // forward_list不支持
c.end();
c[7];
c.at(7);

array<int, 32> a;
```

### string
```cpp
string str = "This is a string.";
// string 可以使用 + 连接，使用 [] 索引。
str.empyt();
str.size();
str.substr(a, b);
str.replace(a, b, str2);
str.find(word), str.rfind(word);

to_string(number);
stoi(str), stof(str), stod(str);
str.c_str();
// 用来判断大小写等的函数在头文件 <cctype> 中
```

### 容器适配器
stack, queue, priority_queue

```cpp
stack<string, vector<string>> str_stack;
stack<string> str_stack(str_vector);

stack.pop();
stack.push(ele);
stack.emplace(args);
stack.top();

q.pop();
q.push(ele);
q.emplace(args);
q.front();
q.back();
q.top(); // 返回最高优先级的
```
### 迭代器
```cpp
iter = v.begin();
iter == v.end();
iter = v.cbegin(), iter == v.cend();
iter = v.rbegin(), iter == v.rend();
iter = v.crbegin(), iter == v.crend();
// c const, r right

// 迭代器类似与指针，指针也是一种迭代器。
*iter; // 解引用
(*iter).member;
iter->member;
// 对于数组，使用指针进行迭代
iter = begin(array);
iter == end(array);
```

### 关联容器
map, set, multimap, multiset
* map用于保存key-value, set用于保存key.
* multimap, multiset允许重复的key.
* 在上述四个类型前加 unordered_构成对应的无序集合, 使用哈希组织, 在存储上是一组桶.

```cpp
map<string, int> word_count;
set<string> words;

pair<string, int> a; // map中的一个键值对可以用pair类型, 头文件为 utility
a.first, a.second;
make_pair(first, second);

// 使用pair类型对map进行迭代
auto map_it = word_count.begin();
map_it->first, map_it->second;
// set的迭代则比较简单, 类似于vector.

c.insert(ele);
c.emplace(args);
c.insert(begin, end);
c.erase(key);
c.erase(iter);
c.erase(begin, end);

c.find(key); -> iter
c.count(key);
c.lower_bound(key);
c.upper_bound(key);
c.equal_range(key); -> pair<begin, end>

// 与pair类似的基础设施 tuple
tuple<T1, T2, …> t; // tuple由多个值组成一个元素
make_tuple(v1, v2, …);
```

### 智能指针
用于管理堆上的内存空间, 显式地创建和销毁对象.

```cpp
#include <memory>
shared_ptr<string> p1;
unique_ptr<string> p2;

shared_ptr q(p1); 
// shared_ptr可以复制, unique_ptr则不能复制
// 这两个指针在会自动销毁

// 使用make_shared产生一个shared_ptr
auto p = make_shared<int>(42);

int* p = new int;
delete p;
// new与delete是显示地处理内存, 容易出错.
// 为防止悬垂指针, 会在释放后对指针变量置空
p = nullptr;

// 使用new构建动态数组
int* pa = new int[size]; //在程序运行种确定数组大小
delete [] pa;
```


### 其他
```cpp
typedef Type MyType;
using MyType = Type;
auto var = func();
```

## 语法
### 运算符
- 当一个对象被用作右值的时候，用的是对象的值；当一个对象被用作左值的时候，用的是对象的身份。
- 算数运算符(没有乘方)，递增递减运算符，逻辑运算符，关系运算符，赋值运算符，位运算符。
- 成员访问运算符 `.` `->` ，条件运算符 `?:` ，逗号运算符。
- sizeof运算符 sizeof (type) 获取字节数。

### 语句
- `if ... else if ... else`
- `switch ... case ... default`
- `while`, `for (;;)`, `for (auto ele: vec)`, `do ... while ...`
- `break`, `continue`, `goto`, `return`
- `try {} catch (error_type) {} ... `, `throw ...`
- `assert(expr)` 使用定义一个预处理变量 NODEBUG 关闭这些 assert 。

### 函数
- 函数定义中的变量都是有生命周期的，当函数块执行结束后，这些变量就会被销毁。如果想在函数调用时保留其内部的某些变量，比如想统计函数被调用的次数，可以在函数定义中使用 static 修饰一个变量，在函数执行结束后仍然存存活。

- 对于基本类型的参数，推荐使用传值参数；对于容器或自定义类型的参数，推荐使用传引用参数；当然某些情况下也可以传指针参数。传引用参数或传指针参数可以避免拷贝，尽量使用常量引用。

- 对于数组参数，推荐使用标准库的做法：`void func(const int* beg, const int* end)`；另外一个做法是将数组指针和尺寸作为参数传递。

    ```cpp
    int main(int argc, char* argv[]) {}
    // argc 为 argv 中字符串的数量
    // argv 为一个字符串数组，在命令行中通过空格分隔成多个数组
    // argv 的第0个元素是程序/命令的名称，第1个开始才是参数
    ```

- 不能是局部对象的引用和指针，但是可以是数组指针或函数指针。

    ```cpp
    // 返回的引用不是局部的，而是函数外部定义的，因此可以这样写。
    const string& shorterString(const string& s1, const string& s2) {
        return s1.size() <= s2.size() ? s1 : s2;
    }
    // 下面这个例子就是错误的，因为s被销毁了
    const string& initString() {
        string s = "hello";
        return s;
    }
    ```

- 函数返回值不能是数组或函数，可以返回数组指针或引用，但这种写法太难读了，还不如把输出数组作为一个参数。

- 函数重载。

- 可以设置默认参数。一旦一个参数被设置了默认值，其后的所有参数都必须设置默认值。

- 内连函数。内连函数并不是真正的函数，没有函数调用的消耗，用于优化程序的速度。使用 `inline` 修饰函数定义，内连函数只是向编译器发出内连的请求，编译器不一定会接受，比如递归的内连函数就很难展开。

- constexpr函数。`constexpr int foo = func();`  func的形参和返回值的类型必须都是字面值，且函数中只能有一条return语句，在编译阶段会把调用替换成结果值。

- 内连函数和constexpr函数放在头文件中。

- 函数指针。

    ```cpp
    // 函数指针
    // bool *pf() 返回的是指向bool类型的变量。
    bool (*pf)(const string&，const string&); // 声明一个函数指针 pf，指定了参数和返回值类型。
    pf = &lengthCompare; // lengthCompare是一个返回 bool 类型的函数。
    pf = lengthCompare;  // 与上一个是等价的，也即 & 可以省略。
    bool b = (*pf)(str1, str2); // 对函数的调用
    bool b = pf(str1, str2);    // 与上一个是等价的，也即 * 可以省略。
    ```
* Lambda

```cpp
// [捕获列表](参数列表) -> 返回类型 {函数体}
// 捕获列表中是传递到lambda函数体的外部变量, 
// 为空是表示不捕获
// & 表示引用捕获, = 表示值捕获, 此两种由编译器推断捕获哪些变量
```

## 类
```cpp
class Sample : public Parent { //这里的public或private决定了 用户 能否访问parent的成员
public: // , private, protected 派生类允许但是外部不允许的
    void member_function() {};
    void member_function() const {}; // 这种在类被初始化为一个常量实例时，不加 const 的函数无法被调用，因为 this 是一个常量。
    Sample& add(const Sample& rhs) {
        some work;
        return *this;
    }
    Sample add(const Sample& lhs, const Sample& rhs) {
        Sample sum = some work;
        return sum;
    }
    // 内联成员函数
    inline
    void member_function() {};
    // 静态成员
    static int var; // var是类的成员，而不是实例得成员
    static
    void member_function() {};
    // 静态成员函数只能访问类的静态属性，不能访问非静态属性，不能调用非静态成员函数。静态成员函数没有隐式的this指针。

    // 友元，使外部定义的函数或类能够访问类的私有成员。
    friend some_func(const Sample& s);
    friend other_class;
    // 友元关系不能继承

    // 默认构造函数：控制默认的初始化过程，没有任何实参。
    Sample() = default; // 显式要求使用合成的
    // 普通的构造函数
    Sample(arg1, arg2): member1(arg1), member2(arg2) {}
    // 委托的构造函数
    Sample(arg1): Sample(arg1, 0) {}
    // 转换构造函数
    // 使用 explicit 抑制默认的转换构造函数
    // 拷贝构造函数
    Sample(const Sample&); // 对于禁止拷贝的类，使用 = delete 删除拷贝构造函数和拷贝赋值函数
    Sample& operator=(const Sample&); // 拷贝赋值运算符
    Sample& 
    
    // 析构函数
    ~Sample();
    
    // 运算符重载
    Sample& operator+(const Sample& ohs, const Sample& rhs);
    
    // 虚函数
    virtual run(); // 可以通过基类访问派生类的函数, 实现多态
    // 纯虚函数
    int func() = 0;
    // 纯虚函数的类是抽象基类，不能直接使用：
}
```


### IO
```cpp
// iostream, fstream, sstream
ifstream input (filepath, ios::in);
ifstream output(filepath, ios::app); // ios::out

istringstream stem(s);
double d;
stem >> d; // 可以用于将 string 转换为其它类型
```

### 泛型算法

```cpp
#include <algorithm>
#include <numeric>

find(lst.cbegin(), lst.cend(), val); -> iter
accumulate(c.cbegin(), c.cend(), 0); -> sum
equal(c1.cbegin(), c1.cend(), c2.cbegin()); -> bool

fill(c.begin(), c.end(), 0);
fill_n(c.begin(), n, 0);
copy(begin(a1), end(a1), a2); -> bool //拷贝数组
replace(c.begin(), c.end(), 0, 42); //将范围内的0替换成42

sort(c.begin(), c.end());
unique(c.begin(), c.end()); //返回的唯一排在容器前面部分, 该函数返回unique序列的尾迭代器

stable_sort(c.begin(), c.end(), compare_func);
for_each(c.begin(), c.end(), func);
```

## 其他
