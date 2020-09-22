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

其它的常用函数

```c++
t.get_id();
std::this_thread::get_id();
std::this_thread::sleep_for(std::chrono::millisecond(100));
std::this_thread::sleep_until()
```

## 互斥 mutex

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

## 同步 condition_variable
使用 condition_variable 实现线程的同步。以生产者-消费者模型为例：

```c++
// main
std::mutex m;
std::condition_variable cond_var;

// productor
produce();
std::lock_guard<std::mutex> lk(*m);
products.push_back(product);
cond_var.notify_one(); // 通知消费者
// consumer
std::unique_lock<std::mutex> lk(*m);
cond_var.wait(lk, [&products](){return not products.empty();});
product = products.back();
porducts.pop_back(0);
lk.unlock();
consume();
```

## 异步线程结果 future

线程中运行的函数的运行结果，可以通过函数的参数传递出来，使用互斥锁可以实现对共享变量的独占访问。在C++的future头文件中，提供了另外的异步线程间同步结果的方法的方法。

future是可用于线程中的共享对象，通过 async、promise 或 packaged_task 产生。参考如下例子

```c++
#include <future>
// async 用于指定一个异步任务
bool cmp(int a, int b) return a < b;
std::furure<bool> ret1 = std::async(cmp, 1, 2); // future 捕获返回值
cout << ret1.get() << endl; // 阻塞当前，直至拿到结果

// promise 提供一个future可以读取的本地对象
void func(std::future<int>& fut) {}
std::promise<int> prom;
std::future<int> fut = prom.get_future;
// 此时将 fut 穿过线程中，修改本地的 prom，通过线程中的 fut 可以获得
// 也可以作为线程间同步的手段
std::thread t(func, fut);
prom.set_value(10);
t.join();

// packaged_task 包装好的任务
std::package_task<bool(int,int)> task(cmp);
std::future<bool> ret2 = task.get_future();
std::thread ta(std::move(task), 1, 2);
cout << ret2.get() << endl;
```

## 原子操作

在某些需要高效率的算法中，可以直接使用原子操作提升效率。

atomic_flag 是 test-and-set 模型的原子类型，只支持 test-and-set 和 clear 两种操作。

```c++
std::atomic_flag af = ATOMIC_FLAG_INIT; // 初始化
if (af.test_and_set()) do_something;  // 如果没被置位过，就置位，并返回true；否则返回false
af.clear(); // 清除置位
```

可以看出通过上述的 test-and-set 与 clear 可以产生互斥锁的效果，只需要将临界区代码放在二者之间。当然 test-and-set 需要放在循环内一直测试，此时也会占用CPU，因此这种方式（自旋锁）仅适合与等待时间很短的情况。

atomic 是一个模板类，提高了更丰富的功能。

* store 修改被封装的值；
* load 读取被封装的值；
* exchange 读取被封装的值并修改封装的值，整个过程是原子的
* compare_exchange_weak
* compare_exchange_strong

最后两个成员函数，是实现 compare-and-swap 模型的原子类型。参数为 (expected, val)，如果atomic == expected，则赋值修改为val；否则替换 expected 为 atomic 的值。weak版本的函数可能会发生伪失败，但是在某些平台上效率更高一些，如果处于准确性考虑还是选用stong版本的较好，据说在 x86 平台下二者效率差别不大。

atomic 对整形和指针进行了特化，支持更多的运算和比较操作。

多线程的内存模型：CPU为提升效率有乱序执行的能力，尽量将内存连在一起的变量放在相邻的指令处理。在原子操作中可以通过设置内存模型控制编译器对指令重排的程度，尽量提升程序的效率。但是指令重排可能会带来错误，因此还是在把握很大的时候用内存模型优化。