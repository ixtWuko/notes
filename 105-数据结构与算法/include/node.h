#ifndef NODE_H
#define NODE_H


template <typename T>
struct ListNode {
    T val;
    ListNode* next;

    ListNode(T _val) : val(_val), next(nullptr) {}
    ListNode(T _val, ListNode* _next) : val(_val), next(_next) {}
};

template <typename T>
struct DoubleListNode {
    T val;
    DoubleListNode* prev, next;

    DoubleListNode(T _val) : val(_val), prev(nullptr), next(nullptr) {}
    DoubleListNode(T _val, DoubleListNode* _prev, DoubleListNode* _next) : val(_val), prev(_prev), next(_next) {}
};

template <typename T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T _val) : val(_val), left(nullptr), right(nullptr) {}
};


#endif//NODE_H