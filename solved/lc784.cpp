#include <bits/stdc++.h>
using namespace std;

// simple change/no change backtracking.

class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> store;

        function<void(int)> dfs = [&] (int i) {
            if (i == s.size()) {
                store.push_back(s);
                return;
            }
            
            char c = s[i];
            if (!isalpha(c)) {
                dfs(i + 1);
                return;
            }

            if (islower(s[i])) {
                s[i] = toupper(c);
            } else {
                s[i] = tolower(c);
            }
            
            dfs(i + 1);
            s[i] = c;
            dfs(i + 1);
        };

        dfs(0);
        return store;
    }
};

int main() {
    Solution sol;
    string s = "a1b2";
    vector<string> ans = sol.letterCasePermutation(s);
    for (auto a : ans) cout << a << " ";
    cout << endl;
}