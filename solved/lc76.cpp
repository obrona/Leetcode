#include <bits/stdc++.h>
using namespace std;

// simple 2 pointer solution.

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> freq;
        for (char c : t) freq[c]++;
        unordered_map<char, int> store;
        int fufilled = 0, need = freq.size();
        int l = 0, r = 0;
        int best_l = 0, best_r = 999999999;

        auto update_best = [&best_l, &best_r] (int l, int r) {
            if (r - l < best_r - best_l) {
                best_l = l, best_r = r;
            }
        };

        auto push = [&freq, &store, &fufilled, &s] (int i) {
            char c = s[i];
            store[c]++;
            if (freq.contains(c) && store[c] == freq[c]) {
                fufilled++;
            }
        };

        auto pop = [&freq, &store, &fufilled, &s] (int i) {
            char c = s[i];
            store[c]--;
            if (freq.contains(c) && store[c] == freq[c] - 1) {
                fufilled--;
            }
        };

        int p = 0;
        for (int i = 0; i < s.size(); i++) {
            while (p < s.size() && fufilled < need) push(p++);
            //cout << i << " " << p << endl;
            if (fufilled == need) update_best(i, p);
            pop(i);
        }

        if (best_r - best_l == 999999999) {
            return "";
        }
        return s.substr(best_l, best_r - best_l);

    }
};

int main() {
    Solution sol;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    
    string ans = sol.minWindow(s, t);
    cout << ans << endl;
}