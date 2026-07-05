#include <bits/stdc++.h>
using namespace std;

// not so simple dp.
// consider simple problem given string s, how many times the substring t occurs in s
// simple dp(s_i, t_j) and take, no take
// but for this dp(s1_i, s2_j, t_k) does not work because of double counting

// let dp(s1_i, s2_j, t_k, side, switched)
// side means t_k must be filled by s1 (or s2)
// switched means we have switch side.
// this way we prevent double counting as we make sure target[k] is confirmed taken by s1 (or s2) 
// even when we skip s1_i (or s2_j).

class Solution {
public:
    string s1, s2, target;
    vector<int> store;
    int MOD = 1e9 + 7;

    int add(int a, int b) {
        return (a + b) % MOD;
    }

    int sub(int a, int b) {
        int c = a - b;
        if (c < 0) c += MOD;
        return c;
    }

    int to_pos(int i, int j, int k, bool b1, bool b2) {
        return i * (s2.size() + 1) * (target.size() + 1) * 4 
            + j * (target.size() + 1) * 4 
            + k * 4 
            + b1 * 2 
            + b2;
    }

    int dp(int i, int j, int k, bool side, bool switched) {
        if (k == target.size()) return switched;
        if (i == s1.size() && j == s2.size()) return 0;

        int& ans = store[to_pos(i, j, k, side, switched)];
        if (ans != -1) return ans;

        ans = 0;
        if (!side) {
            if (i == s1.size()) return ans = 0;
            
            if (s1[i] == target[k]) {
                // careful of double couting last character.
                // if next transition k == target.size(), we get 2 instead of 1.
                // also need to check for switched, return 0 if switch is false.
                ans = (k == target.size() - 1) ? switched : add(dp(i + 1, j, k + 1, 0, switched), dp(i + 1, j, k + 1, 1, true));
            } 

            ans = add(ans, dp(i + 1, j, k, 0, switched));
            
        } else {
            if (j == s2.size()) return ans = 0;
            
            if (s2[j] == target[k]) {
                ans = (k == target.size() - 1) ? switched : add(dp(i, j + 1, k + 1, 0, true), dp(i, j + 1, k + 1, 1, switched));
            } 
            ans = add(ans, dp(i, j + 1, k, 1, switched));
            
        }

        return ans;
    }
    int interleaveCharacters(string word1, string word2, string target) {
        s1 = word1;
        s2 = word2;
        this->target = target;
        store = vector((s1.size() + 1) * (s2.size() + 1) * (target.size() + 1) * 4, -1);

        int a1 = dp(0, 0, 0, 0, 0), a2 = dp(0, 0, 0, 1, 0);
        return add(a1, a2);
    }
};

int main() {
    Solution sol;
    auto word1 = "abc";
    auto word2 = "bac";
    auto target = "abc";

    int ans = sol.interleaveCharacters(word1, word2, target);
    cout << ans << endl;
}