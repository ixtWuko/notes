# 如何写 makefile

对于源文件较多的 c/c++项目，直接在 shell 中使用 gcc/clang 进行编译会十分麻烦，makefile 可以解决这一问题。Makefile 记录了项目的编译规则，当使用 make 命令进行项目的编译时，make 命令会使用 makefile 中记录的规则，一步步地编译、链接，生成目标程序；同时已经 make 过的项目再次 make 时，只会重新编译发生修改过的源文件。这些特性都能够节省编译时间。

makefile 文件包含五种成分：显式规则、隐晦规则、变量定义、文件指示、注释。其中隐晦规则指 make 命令能够自动推导的命令，可以省略规则中的某些元素；文件指示指 makefile 引用其它 makefile，或者指定使用 makefile 哪一部分的规则。一个 makefile 的基本成分如下所示：

```makefile
target : prerequisites
    command
# target 为该步骤的目标，可以是目标文件、执行文件、标签
# prerequisites 为目标所依赖的成分，可以是源文件、目标文件、标签
# command 为生成上述目标所进行的shell命令
# 目标 : 依赖
#     shell命令
```

### 注释

makefile 中使用 `#` 来标记注释。

### 显示规则

下面是一个 makefile 文件的例子。

```makefile
# 使用 main.cpp, a.cpp, b.cpp, c.cpp 生成目标程序 main
# ---------------------
main : main.o a.o b.o c.o
    c++ -o main main.o a.o b.o c.o
main.o : main.cpp
    c++ -c main.cpp
a.o : a.cpp
    c++ -c a.cpp
b.o : b.cpp
    c++ -c b.cpp
c.o : c.cpp
    c++ -c c.cpp

.PHOMY : clean    # 声明 clean 为一个伪目标
clean :           # 没有依赖的规则，make命令不会自动执行，需要使用形如 make clean 这样的形式才能执行
    rm main *.o
# --------------------
```

下面是 makefile 中生成规则的一些细节：

- 通过比较目标与它的依赖间修改时间的差异，只要依赖中有比目标新的文件，就重新生成目标。
- 在一条规则中，可以有多个目标，使用空格分割；可以有多条 shell 命令。
- 多条 shell 命令可以放入多行，此时 shell 命令会放入不同的进程执行；如果后面 shell 命令依赖前面 shell 命令的效果，则两条 shell 命令使用 `;` 分割。`\` 可以折行。
- make 命令默认将每一条 shell 命令打印出来，如果不想打印命令，在 shell 命令前加 `@`。
  如果不要求 make 检查 shell 命令的执行是否正确，在其前加 `-`。
- makefile 中可以使用的通配符与 shell 中相同，`*` `?`；也使用 `~` 指代用户文件夹。

上述例子为生成执行程序的规则，下面介绍生产静态库(Archive File)的规则：

```makefile
name_of_lib(a.o) a.o
    ar rc name_of_lib a.o
```

### 使用变量

makefile 文件中的变量，类似于 c 文件中的宏定义，起替换文本的作用。下面是一个使用变量的例子。

```makefile
objects = main.o a.o b.o c.o

main : $(object)
    c++ -o main $(object)
```

使用变量时的四种赋值运算符：

- `x = $(y)` 懒求值，在运行时求值；
- `x := $(y)` 立即求值，在定义时求值；
- `x ?= $(y)` 只有当 x 不存在时才定义 x；
- `x += $(y)` 追加。

上述四种运算符中的前两种比较容易让人产生迷惑，下面以一个例子说明其差别：

```makefile
# 使用 =
x = hello
y = $(x) world
echo $(y) # -> hello world

x = hi
echo $(y) # -> hi world

# 使用 :=
x = hello
y := $(x) world
# 立即求值，在这里已经将 y 中的 $(x) 替换了，后面 x 的变化不会影响 y
echo $(y) # -> hello world

x = hi
echo $(y) # -> hello world
```

赋值运算符另一个需要注意的地方是：不要在赋值语句的后面添加注释，因为注释前的空格会添加到变量里面，产生不可预期的结果。

变量的高级用法——变量值替换

```makefile
sources = a.cpp b.cpp c.cpp
objects = $(sources:%.cpp=%.o)
```

#### 内置变量

```makefile
$(AR)    # 生产 archive 文件的默认程序 ar
$(CC)    # 编译 C 代码的默认编译器 cc
$(CXX)   # 编译 C++ 代码的默认编译器 g++

$(ARFLAGS)   # ar 的参数 'rv'
$(CFLAGS)    # 编译 C 代码的参数
$(CXXFLAGS)  # 编译 C++ 代码的参数
$(CPPFLAGS)  # C 代码预编译的参数
```

#### 条件

```makefile
objects = main.o a.o b.o c.o

main : objects
ifeq ($(CXX), g++) # 这里的 $(CXX) 是内置变量
    $(CXX) -o main $(objects) $(libs_for_g++)
else
    $(CXX) -o main $(objects) $(normal_libs)
endif

# 其他的 ifneq, ifdef var_name, ifndef var_name
```

#### 函数

```makefile
# (function arguments)
$(wildcard src/*.cpp)             # 通配符匹配的部分
$(subst .cpp,.o,$(sources))       # 字符串替换
$(patsubst %.cpp,%.o,$(sources))  # 模式字符串替换
$(strip $(string))                # 去掉字符串开头和结尾的空格

$(dir src/foo.c)         # 取文件目录，得到 src/
$(notdir src/foo.c)      # 取文件名，得到 foo.c
$(suffix src/foo.c)      # 取尾缀，得到 .c
$(basename src/foo.c)    # 取前缀，得到 src/foo
$(addsuffix .c,src/foo)  # 加尾缀，得到 src/foo.c
$(addprefix src/,foo.c)  # 加前缀，得到 src/foo.c

$(foreach n,$(names),$(n).o)  # 循环，将 names 中的每一个都添加 .o
$(shell cat foo)              # 执行 shell 命令

$(warning "test")
$(error "test")
```

### 隐晦规则

一些在 makefile 经常用到的规则，make 会为我们自动生成。下面是一些常用的隐含规则：

- 编译 C 代码：自动将 name.c 生成 name.o，生成命令为 `$(CC) -c $(CPPFLLAGS) $(CFLAGS)` 。

- 编译 C++ 代码：自动将 name.cc 生产 name.o，生成命令为 `$(CXX) -c $(CPPFLAGS) $(CXXFLAGS)` 。

- 链接 Object 文件：自动将一个或多个 Object 文件链接成执行文件。如 `main : main.o a.o` ，将会执行下面的命令：

  ```makefile
  cc -c main.c -o main.o
  cc -c a.c -o a.o
  cc main.o a.o -o main
  rm -f main.o
  rm -f a.o
  ```

- 生产静态库的规则也可以自动推导，如 `name_of_lib(a.o b.o)` 将会执行下面的命令：

  ```makefile
  cc -c a.c -o a.o
  cc -c b.c -o b.o
  ar r name_of_lib.a a.o b.o
  rm -f a.o
  rm -f b.o
  ```

#### 使用模式规则

`%` 在 makefile 中表示任意长度的非空字符串，模式规则指使用 `%` 定义的规则，可以达到一条规则处理多个目标的目的。下面以例子说明模式规则以及自动变量的用法：

```makefile
# 将所有的 .cpp 文件编译成对应的 .o 文件
%.o : %.cpp
    $(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@
# $@ 为当前目标，$< 为当前第1个依赖，这两个为自动变量。
# 类似于迭代器，每次会取一个目标和依赖执行命令，将所有符合模式的文件全部迭代。
```

总结一下常用的自动变量：

```makefile
$@    # 目标
$<    # 第1个依赖
$?    # 比目标新的依赖
$^    # 所有依赖，会去除重复的
$+    # 所以依赖，不会去除重复的
$*    # 模式匹配到的部分，即 % 代表的部分
$(@D) $(@F)    # $@ 的目录名和文件名
# 其他的自动变量也可以构造类似的，获得目录名和文件名
```

### 文件指示

文件指示指在 makefile 中引用其他的 makefile 文件。

```makefile
include foo.make *.make  # 引用其他的 makefile
```

### make 命令

在 make 命令使用中经常看到的 all、clean、install、test 等，都是伪目标，需要在 makefile 中制定这些伪目标所要求的行为。

make 命令的常用参数：

```bash
-f filename     # 指定makefile文件
-I include_dir  # 在该目录下搜索 makefile
-j jobnum       # 指定 job 数量，默认 make会运行尽量多的 job
```
