#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <utility>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>


template <typename T>
void print(const T& t) {
    std::cout << t;
}

template <typename T1, typename T2>
void print(std::pair<T1, T2>& t) {
    print("(");
    print(t.first);
    print(" : ");
    print(t.second);
    print(")");
}

template <typename Func, typename Tuple, int N>
struct TupleHelper {
    static void func(Func f, const Tuple& _) {
        TupleHelper<Func, Tuple, N-1>::func(f, _);
        f(std::get<N-1>(_), N-1);
    }
};

template <typename Func, typename Tuple>
struct TupleHelper<Func, Tuple, 1> {
    static void func(Func f, const Tuple& _) {
        f(std::get<0>(_), 0);
    }
};

template <typename Func, typename... Args>
void manipulate_tuple(Func f, const std::tuple<Args...>& _) {
    TupleHelper<Func, decltype(_), sizeof...(Args)>::func(f, _);
}

template <typename... Args>
void print(const std::tuple<Args...>& t) {
    print("(");
    manipulate_tuple([](auto _, std::size_t idx){
        if (idx != 0) print(",");
        print(_);
    }, t);
    print(")");
}

template <typename T, typename AllocT, template <typename, typename...> typename SequenceT>
void print(SequenceT<T, AllocT> seq)
{
    print("{ ");
    for (auto iter = std::begin(seq); iter != std::end(seq); iter = std::next(iter))
    {
        if (iter != std::begin(seq))
            print(", ");
        print(*iter);
    }
    print(" }\n");
}


#endif//PRINT_H