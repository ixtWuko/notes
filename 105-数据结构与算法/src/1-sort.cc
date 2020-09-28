#include "include/print.h"
#include "include/node.h"

using namespace std;


// =======  插入排序  =======
vector<int> insertSort(vector<int>& nums) {
    if (nums.empty()) return nums;
    list<int> helper;

    helper.emplace(helper.begin(), nums[0]);
    for (int i = 1; i < nums.size(); ++i) {
        auto it = helper.begin();
        while (it != helper.end()) {
            if (*it > nums[i]) break;
            ++it;
        }
        helper.emplace(it, nums[i]);
    }

    vector<int> res(helper.begin(), helper.end());
    return res;
}

// ======= 冒泡排序  =======
vector<int> bubbleSort(vector<int>& nums) {
    if (nums.empty()) return nums;
    vector<int> res(nums.begin(), nums.end());

    for (int i = 1; i < res.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (res[j] > res[i]) swap(res[j], res[i]);
        }
    }
    return res;
}

// =======  归并排序  =======
vector<int> mergeSort(vector<int>& nums) {
    if (nums.empty()) return nums;

    vector<int> res(nums.begin(), nums.end());
    mergeSort(res, 0, nums.size()-1);
    return res;
}

void mergeSort(vector<int>& nums, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergeSort(nums, l, mid);
    mergeSort(nums, mid+1, r);

    vector<int> tmp(r-l+1);
    int i = l, j = mid+1;
    int k = 0;
    while (i <= mid and j <= r) {
        if (nums[i] < nums[j]) tmp[k++] = nums[i++];
        else tmp[k++] = nums[j++];
    }
    while (i <= mid) tmp[k++] = nums[i++];
    while (j <= r) tmp[k++] = nums[j++];
    for (int i = 0; i < r-l+1; ++i) nums[l+i] = tmp[i];
}

// ========  快速排序  =======
vector<int> quickSort(vector<int>& nums) {
    if (nums.empty()) return nums;
    vector<int> res(nums.begin(), nums.end());

    quickSort(res, 0, res.size()-1);
    return res;
}

void quickSort(vector<int>& nums, int l, int r) {
    if (l >= r) return;
    int key = nums[r];
    int i = l-1;
    for (int j = l; j < r; ++j) {
        if (nums[j] <= key) {
            ++i;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i+1], nums[r]);
    quickSort(nums, l, i);
    quickSort(nums, i+2, r);
}


// =======  堆排序  =======
template <typename T>
class Heap {
private:
    vector<T> data;

public:
    Heap() = default;
    Heap(vector<T>& _input) : data(_input) {
        for (int i = data.size() / 2; i >=0; --i) {
            max_heapify(i);
        }
    }

    vector<T> sort() {
        vector<T> res;
        while (not data.empty()) {
            max_heapify(0);
            swap(data[0], data[data.size()-1]);
            res.push_back(data.back());
            data.pop_back();
        }
        return res;
    }
private:
    inline int parent_idx(int _idx) {
        return (_idx - 1) / 2;
    }
    inline int left_idx(int _idx) {
        return 2 * _idx + 1;
    }
    inline int right_idx(int _idx) {
        return 2 * _idx + 2;
    }

    void max_heapify(int _idx) {
        int largest = _idx;
        int l = left_idx(_idx);
        int r = right_idx(_idx);
        if (l < data.size() and data[l] > data[largest]) largest = l;
        if (r < data.size() and data[r] > data[largest]) largest = r;

        if (largest != _idx) {
            swap(data[_idx], data[largest]);
            max_heapify(largest);
        }
    }
};

// =======  顺序查找  =======
size_t search(vector<int>& nums, int key) {
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == key) return i;
    }
    return -1;
}


// =======  顺序统计量  =======
int kthElement(vector<int>& nums, int kth) {
    return kthElement(nums, 0, nums.size()-1, kth-1);
}

int kthElement(vector<int>& nums, int l, int r, int kth) {
    int key = nums[r];
    int i = l-1;
    for (int j = l; j < r; ++j) {
        if (nums[j] <= key) {
            ++i;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i+1], nums[r]);
    if (kth == i+1) return nums[i+1];
    else if (kth < i+1) return kthElement(nums, l, i, kth);
    else return kthElement(nums, i+2, r, kth);
}
