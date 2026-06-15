#include <bits/stdc++.h>
using namespace std;

// since length is 10^3, just do naive O(n^2) algo to check all possible subarrays.

bool is_valid(const unordered_map<int, int> &store, const unordered_map<int,int> &freq_set) {
    if (store.size() == 1) return true;
    if (freq_set.size() != 2) return false;
    
    int a = freq_set.begin()->first, b = next(freq_set.begin())->first;
    if (a < b) swap(a, b);
    return a % 2 == 0 && 2 * b == a;
}

class Solution {
public:
    int getLength(vector<int>& nums) {
        int best = 1;
        for (int i = 0; i < nums.size(); i++) {
            unordered_map<int, int> store;   
            unordered_map<int,int> freq_set; // we  do not include 0.

            for (int j = i; j < nums.size(); j++) {
                int& c = store[nums[j]];
                if (c != 0) {
                    freq_set[c]--;
                    if (freq_set[c] == 0) {
                        freq_set.erase(c);
                    }
                }
                freq_set[++c]++;

                if (is_valid(store, freq_set)) {
                    best = max(best, j - i + 1);
                }
            }
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,2,2,1,2,3,3,3};
    int ans = sol.getLength(nums);
    cout << ans << endl;
}