# Cpp 基础

## Part I 基础
可以将cpp看作多种次语言的联邦，有4种次语言：C、OO Cpp、Template Cpp、STL。

### 数据类型与变量常量
- 基本数据类型：`bool`, `char`, `int`, `float`, `double`, `void`, `wchar_t`. (`bool = true, false`)
- 尽管Cpp中可以像C一样定义常量，但是在Cpp中推荐使用const关键字定义常量。
- Cpp中的存储类定义：`auto`, `register`, `static`, `extern`, `mutable`, `thread_local`.
  - `auto` 可以自动推定类型。
  - `static` 的作用与C中的相同，特别的在类中使用 `static` 会使该成员成为对象间共享的成员。
  - `thread_local` 仅可在线程上访问。
- 派生数据类型：数组，指针，引用，函数，结构体，对象。
  - Cpp 11中增加了 `nullptr` 作为空指针。
  - 引用必须在创建时初始化，一旦初始化就不能再指向另一个对象。
  - 结构体和对象的区别：结构体没有对访问权限的控制，全部都是public；而class中默认为private。
- 尽量避免使用显示强制类型转换。
  - `static_cast<type>(var)`：基本的强制类型转换。
  - `const_cast<type>(var)`：转换为常量对象。
  - `reinterpret_cast<type>(var)`：为对象的位模式重新解释。


### 字符串与向量
- 不推荐使用C风格字符串，而是使用 string 类。
- string 对象上的操作
  ```cpp
  // 使用 >> str 读取时，会自动忽略开头的空白，在下一次遇到空白时结束。如果需要读取一整行，使用getline
  while (cin >> word) {} // 读取未知数量的string对象
  while (getline(cin, line)) {} // 读取位置数量的line

  str.empty();
  str.size(); // 返回 string::size_type
  str.c_str();
  ```
- vector 的初始化和成员
  ```cpp
  vector<int> ivec(10, 1); // length = 10, all value = 1
  vector<int> ivec{1, 2, 3, 4, 5};

  v.empty();
  v.size();
  v.push_back(value);
  for (auto iter = v.begin(); iter != v.end(); ++iter) {cout << *iter;}
  // Cpp 11 增加了常量iterator，使用 cbegin(), cend() 处理只读对象
  ```

### 流程控制
- 范围for循环
  ```cpp
  int array[5] = {1, 2, 3, 4, 5};
  for (auto &x : array) {
      ... // 这里使用的元素的引用
  }
  ```
- 异常处理的语句
  ```cpp
  // 抛出一种类型的异常
  throw runtime_error("error message");
  // 异常处理
  try { ... }
  catch (error_type) { handle_statements }
  catch (another_error_type) { handle_statements }
  ```
- 调试帮助
  ```cpp
  #define NDEBUG // 关闭所有的assert语句
  assert(expr);
  ```

### 函数
- 当使用数组作为参数时，主要使用数组指针作为参数，可以仿照标准库的做法：`void function_name(const int *beg, const int *end)`.
- 函数参数的传递，与C相比增加了引用调用，使用中推荐使用常量引用保护参数不被随意修改。内置数据类型使用传值比传引用更高效，自定义类型使用传引用更高效。（const reference）
- 可以定义返回引用的函数，返回引用的函数还可被赋值。但不能返回局部变量的引用；也不能返回函数内部new分配的内存的引用。
  ```cpp
  char &get_val(string &str, string::size_type ix) {
      return str[ix];
  }
  int main() {
      string s("hello");
      get_val(s, 0) = 'H'; // 函数调用作为左值
  }
  ```
- 函数指针与C类似，在Cpp中当把一个函数名当作一个值使用时，该函数自动转换为指针。因此当一个函数名作为另一个函数的参数时，实际是其函数指针作为参数。
- Cpp 11中的函数可以返回一个花括号围起来的列表。
- 函数重载。
- 默认实参的位置建议放在头文件中，且不能对同一个参数多次设置默认实参。
- 内联函数，在函数定义前加inline即可，不要与lambda函数和函数指针混淆。内联函数只是告知编译器此函数为内联函数，但是编译器可能不会将其以内联函数对待。内联函数应在头文件中定义。
- Lambda函数（匿名函数）
  ```cpp
  auto log = []{cout << "this is a log text" << endl;};
  auto less = [](int a, int b) -> bool {return a < b;};
  sort(int *array, int length, [](int a, int b){return a < b;});
  ```

### 面向对象
- 类的属性可以指定初始值，这种指定在该属性被声明时。
  ```cpp
  class Obj {
      int age = 0;
  }
  ```
- const修饰的成员函数
  ```cpp
  Object::read(unsigned int ix) const {} // 无法改变对象的属性，除非是mutable
  Object::write(unsiged int ix, float val) {} // 可以改变对象的属性
  ```
- 构造函数、拷贝构造函数、析构函数
  ```cpp
  class Sales_data {
  public:
      Sales_data(string s, unsigned cnt, double price) :
              bookNo(s), units_sold(cnt), revenue(cnt*price) { }
      Sales_data(): Sales_data("", 0, 0) { } // 委托构造函数
  }
  ```
- 友元 firend。
  ```cpp
  class A {
      friend class B; // B的成员可以对A的私有属性操作，但是两者没有包含关系
      friend void clear(); // 函数clear可以对A的私有属性操作，但是clear不是A的成员。
  }
  ```

### 模块
- 在头文件中不用使用 using namespace xxx

## Part II 标准库

- 继承自C的标准库：cctype、cmath、ctime、cstdlib




