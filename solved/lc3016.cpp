#include <bits/stdc++.h>
using namespace std;

// get the frequency of each character.
// clearly we want the most frequent characters to have the least presses needed.

class Solution {
public:
    int minimumPushes(string word) {
        unordered_map<char, int> store;
        for (char c : word) store[c]++;
        vector<pair<char,int>> arr(store.begin(), store.end());
        sort(arr.begin(), arr.end(), [] (auto& p1, auto& p2) { return p1.second > p2.second; });

        int sum = 0;
        int presses = 1;
        int cnt = 8;

        auto reset = [&] () {
            cnt = 8;
            presses += 1;
        };

        for (auto [c, n] : arr) {
            if (cnt == 0) reset();
            sum += presses * n;
            cnt--;
        }

        return sum;
    }
};

int main() {
    Solution sol;
    string word = "aabbccddeeffgghhiiiiii";
    int ans = sol.minimumPushes(word);
    println("{}", ans);
}