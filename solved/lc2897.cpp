#include <bits/stdc++.h>
using namespace std;

// (x, y) -> (x & y, x | y) transfer bits in x not in y to y.
// greedy solution. 
// take index 0, transfer as many bits to num at index 0.
// repeat for index 1 to k - 1.
// this gives a O(kn) solution. 

// can get a O(30^2 * n) solution.
// for each bit index 0 to 29, we store numbers whose bit is at at those positions.
// so if we want to transfer bit i to the target index, 
// just take any number whose bit i is 1.
// too bad it i TLE.

// can get a O(30n) solution.
// think of it as gravity. the 1 bits fall to the ground.
// eg 
// 1000
// 1001
// 1010
// 1111
// 
// the best way is 
// 1000
// 1000
// 1011
// 1111

long long MOD = 1000000007;

class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        int N = bit_width((unsigned int) *max_element(nums.begin(), nums.end()));
        
        vector<int> store(N, 0);

        for (int x : nums) {
            for (int i = 0; i < N; i++) {
                store[i] += ((x >> i) & 1);
            }
        }

        long long sum = 0;
        for (int i = 0; i < k; i++) {
            long long x = 0;
            for (int b = 0; b < N; b++) {
                if (store[b] > 0) {
                    x += 1 << b;
                    store[b]--;
                }
            }

            x %= MOD;
            sum += (x * x) % MOD;
            sum %= MOD;
        }

        return sum;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {25,52,75,65};
    int k = 4;

    int ans = sol.maxSum(nums, k);
    cout << ans << endl;
}