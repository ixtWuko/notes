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
    int i = l;
    int j = r;
    while (i < j) {
        if (nums[i] < key) ++i;
        else {
            swap(nums[i], nums[j]);
            --j;
        }
    }
    swap(nums[j], nums[r]);
    quickSort(nums, l, i-1);
    quickSort(nums, j+1, r);
}

int main() {
    vector<int> unordered {3, 4, 1, 2, 5};

    vector<int> r1 = insertSort(unordered);
    print(r1);
    vector<int> r2 = bubbleSort(unordered);
    print(r2);
    vector<int> r3 = mergeSort(unordered);
    print(r3);
}