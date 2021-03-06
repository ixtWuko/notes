# 模板

## 函数模板

```c++
template <typename T>
void max(T&& a, T&& b) {
    return a > b ? a : b;
}

// 函数模板的使用
max(1, 2);           // OK
max(1, 2.0);         // ERROR
max<float>(1, 2.0);  // OK

// 返回类型推断
template <typename T>
auto max(T a, T b) -> decltype(a > b ? a : b) {
    return a > b ? a : b;
}
```

## 类模板
```c++
template <typename T>
class TClass {
    T member;
    void func(const T& arg);
}
```
### 特化
全特化是模板对于特殊情况下的处理，这种特殊情况是模板参数全部指定的情况，如上述的模板类型进行全特化：
```c++
template <>
class TClass<float> {
    void func(float arg);
}
```
偏特化也是对特殊情况的处理，这种特殊情况下部分参数需要指定。可以看出全特化后其实已经不再是一个模板类，但是偏特化后仍是一个模板。

**函数模板是不允许进行偏特化的，但是允许重载。**

## 模板参数
类型形参就是用来指代类型的模板参数，会使用 `typename` 或 `class` 来说明是一个类型形参。非类型形参就是不是类型的模板参数，支持整形、指针、引用，这里的整形是广义的整形，如 `bool` 其实也是整形。

模板参数可以指定默认值，如 `template<typename T = string, int N = 10>`.

模板参数可以是变长的，如 `template<typename ... T>` 指不定长度、不定类型的多个类型。这一特性有时称为模板参数包。

---

> 不了解 C++ 中的模板并不会影响到 C++ 的日常使用，这里只是一个简单的介绍。