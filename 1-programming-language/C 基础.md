# C 基础内容

## Part I : 基础

一个 C 程序是由函数和数据构成的。大概包括以下内容：

- 各种数据类型的常量与变量
- 运算符
- 执行结构：顺序、条件、循环
- 函数
- I/O
- 预处理器


### 数据类型

- 基本类型：`char`, `int`, `short`, `long`, `float`, `double`, `long double`。前4个整形都可以加 `unsigned` 修饰。\
  整形默认为十进制，以 `0` 开头的为八进制、以 `0x` 开头的为十六进制，以 `0b` 开头的为二进制。添加 `u` 尾缀的是无符号，添加 `l` 尾缀的是长整形。\
  浮点数默认为双精度，添加 `f` 尾缀的是单精度浮点数。
- `Void` 类型。
- 枚举类型
  ```c
  enum Day {
      MON = 1, TUE, WED, THU, FRI, SAT, SUN
  }; // value 默认从 0 开始，这里根据需要指定 value 从 1 开始。

  enum Day first_day = SUN; // 可以将 enum Day 当作数据类型名称看待。
  ```
- 派生类型：指针、数组、字符串、结构体、共用体、函数。


### 变量与常量
- 变量的声明中需要注意 `extern` 的用法。
  ```c
  int a;          // 声明的同时定义
  extern int a;   // 只声明，并未定义。对所有的源文件都可见。
  
  // 定义指为该变量指派存储空间
  ```
- 常量的声明有两种方法。
  ```c
  // 使用预处理器
  #define WIDTH 800
  #define HEIGHT 600
  // 使用const
  const int LENGTH = 100;
  ```
- `static` 关键字修饰的函数内局部变量，在函数首次被调用时初始化，在函数执行结束后保持活性，因此可以在函数的每次调用之间传递数据。\
  `static` 修饰全局变量，作用域限制在声明它的文件内部。而 `extern` 修饰的全局变量，作用域会延伸到文件外部。
- 强制类型转换，`(int)price` 将返回一个整形。


### 运算符

-   |       |                                                 |
    | :---: | :---------------------------------------------- |
    | 算数  | `+`  &nbsp;&nbsp;`-`  &nbsp;&nbsp;`*`  &nbsp;&nbsp;`/`  &nbsp;&nbsp;`%`  &nbsp;&nbsp;`++`  &nbsp;&nbsp;`--` |
    | 比较  | `>`  &nbsp;&nbsp;`>=`  &nbsp;&nbsp;`<`  &nbsp;&nbsp;`<=`  &nbsp;&nbsp;`==`  &nbsp;&nbsp;`!=`      |
    | 位    | `&`  &nbsp;&nbsp;`|`  &nbsp;&nbsp;`^`  &nbsp;&nbsp;`~`  &nbsp;&nbsp;`<<`  &nbsp;&nbsp;`>>`        |
    | 逻辑  | `&&`  &nbsp;&nbsp;`||`  &nbsp;&nbsp;`!`                             |
    | 指针  | `&`  &nbsp;&nbsp;`*`  &nbsp;&nbsp;`.`  &nbsp;&nbsp;`->`                       |
    | 其它  | `opt=`  &nbsp;&nbsp;`,`  &nbsp;&nbsp;`sizeof()`                     |
    |       |                                                 |

- 移位运算左移时右侧补0.
- 三元运算符：`condition ? expression : opposite_expression`


### 执行结构
- `a > b ? a : b`
- `if (condition) ... else if (another condition) ... else ...`
- `while (condition) ...`
- `do ... while (condition)`
- `for ( ; ; ) ...`
- `switch (cases) case a: ... case b: ... default: ...`
- `break`
- `continue`


### 派生数据类型
- `pointer`：指针中的空指针 `NULL`，可以用于条件判断。
- `array`
  ```c
  int prime_numbers[] = {2, 3, 5, 7, 11, 13, 17, 19};
  int square_numbers[10]; // 此时已经为其分配了存储空间，之后无法使用{}进行初始化，可使用循环进行赋值。
  ```
- `string`：本质是一个以`\0`结尾的字符数组，对字符串操作的函数都在标准库文件`string.h`中。
- `struct`
  ```c
  // 推荐的写法
  typedef struct _book_info {
      int id;
      char title[128];
      char author[128];
      struct _book_info *next;
  } Book;
  Book last_book = {50, "The c programming language", "K&R", NULL};

  // 位域：以不足一字节的长度保存一个变量。
  typedef struct _flag {
      unsigned int is_key:1;       // 取1位二进制位作为该成员
      unsigned int :4              // 空闲4位
      unsigned int value_type:3;   // 取3位二进制表示值的类型
  } Flag;
  ```
- `union` ：与结构体类似，但是其成员变量只能同时使用一个。
    ```c
    // 推荐的写法
    typedef union _identify {
        int id;
        char name[128];    // 每个union变量的空间占用等于占用最大的变量的大小，因此由此union生成的变量大小为128字节。
    } Identify；
    Identify first_man; //该变量的两个成员只能同时使用一个，会相互覆盖
    ```

### 函数
- 函数参数可以传值，也可以传指针。尽管函数不应改变参数的值，但是在C程序的函数中，由于无法返回复杂的数据类型，或者处于节省计算资源的需要，会对参数的值进行修改。
- 函数可以有返回值，也可以无返回值；可以返回值或返回指针。
- 结构体和指向结构体的指针，可以作为函数参数，也可以作为函数的返回值。
- 指向函数的指针
    ```c
    int (*cmp) (int a, int b) {
        return a - b;
    }
    // 调用
    int result = (*cmp) (a, b);

    // 回调函数（函数没有实现，只说明回调的形式）
    void init_array(int *array, size_t array_length, int (*generator)(void));
    int random_value();
    int main(void) {
        int a[10];
        init_array(a, 10, random_value);
    }

    // 带有参数时的回调函数
    void sort(int *array, size_t array_length, int (*cmp)(int, int));
    int less(int a, int b);
    int main(void) {
        int a[10] = {...};
        sort(a, 10, less);
    }
    ```


### 预处理器
- 使用预处理器主要控制编译过程，在C中的功能比较琐碎。
    ```c
    #include <stdio.h>

    #undef MAX_INDEX
    #define MAX_INDEX 100 // 也可以定义类似函数的东西
    #ifdef MAX_INDEX // 如果有定义则返回真
    #ifndef MAX_INDEX // 如果没有定义则返回真

    #if
    #else
    #elif
    #endif

    #ifndef _SAMPLE_H_
    #define _SAMPLE_H_
    #endif // _SMAPLE_H_

    // `\` 宏延续运算符，如果一行容纳不下，可以使用 `\` 另起一行
    // `#` 字符串常量化运算符，如下
    #define message_for(a, b) printf(#a " and " #b ": we love you!\n")
    int main () {
        message_for(Carole, Debra);
    }
    // output
    Carole and Debra: we love you!

    // `##` 标记粘贴运算符，合并两个参数为一个，如下
    #define tokenpaster(n) printf("token" #n " = %d ", token##n)
    int main () {
        int token34 = 40;
        tokenpaster(34);
    }
    // output
    token34 = 40
    // 尽管有这样的能力，但是代码会造成阅读困难，尽量不使用。
    ```


## Part II : 标准库

**以下主要记录了常用的，并不是全部的标准库内容**

### ctype.h

```c
int isalpha(int c); // 是否为字母
int islower(int c); // 是否为小写字母
int isupper(int c); // 是否为大写字母
int isdigit(int c); // 是否为十进制数字
int isxdigit(int c); // 是否为十六进制数字
int isalnum(int c); // 是否为字母或数字

int ispunct(int c); // 是否为标点符号，!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
int isgraph(int c); // 是否有图形表示法，包含字母、数字、标点符号
int isspace(int c); // 是否为空白字符，包含空格和制表符
int isprint(int c); // 是否可打印，包含字母、数字、标点符号、空格字符。空格字符包含制表符、换行符、垂直制表符、换页符、回车符、空格。
int iscntrl(int c); // 是否为控制字符，000~037、177

int tolower(int c); // 将大写字母转换为小写字母
int toupper(int c); // 将小写字母转换为大写字母
```

### string.h

```c
size_t strlen(char *s); // 返回字符串的长度

char *strcat(char *s1, char *s2); // 连接字符串 s2 到字符串 s1 的末尾
char *strncat(char *s1, char *s2, size_t n); // 连接字符串 s2 的前 n 个字符到字符串 s1 的末尾
char *strcpy(char *s1, char *s2); // 复制 s2 到 s1 
char *strncpy(char *s1, char *s2, size_t n); // 复制 s2 的前 n 个字符到 s1

int strcmp(char *s1, char *s2); // 比较两个字符串，相等时返回0
int strncmp(char *s1, char *s2, size_t n); // 比较两个字符串的前 n 个字节。

char *strchr(char *s, int c); // 返回在字符串中第一次出现字符 c 的地址（指针）， 否则返回 NULL
char *strrchr(char *s, int c); // 返回在字符串中最后一次出现字符 c 的地址（指针）， 否则返回 NULL
char *strstr(char *s1, char *s2); // 返回字符串 s2 在字符串 s1 中第一次出现的地址（指针）， 否则返回 NULL
```

### math.h 与 limits.h, float.h

```c
// math 中包含一些数学工具
double sin(double), double cos(double), double tan(double);
double asin(double), double acos(double), double atan(double);
double atan2(double y, double x); // 返回 y/x 的反正切
double sinh(double), double cosh(double), double tanh(double);

double exp(double), double pow(double x, double y), float powf(float x, float y);
double sqrt(double);
double log(double), double log10(double);

double ceil(double), double floor(double);
int abs(int), double fabs(double), double cabs(struct complex znum);

double modf(double x, double *integer); // 返回小数部分，整数部分存入指针 integer 指向的变量
double fmod(double x, double y); // 返回两数相除的余数（商为整数时的余数）

// limits 中包含整形所能表示数据的边界
CHAR_MAX, CHAR_MIN
INT_MAX, INT_MIN
// float 中包含浮点数所能表示数据的边界
FLT_MAX, FLT_MIN
DBL_MAX, DBL_MIN
```

### stdlib.h

```c
int atoi(char *s); // 将一个字符串转换为整数
char *itoa(int n, char *str, int radix); // radix 为进制
double atof(char *s); // 将一个字符串转换为浮点数 double
long int atol(char *s); // 将一个字符串转换为长整形
double strtod(char *s, char **endp); // 将一个字符串转换为单精度浮点数，检查是否溢出，将未转换部分的指针保存在 *endp 中
long strtol(char *s, char **endp, int base); // 将一个字符串转换为长整形，检查是否溢出，将为转换部分的指针保存在 *endp 中，base 为转换使用的进制

// 数学相关
int abs(int);
long int labs(long int);
// 数学相关的两个随机函数
int rand(void); // 产生一个 0~RAND_MAX 之间的伪随机数
void srand(unsigned int seed); // 将 seed 作为生成新的伪随机数序列的种子数。

// 搜索与排序
void *bsearch(void *key, void *base, size_t n, size_t size, int (*cmp)(void *keyval, void *datum)); // 在 base[0] ... base[n-1] 之间查找 *key 的匹配，函数 cmp 中如果 *keyval < *datum ，返回负值，相等返回零，否则返回正值。bsearch 返回一个指向匹配项的指针 or NULL
void qsort(void *base, size_t n, size_t size, int (*cmp)(void *, void *)); // 排序，与上面的搜索类似

// 内存
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void ptr);

// 程序终止
void abort(void); // 异常终止
void exit(int status); // 正常终止
exit(0);

// 系统控制
int system(char *s); // 将字符串作为命令传递给执行环境，如果字符串为空，则判断外部环境是否有命令解释器
char *getenv(char *name); // 获得与 name 相关的环境变量，如果不存在返回 NULL
```

### stdarg.h
该头文件可以实现参数数目未知的函数。
```c
// 参数可变的函数
double average(int num, ...) {
    va_list varlist; // 该变量用来保存参数中...位置传入的所有参数
    double sum = 0.0;
    int i;

    va_start(varlist, num); // 为num个参数初始化varlist
    for (int i=0; i < num; ++i) {
        sum += va_arg(varlist, int); // 依次访问参数，有点类似迭代器
    }
    va_end(varlist); // 清理内存
    return sum / num;
}
```

### stdio.h

标准文件： `stdin`, `stdout`, `stderr` 。linux 中的一切皆为文件，默认的stdin为键盘，默认的stdout为屏幕。

#### 文件操作

```c
FILE *fopen(char *filename, char *mode); // mode 的值有 'r' 'w' 'a' 'r+' 'w+' 'a+'
FILE *f = fopen(filename, mode);

FILE *freopen(char *filename, char *mode, FILE *stream); // 打开文件的同时将其关联到指定的 stream 流，常用于改变与 stdin、stdout、stderr 相关的文件，读入时选择stdin，输出时选择stdout

int fflush(FILE *stream); // 将已写入缓冲区但尚未写入文件的数据写入文件，错误返回 EOF，否则返回0。fflush(NULL) 将清洗所有的输出流
int fclose(FILE *stream); // 将未写入的数据写入流，释放缓冲区，然后关闭流，错误返回 EOF，否则返回0

int remove(char *filename); // 删除指定的文件，错误返回非0值
int rename(char *oldname, char *newname); // 重命名文件，错误返回非0值
FILE *tmpfile(void); // 创建临时文件，程序结束时自动删除。创建失败返回 NULL
char *tmpnam(char s[]); // 生成一个唯一的名字，作为该函数的返回值，同时保存在数组 s 中
```

#### 输入输出

1. 定位

```c
int fseek(FILE *stream, long offset, int origin); // 设置流的位置，后续的读写将从新位置开始。对于二进制文件，位置被设置在 origin 开始的第 offset 个字符处， 对于文本流，offset 必须设置为0，或者 ftell 的返回值。fseed 错误时返回非0值。
long ftell(FILE *stream); // 返回 stream 流的当前位置，错误返回 -1L
int fgetpos(FILE *stream, fpos_t *ptr); // 把 stream 流的当前位置保存在 *ptr 中，错误返回一个非0值
int fsetpos(FILE *stream, fpos_t *ptr); // 把 stream 流的位置设置为 *ptr，中的位置，错误返回非0值
void rewind(fp); // 设置文件位置到开头
```

2. 二进制输入输出

```c
size_t fread(void *ptr, size_t size, size_t nobj, FILE *stream); // 从 stream 流中读取最多 nobj 个长度为 size 的对象，保存在 ptr 指向的数组中。
size_t fwrite(void *ptr, size_t size, size_t nobj, FILE *stream); // 从 ptr 指向的数组中读取 nobj 个长度为 size 的对象，输出到 stream 流中
```

3. 非格式化输入输出

```c
int fgetc(FILE *stream); // 返回 stream 流中的下一个字符，末尾或者错误返回 EOF
char *fgets(char *s, int n, FILE *stream); // 最多将 n-1 个字符读入到数组 s 中，以 '\0' 结尾，末尾或者错误返回 NULL
int fputc(int c, FILE *stream); // 将字符 c 写入 stream 流中，错误返回 EOF
int fputs(char *s, FILE *stream); // 将字符串 s 输出到 stream 中，不含 '\n' ，错误返回 EOF
int getc(FILE *stream); // 等价于 fgetc
int putc(int c, FILE *stream); // 等价于 fputc

int getchar(void); // 等价于 getc(stdin)
char *gets(char *s); // 把下一行输入读入 s 中，末尾的换行符用 '\0' 替换，错误返回 NULL
int putchar(int c); // 等价于 putc(c, stdout)
int puts(char *s); // 把 s 和一个换行符输出到 stdout 中，错误返回 EOF

ing ungetc(int c, FILE *stream; //  把字符 c 推入到指定的流 stream 中，以便它是下一个被读取到的字符。错误返回 EOF
```

4. 格式化输入输出

```c
int fprintf(FILE *stream, char *format, ...); // 按照格式输入到 stream 流中
int printf(char *format, ...); 
int sprintf(char *s, char *format, ...); // 按照格式输入到字符串 s 中，并以 '\0' 结束

int fscanf(FILE *stream, char *format, ...); // 按照格式从 stream 流中读取
int scanf(char *format, ...);
int sscanf(char *s, char *format, ...); // 按照格式从字符串 s 中读取

/******* 一些格式标记
- 指定被转换的参数在其字段内左对齐
+ 指定在输出的数前面加上正负号
o 八进制
x 十六进制
e 指数形式
g 自动选择 f 或者 e
*******/
```

### time.h
```c
clock_t clock(void); // 从程序开始计时的时间
time_t time(time_t *seconds); // 计算从19701010 000000UTC开始经历的时间，以秒计。同时返回和存储在seconds中

char *ctime(const time_t *timer); // 返回一个表示时间的字符串，格式为 Mon Aug 1 20:26:14 2019
struct tm *gmtime(const time_t *timer); // 将timer表示的时间分解成tm结构，tm结构包含年月日时分秒、周几、一年中第几天
struct tm *localtime(const time_t timer); // 功能与gmtime相同，只是时区改为本地时区
char *asctime(const struct tm *timeptr); // 功能与ctime相同，只是参数不同

double difftime(time_t time1, time_t time2); // 单位为秒
``` 