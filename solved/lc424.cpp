#include <bits/stdc++.h>
#include <print>
using namespace std;

// check for each character A, B, C, D ... Z.
// use 2 pointer.
// if we want to change a character and cannot, we must free a slot.

int helper(const string& s, char c, int k) {
    int l = 0, best = 0, cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            cnt++;
            best = max(best, cnt);
            continue;
        } 

        if (k > 0) {
            k--;
            cnt++;
            best = max(best, cnt);
        } else {
            while (l < i && s[l] == c) {
                l++;
                cnt--;
            }

            if (l != i) {
                cnt = i - l;
                best = max(best, cnt);
            }

            l++;
        }
    }

    return best;
}

class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_set<char> store(s.begin(), s.end());
        int best = 0;
        for (char c : store) best = max(best, helper(s, c, k));
        return best;
    }
};

int main() {
    string s = "ABAB";
    println("{}", helper(s, 'C', 0));
}

