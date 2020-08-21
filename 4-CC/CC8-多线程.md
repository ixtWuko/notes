# C++ 多线程

## 线程
线程使用 thread 建立，建立后立即运行。
```c++
#include <thread>
void back_task(args) {}
std::thread t(back_task, args);
// or
class back_task_obj {
    members;
    back_task_obj(_members) : membars(_members) {}
    void operator()(args) {}
};
back_task_obj fo(members);
std::thread to1(fo, args);
std::thread to2(std::ref(fo), args);
std::thread to3{func_obj(members), args};

// 等待线程运行结束
t.join();
// 不等待线程运行结束
t.detach();
```
制作符合 RAII 的 thread_guard, 保证线程在出作用域是结束。
```c++
class thread_guard {
    std::thread& t;
public:
    explicit thread_guard(std::thread& _t) : t(_t) {}
    ~thread_guard() { if (t.joinable) t.join(); }
    // 不允许拷贝
    thread_guard(const thread_guard& _) = delete;
    thread_guard& operator=(const thread_guard& _) = delete;
};
```

## 互斥
使用 mutex 实现资源访问的互斥。mutex 可以在全局作用域中声明，优势是可以直接在函数或者仿函数中使用；或者在 main 中声明，使用指针传入函数和仿函数。mutex 不允许拷贝和移动，不能使用引用传入。
我更倾向于使用在 main 中声明 mutex ，看起来会干净一些，注意不要产生悬垂指针。
```c++
void func(args, std::mutex* m) {
    // 临界区
    {
        std::lock_guard<std::mutex> lock(*m); // 不要忘记解引用
        do_something();
    } // 出作用域时锁会失效，因为 lock 析构了
}

std::mutex m;
std::thread t(func, args, &m);
```
mutex 的类型：
- mutex 独占资源，同时只允许一个线程读写；
- recursive_mutex 递归锁，满足函数相互调用时的锁设置；
- shared_mutex 允许多个读者，但只允许一个写者。

这三种互斥都有带时间后缀的，可以设置与时间相关的功能。

guard 的类型
- lock_guard 立即锁定，至析构时解锁；
- unique_lock 不立即锁定，需要使用 lock() 进行锁定，适合与条件量共同使用；
- scoped_lock 17中加入，可以放入多个互斥量，能够避免死锁。

## 同步
使用 condition_variable 实现线程的同步。
