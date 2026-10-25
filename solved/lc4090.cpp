#include <bits/stdc++.h>
#include <ranges>
using namespace std;

// O(n**2) algo.
// fix the middle index j
// get the distinct count for arr[i:j] and arr[j + 1:k]
// then just multiple cnt of same value.

class Solution {
public:
    int countMagicalPairs(string s) {
        int cnt = 0;
        unordered_map<int, int> left, right;
        array<int, 26> store{};
        
        for (int j = 0; j < s.size() - 1; j++) {
            left.clear();
            right.clear();

            store.fill(0);
            for (int i = j, d = 0; i > -1; i--) {
                d += (store[s[i] - 'a']++ == 0);
                left[d]++;
            }

            store.fill(0);
            for (int k = j + 1, d = 0; k < s.size(); k++) {
                d += (store[s[k] - 'a']++ == 0);
                right[d]++;
            }

            for (auto [k, v] : left) {
                auto it = right.find(k);
                if (it != right.end()) cnt += v * it->second;
            }
        }
        return cnt;
    }
};

int main() {
    Solution sol;
    string s = "aba";

    int ans = sol.countMagicalPairs(s);
    cout << ans << endl;
}