#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> generateValidStrings(int n, int k) {
        vector<string> store;
        string stack;

        function<void(int,bool,int)> helper = [&helper, &store, &stack, n, k] (int i, bool b, int sum) {
            if (i == n) {
                if (sum <= k) store.push_back(stack);
                return;
            }
            
            stack.push_back('0');
            helper(i + 1, false, sum);
            stack.pop_back();
            
            if (!b && sum + i <= k) {
                stack.push_back('1');
                helper(i + 1, true, sum + i);
                stack.pop_back();
            }

        };

        helper(0, false, 0);
        return store;
        
    }
};

int main() {
    Solution sol;
    int n = 3, k = 1;
    auto ans = sol.generateValidStrings(n, k);
    for (auto s : ans) cout << s << " ";
    cout << endl;
}