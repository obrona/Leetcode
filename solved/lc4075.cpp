#include <bits/stdc++.h>
using namespace std;

// O(n^2) solution.
// for each start index i, store a hashmap of key x % k and the count.
// subarray (i, j) is valid if sum % k == x % k for every x in the subarray.
// need some constant factor optimisations.
// for example if the hashmap contains >1 key, then we break.

class Solution {
public:
    int resilientSubarray(vector<int>& nums, int k) {
        int best = 1;
        unordered_map<int, int> store;
        for (int i = 0; i < nums.size(); i++) {
            store.clear();
            int sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                store[nums[j] % k]++;
                if (store.size() > 1) break;

                auto it = store.find(sum % k);
                if (it != store.end() && it->second == j - i + 1) {
                    best = max(best, j - i + 1);
                }
                
            }

        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,5,4,8};
    int k = 4;

    cout << sol.resilientSubarray(nums, k) << endl;
}