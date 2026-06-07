#include <bits/stdc++.h>
using namespace std;

// simple dp.
// dp(i, isTaken) means we are considering arr[0:i+1] and we are at index i.
// isTaken is to check whether index i is taken from a token at inde i + 1.

class Solution {
public:
    vector<long long> store;

    int pos(int i, bool b) {
        return i * 2 + b;
    }

    long long dp(int i, bool b, const vector<int>& nums, const string& s) {
        if (i < 0) return 0;
        
        auto& ans = store[pos(i, b)];
        if (ans != -1) return ans;

        if (b) {
            if (s[i] == '0') {
                return ans = dp(i - 1, false, nums, s);
            } else {
                auto notake = dp(i - 1, false, nums, s);
                auto take = (i > 0) ? nums[i - 1] + dp(i - 1, true, nums, s) : 0;
                return ans = max(take, notake);
            }
        } else {
            if (s[i] == '0') {
                return ans = dp(i - 1, false, nums, s);
            } else {
                auto nomove = nums[i] + dp(i - 1, false, nums, s);
                auto move = (i > 0) ? nums[i - 1] + dp(i - 1, true, nums, s) : 0;
                return ans = max(move, nomove);
            }
        }
       
    }


    long long maxTotal(vector<int>& nums, string s) {
        store = vector(s.size() * 2, -1LL);
        return dp(s.size() - 1, false, nums, s);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,1,4};
    string s = "001";

    auto ans = sol.maxTotal(nums, s);
    println("{}", ans);

}