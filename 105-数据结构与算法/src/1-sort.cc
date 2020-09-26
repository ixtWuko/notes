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

}

int main() {
    vector<int> unordered {3, 4, 1, 2, 5};

    vector<int> r1 = insertSort(unordered);
    print(r1);
    vector<int> r2 = bubbleSort(unordered);
    print(r2);
}