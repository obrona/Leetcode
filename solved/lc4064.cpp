#include <bits/stdc++.h>
using namespace std;

// O(n + k^2logN) sol.
// 1 <= k <= 3000 is the intuition.
// consider a subarray (i, j) defined by sum(0..j) - sum(0..i - 1).
// modulo of sum falls in range 0..k-1
// so basically for pairs modulo (x, y) let x be modulo sum of arr[0..i-1]
// and y be modulo sum of arr[0..j]
// get the difference and then in range (i, j) check if any element has 2*x % k equal to the 
// difference.

// for each modulo y, take the rightmost index.
// for each modulo x take the leftmost index.

int mod(int x, int k) {
    int y = x % k;
    return y < 0 ? y + k : y;
}

class Solution {
public:
    int longestSubarray(vector<int>& nums, int k) {
        vector<int> prefix_sum(nums.size());
        vector<vector<int>> prefix_store(k);
        vector<vector<int>> elem_store(k);

        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum = (sum + nums[i]) % k;
            if (sum < 0) sum += k;
            prefix_sum[i] = sum;
            prefix_store[sum].push_back(i);
            elem_store[mod(2 * nums[i], k)].push_back(i);
        }

        auto helper = [](int l, int r, const vector<int>& pos) {
            auto it = lower_bound(pos.begin(), pos.end(), l);
            return it != pos.end() && *it <= r;
        };

        int best = 0;

        // case 1, the subarray is a prefix itself.
        for (int y = 0; y < k; y++) {
            if (prefix_store[y].size() == 0) continue;
            int r = prefix_store[y].back();

            if (y == 0 || helper(0, r, elem_store[y])) {
                best = max(best, r + 1);
            }
        }

        // case 2: subarray is not a prefix, i.e l != 0
        for (int x = 0; x < k; x++) {
            for (int y = 0; y < k; y++) {
                if (prefix_store[x].size() == 0) continue;
                if (prefix_store[y].size() == 0) continue;

                int l = prefix_store[x].front() + 1;
                int r = prefix_store[y].back();

                if (l > r || (r - l + 1) <= best) continue;

                int diff = prefix_sum[r] - prefix_sum[l - 1];
                if (diff < 0) diff += k;

                if (diff == 0 || helper(l, r, elem_store[diff])) {
                    best = max(best, r - l + 1);
                }
            }
        }

        return best;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {-4,-3};
    int k = 3;

    int ans = sol.longestSubarray(nums, k);
    cout << ans << endl;
}