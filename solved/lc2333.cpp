#include <bits/stdc++.h>
using namespace std;

// sort abs(arr1[i] - arr2[i]) in increasing order.
// greedy solution. 
// notice the quadratic x^2.
// greedy solution.
// always reduce the largest square.
// if multiple same value, it is better to split and -1 from each value so the square becomes (x - 1)^2.


class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int> store;
        for (int i = 0; i < nums1.size(); i++) {
            store.push_back(abs(nums1[i] - nums2[i]));
        }
        sort(store.begin(), store.end());

        long long ops = k1 + k2;
        int p = store.size() - 1;
        int curr = store.back();

        while (ops >= 0) {
            while (p > -1 && store[p] == curr) p--;
            
            int next = (p == -1) ? 0 : store[p];
            int len = store.size() - 1 - p;
            auto total = (long long) (store.size() - 1 - p) * (curr - next);

            if (total <= ops) {
                ops -= total;
                curr = next;
                if (p == -1) break;
            } else {
                long long temp = 0;
                int q = ops / len;
                int r = ops % len;

                temp += (long long) r * pow((long long) (curr - q - 1), 2);
                temp += (long long) (len - r) * pow((long long) (curr - q), 2);

                for (int i = p; i > -1; i--) {
                    temp += pow((long long) store[i], 2);
                }

                return temp;
            }
        } 
        
        return 0;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {10,10,10,11,5};
    vector<int> nums2 = {1,0,6,6,1};
    int k1 = 11;
    int k2 = 27;

    auto ans = sol.minSumSquareDiff(nums1, nums2, k1, k2);
    cout << ans << endl;
}