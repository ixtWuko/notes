# C 技巧

### 命令行参数
```c
int main(int argc, char *argv[]) {
    ...
}
// 当使用命令行工具时，会自动生成argc和argv两个变量，其中argc保存参数的数量，argv[0]存储程序名称，argv[1]保存指向第一个参数字符串的指针，以此类推。
```


### 程序计时
```c
#include <time.h>

start_time = clock();
// your program here
end_time = clock();
printf("This program cost %fs.\n", (end_time - start_time) / CLOCKS_PER_SEC);
```

### 使用随机数
```c
#include <time.h>
#include <stdlib.h>

// 获得 [floor, ceil] 之间的随机数
srand((unsigned)time(NULL));
int random_value = rand() / (ceil - floor) + floor;
```

### 结构体指定初始化
```c
static struct usb_driver usb_storage_driver = {
    .owner = THIS_MODULE,
    .name = "usb-storage",
    .probe = storage_probe,
    .disconnect = storage_disconnect,
    .id_table = storage_usb_ids,
};
```

### 字符串分割
```c
char *strtok(char *s, char *delim); // 以 delim 中的字符为分隔符，将字符串分割

/* strtok example */
int main () {
    char str[] = "- This, a sample string.";
    char *token;
    printf("Splitting string \"%s\" into tokens:\n", str);
    token = strtok(str, " ,.-");
    while (token != NULL) {
        printf ("%s\n",token);
        token = strtok (NULL, " ,.-"); // 这里参数 NULL 会使得 strtok 函数继续之前的字符串
    }
    return 0;
}
/* output */
Splitting string "- This, a sample string." into tokens:
This
a
sample
string
```

### C语言的面向对象
```c
// C语言的面向对象是使用函数指针实现的，就是在结构体中设置函数指针作为其成员。
typedef struct list {
    struct list *_this;
    void (*insert)(void *node);
    void (*drop)(void *node);
    void (*clear)(void);
    void (*get)(int index);
} List;

List *list = NULL; // 在下面函数的实现中需要使用list变量
void insert(void *node);
void drop(void *node);
void clear(void);
void *get(int index);

// 指定一个构造函数
List *ListConstruction() {
    list = (List*)malloc(sizeof(List));
    list->insert = insert;
    list->drop = drop;
    list->clear = clear;
    list->get = get;
    list->_this = list;
    return (List*)list;
}
```