#include <bits/stdc++.h>
#include <bit>
using namespace std;

// use Mo's algo.
// sort by increasing block index = left index / 256, then by increasing right index.
// for each query, we shift at most sqrt(N) for the left index.
// the right index only moves forward for each block, so at most Nsqrt(N).
// use blk size that is a pow of 2 so we do not need to use modulo operations.

vector<array<int,4>> process(const vector<vector<int>>& queries, int blk_size) {
    int shift = bit_width((unsigned int) blk_size) - 1;
    vector<array<int,4>> out;
    for (int i = 0; i < queries.size(); i++) {
        const auto& q = queries[i];
        out.push_back({i, q[0] >> shift, q[0], q[1] + 1});
    }
    sort(out.begin(), out.end(), [] (const auto& arr1, const auto& arr2) {
        if (arr1[1] != arr2[1]) {
            return arr1[1] < arr2[1];
        }
        return arr1[3] < arr2[3];
    });

    return out;
}

class Solution {
public:
    vector<bool> validSubarrays(vector<int>& nums, int k, vector<vector<int>>& queries) {
        unordered_map<int,int> freqs;
        int odd_cnt = 0;
        vector<bool> out(queries.size(), false);
        auto processed = process(queries, 512);

        auto add = [&] (int x) {
            int cnt = ++freqs[x];
            if (freqs[x] & 1 == 1) {
                odd_cnt++;
            } else {
                odd_cnt--;
            }
        };

        auto remove = [&] (int x) {
            int cnt = --freqs[x];
            if (cnt & 1 == 1) {
                odd_cnt++;
            } else {
                odd_cnt--;
            }
            if (cnt == 0) {
                freqs.erase(x);
            }
        };

        auto clear = [&] () {
            freqs.clear();
            odd_cnt = 0;
        };

        int prev_blk = -1;
        int curr_l = 0, curr_r = 0;
        for (const auto& [i, bi, l, r] : processed) {
            // no need to clear the store when starting a new block.
            // we can just shrink, extend curr_r accordingly.

            while (curr_r > r) {
                remove(nums[--curr_r]);
            }

            while (curr_r < r) {
                add(nums[curr_r++]);
            }

            while (curr_l < l) {
                remove(nums[curr_l++]);
            }

            while (curr_l > l) {
                add(nums[--curr_l]);
            }

            out[i] = !odd_cnt && freqs.size() == k;
        }

        return out;
    };
};

int main() {
    Solution sol;
    vector<int> nums = {1,2,2,1};
    int k = 2;
    vector<vector<int>> queries = {{0,1},{0,3},{1,2}};
    
    auto ans = sol.validSubarrays(nums, k, queries);
    for (auto a : ans) cout << a << " ";
    cout << endl;
}