#include <bits/stdc++.h>
using namespace std;

// slice indexing here is right exclusive.

// difficult dp.
// dp(i, m) is the best score you can get in arr[i:] with m slots.
// can choose nothing, so go to dp(i + 1, m)
// or select at least l elements and up to r elements eg. sum(arr[i:i + l]) + dp(i + l, m - 1)

// use deque to store sliding window max.
// need to use offset to range update max quickly.
// use prefix sums to get sum(arr[l:r]) quickly.

// note elements pop from the right and added from the left,
// i.e the window goes from right to left.
struct SlidingMax {
    long long offset = 0;
    deque<pair<int,long long>> window;

    void pop_right(int idx) {
        if (window.empty()) return;
        auto [i, _] = window.back();
        if (i != idx) return;
        window.pop_back();
    }

    void add_left(int idx, long long val) {
        while (!window.empty()) {
            auto [_, v] = window.front();
            if (val >= v + offset) {
                window.pop_front();
            } else {
                break;
            }
        }
        window.emplace_front(idx, val - offset);
    }

    void add_to_offset(long long v) {
        offset += v;
    }

    long long get_max() {
        if (window.empty()) return (long long) -1e14;
        return window.back().second + offset;
    }
};

struct PrefixSum {
    vector<long long> prefix_sums;

    PrefixSum(const vector<int>& nums): prefix_sums(nums.size(), 0) {
        prefix_sums[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            prefix_sums[i] = nums[i] + prefix_sums[i - 1];
        }
    }

    // get the sum of arr[l:r]
    long long query(int l, int r) {
        return (l == 0) ? prefix_sums[r] : prefix_sums[r] - prefix_sums[l - 1];
    }
};

class Solution {
public:

    // remember dp(i, m) must contain at least 1 subarray
    long long dp(const vector<int>& nums, int M, int L, int R) {
        long long MIN = -1e14;
        vector<vector<long long>> store(nums.size() + 1, vector(M + 1, MIN));
        PrefixSum prefix_sum(nums);

        for (int m = 1; m <= M; m++) {
            SlidingMax sliding_max;
            for (int i = nums.size() - 1; i >= 0; i--) {
                // the default element cannot be 0, because we must at least 1 subarray.
                long long notake = (i < nums.size() - 1) ? store[i + 1][m] : MIN;
                
                long long take = MIN;
                if (i + L <= nums.size()) {
                    sliding_max.pop_right(i + 1 + R);
                    sliding_max.add_to_offset(nums[i]);

                    // since we already take 1 subarray, we can take nothing.
                    sliding_max.add_left(i + L, prefix_sum.query(i, i + L - 1) + max(0LL, store[i + L][m - 1]));
                    take = sliding_max.get_max();
                }

                store[i][m] = max(notake, take);
            }
        }

        return store[0][M];

    }


    // special case when all elems are negative.
    // then just select the least negative elem (the max element).
    // if at least 1 element is >= 0, the result is always >= 0.
    long long maximumSum(vector<int>& nums, int m, int l, int r) {
        /*if (all_of(nums.begin(), nums.end(), [] (int x) { return x < 0; })) {
            return *max_element(nums.begin(), nums.end());
        }*/

        return dp(nums, m, l, r);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-3,-4,-1};
    int m = 2, l = 1, r = 2;

    long long ans = sol.maximumSum(nums, m, l, r);
    println("{}", ans);
}


