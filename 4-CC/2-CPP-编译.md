# c++ 编译

## gcc/g++ 命令

gcc/g++ 是 linux 下常用的 c/c++的编译器，关于 gcc 是什么、gcc 的历史等内容，可以参考这篇[GCC 编译器 30 分钟入门教程](http://c.biancheng.net/gcc/)或维基。需要注意的是，g++与 gcc 并不是两个相互独立的编译指令，gcc 是通用编译指令， 也可以编译 c++程序，而 g++只能编译 c++程序，并且会链接 c++的标准库，c++代码推荐使用 g++指令。

对于 c 或 c++源文件较少的项目，可以直接使用 gcc 命令进行编译，对于源文件较多的项目，更推荐使用编译控制工具如 make、CMake。

gcc 的编译过程有以下 4 步：

- 进行源文件的预处理，生成`.i`文件；
- 将`.i`文件编译成汇编语言，生成`.s`文件；
- 汇编，生成目标文件`.o`文件；
- 将多个`.o`文件链接为最终的可执行文件或库文件。

### 常用 gcc/g++命令参数

编译单个源文件，生成可执行程序

```bash
$ g++ source.cpp    # 默认生成 a.out
$ g++ source.cpp -o single
```

编译多个源文件，生成可执行程序

```bash
$ g++ source-1.cpp source-2.cpp -o main
```

只完成预编译，即只完成第 1 步

```bash
$ g++ -E source.cpp
```

只完成生成汇编语言，即完成前 2 步

```bash
$ g++ -S source.cpp
```

生成目标文件但不进行链接，即完成前 3 步

```bash
$ g++ -c source.cpp
```

创建静态库

```bash
$ g++ -c source-1.cpp source-2.cpp
$ ar rcs libsource.a source-1.o source-2.o
# ar命令是用来生成archive文件的指令，静态库就是archive文件
# r 替换或添加目标文件； c 不管是否存在都创建；
# s 创建目标文件索引，在较大的库时能够提高速度。

# 注意使用库还需要对应的头文件
# 使用静态库
$ g++ uselib.cpp libsource.a -o use
```

创建动态库

```bash
$ g++ -shared -fPIC source.cpp -o libsource.so
# 使用动态库
$ g++ uselib.cpp libsource.so -o use
# 动态链接库需要在特定位置才能执行程序
```

链接其他位置的库

```bash
# 链接 /dir/lib/ 处的 libsource.a(so) 库
$ g++ uselib.cpp -L /dir/lib -lsource
```

指定额外的头文件

```bash
# 使用 /dir/include/ 处的头文件
$ g++ source.cpp -I /dir/include
```

在编译的同时产生调试信息，搭配 gdb 工具使用

```bash
$ g++ -g source.cpp
```

控制警告信息

```bash
$ g++ -Wall source.cpp  # 发出所用警告
$ g++ -w source.cpp     # 关闭警告
```

设置 c++的标准

```bash
$ g++ -std=c++11 source.cpp
# 其他的选项如 c++98 c++03 c++14 c++17
```

禁止使用动态库

```bash
$ g++ source.cpp -static
# 默认会尽量使用动态库
```

优化选项

```bash
$ g++ source.cpp -O0
# -O0 没有优化
# -O1 默认选项
# -O2
# -O3 优化级别最高
```

## gdb 调试器

在 linux 下开发 c++程序，可能会使用到 gdb 调试器，尤其是在某些无法使用 IDE 的情形下，可以直接使用 gdb 进行调试。
使用 gdb 调试程序前，需要使用特定的参数编译 c++程序，然后就可以使用 gdb 指令进入调试环境

```bash
$ g++ -g source.cpp -o source # -g 参数用来生成调试用的信息
$ gdb source  # 进入调试环境
```

下面介绍一些常用的调试指令

```bash
(gdb) l     # list       列出源文件的内容
(gdb) b 5   # breakpoint 设置断点，在第5行
(gdb) r     # run        执行到断点处
(gdb) p var # print      打印变量的值
(gdb) n     # next       单步调试
(gdb) c     # continue   继续执行
(gdb) q     # quit       退出调试
```

## clang 命令

clang 也是 c/c++等多种语言的编译器，是 gcc 的替代品，提供更好的错误提示。在对 Apple 公司使用的 Object-c 有更好的支持，是 MacOS 下 XCode 的默认编译器。clang 命令与 gcc/g++命令的基本相同，在 linux 系统下安装方法如下

```bash
$ sudo apt install llvm
$ sudo apt install clang
```

可以将系统的默认编译器替换为 clang

```bash
# change default compiler to clang
# run these command and choose the clang
$ sudo update-alternatives --config cc
$ sudo update-alternatives --config c++
```
