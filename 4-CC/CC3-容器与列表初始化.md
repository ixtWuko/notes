## 容器
容器可以分为三类：序列式容器、关联容器、无序容器，此外还有一些容器适配器。
### 序列容器
**`array`** 与 **`vector`** ：`array` 与C中的数组类似，是一种大小固定的存储连续的容器；`vector` 也是存储连续的，但它的长度可以动态调整。相对于数组类型，这两种容器更为安全。由于 `array` 与 `vector` 都是连续存储的容器，能够高效地利用索引访问元素，但在中间部分插入/删除元素比较低效。

**`deque`** ：一种双端队列，也是一种连续存储的容器，能够高效地在首尾部添加/删除元素，但在中间部分插入/删除元素比较低效。

**`list`** 与 **`forward_list`** ：`list` 是由双向链表实现的，`forward_list` 是由单向链表实现的，因此这两种容器能够高效地插入/删除元素，但很难进行随机访问。

### 关联容器
**`map`** ：`map` 类型存储键值对，通常是以二叉树实现的，默认以 key 作为比较的依据。`map` 中的 key 不允许重复，而 **`multimap`** 与 `map` 的唯一的区别是元素可以重复。

**`set`** ：`set` 类型只存储键值，其它特性与 `map` 相同，**`multiset`** 与 `set` 的唯一区别是元素可以重复。

由于关联容器的底层实现是二叉树（红黑树），因此默认情况下关联容器中的 keys 是有序的。如果使用关联容器时对排序没有需求，可以选择下面的无序容器。

### 无序容器
关联容器中的四种类型都有对应的无序版本：**`unordered_map`**, **`unordered_multimap`**, **`unordered_set`**, **`unordered_multiset`**；无序容器通常是以哈希表实现的。

### 容器适配器
**`stack`** 默认的容器是 `deque`，**`queue`** 默认的容器是 `deque`，**`priority_queue`** 与 `queue` 功能类似，但是会按照压入元素的值排序，弹出值最大的元素。默认使用的容器是 `vector`。

## 如何选择容器
根据《C++标准库》中的描述，默认情况下应该选择 `vector`，如果需要经常在首尾部插入或移除元素，应该选择 `deque`，如果需要经常在中间部分插入或移除元素，应该选择 `list`。
如果需要经常查找元素，应该选择 `unordered_set`，如果需要使用键值对，应该选择 `unordered_map`，如果在上述两种场景下，需要满足有序，应该选择 `set` / `map`。

## 容器的操作
容器实现了大量的功能，以成员函数的形式提供这些功能，这里不在赘述，可以查看 [C++ Reference / Container](https://zh.cppreference.com/w/cpp/container)。但是仅仅阅读文档可能无法弄清楚这些成员函数的具体表现，需要在实践中多累积经验。

下面是一些我认为灵活使用的方法。

#### pair 与 tuple
尽管 `pair` 提供了 `first`, `second` 来访问元素，但是还可以使用 `get<idx>()` 函数来访问 `pair`, `tuple`, 甚至 `array` 的值，并且该函数还可以作为左值使用 `get<1>(p) = 10`。

`pair`, `tuple` 都提供来比较的能力，按照先比较第一个元素，相等时再比较第二个元素，……，以这样的顺序进行比较。

`make_pair`, `make_tuple` 用来创建新的 `pair`, `tuple`；而 `tie` 用来打包 `tuple`, 这里打包的是引用。
```c++
int a, b, c;
a = b = c = 0;
auto t = tie(a, b, c);
tie(a, b, c) = t;
```
上面的例子可以看出，使用 `tuple` 可以很方便地实现函数返回多个值，这种行为与 Python 非常类似，可以使用 `std::ignore` 略过不需要的值。

#### array
`array.data()` 会返回指向首元素的指针，这样就可以像使用数组一样处理 array 的数据。如：
```c++
array<int, 10> a {1, 2, 3, 4, 5};
int* p = a.data();
for (int i = 0; i < 10; ++i) {
    cout << *(p+i) << endl;
}
```
`vector`也提供了这个功能。

#### vector 与 deque
`vector` 与 `deque` 非常相似，只有在双端插入移除元素的需求时才会使用 `deque`。尽管 `vector` 也提供来访问首个元素的成员函数 `front`，但是没有像 `deque` 一样提供插入移除首个元素的成员函数。

借助 initlist 来实现初始化一个值的容器。
```c++
// 如果想初始化一个 大小为 n 的 vector / deque
vector<type> vec(n);
// 如果想初始化一个 第一个元素为 n 的 vector / deque
vector<type> vec({n});
```

#### list 与 forward_list
相比与前面的 `vector` 与 `deque`，`list` 与 `forward_list` 增加来很多不同的能力：排序 sort，逆序 reverse，去重 unique，合并 merge，移动元素 splice，去除元素 remove 等。


`forward_list` 没有实现 `size()`，原因可能是由于这种容器的设计目的是快速的插入，每次插入操作都去维护一个保存 size 的变量显然会降低效率；而每次获得 size 都遍历一遍链表的实现也是低效的，因为人们容易滥用 `size()` 成员函数。索性就没有实现，而且对于用户而言也不难自己实现。


#### map 与 multimap
`map` 中的元素是有序的，在 `map` 模板中，除前两个参数用来指定 key 与 value 的类型外，还可以提供第三个参数，用于指定排序时使用的比较方法。因此可以有两种方式来改变默认的排序规则：1) 指定 `map` 模板中的排序参数；2) 修改所使用类型的比较函数。

默认的排序准则是 `std::less<>`，如果像降序排列，可以使用 `std::greater<>`，尖括号内为 key 的类型。或者想使用自定义的排序准则，可以自定义一个比较的函数：
```c++
struct StrLenCmp {
   bool operator() (const string& lhs, const string& rhs) const {
      return lhs.size() < rhs.size();
   }
};
map<string, int, StrLenCmp> m;
```
尽管使用这样自定义的函数甚至可以实现以 value 值进行排序，但是 `map` 中只能保证 key 值唯一，不能保证 value 值唯一，因此使用 value 作为排序依据得到的排序结果无法保证。如果真的需要使用 value 排序，可以将 pair 放入一个 vector 中进行排序。

#### set 与 multiset
`set` 与 `map` 同理，也可以设置排序准则。

#### unordered 容器
unordered 容器可以在模板参数中指定一个 hash 函数，也可以在模板参数中指定一个用于比较相等的函数，对于小型程序用的的概率不是很大，使用默认的参数就好。

#### 补充：bitset
`bitset` 用来保存一串布尔值，使用 `vector<bool>` 也可以。具体的用法：
```c++
bitset<4> flag("1100");
bitset<16> flags(0xffff);
```
这种工具提供了下标访问，翻转 flip，以及用于检查全部位的 any all。

## 其它细节
* 容器无法以 引用 作为元素，但是可以以 指针 作为元素。
* 一般情况下，容器在不指定其它构造方法的情况下，都可以推断容器会进行默认构造。但是对于不是通过对象实现的类型，如基本类型，是没有默认构造的，都需要进行手动地初始化。
* `clear()` 成员函数会将容器置为空容器，不是把所有元素设为默认值。
* 连续存储容器的扩容，以 vector 为例，当 size == capacity 时，vector 会以1.5倍或2倍来增加capacity。而链表存储容器，以 list 为例，每增加一个元素就申请一个元素的空间。

## 列表初始化
列表初始化为 C++ 提供来统一的初始化方式。不管是基本类型，还是容器，以及自定义的类型，都可以使用列表初始化。在自定义类型中的构造函数中使用初始值列表，那么就可以使用列表初始化来进行，这两个是对应的。
