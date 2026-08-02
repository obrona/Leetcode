#include <bits/stdc++.h>
using namespace std;

// get the frequency of each value, then transform into vector of (val, freq) sorted in increasing val.
// then for (i, j) i < j, we add min(freq[i], freq[j]) to a global store.
// for h = 2 * val[i], add freq[i] / 2 instead.
// for h = val[i], add freq[i].

// for each h, not possible to double count.
// suppose vals[i] is double counted with j and j' but the final value will be different.

class Solution {
public:
    int maximumWidth(vector<int>& planks) {
        unordered_map<int, int> freqs;
        for (int x : planks) freqs[x]++;
        vector<pair<int,int>> store(freqs.begin(), freqs.end());
        sort(store.begin(), store.end(), [] (auto& p1, auto& p2) { return p1.first < p2.first; });

        unordered_map<int,int> results;
        for (int i = 0; i < store.size(); i++) {
            const auto& p = store[i];
            results[p.first] += p.second;

            results[p.first * 2] += p.second / 2;
            for (int j = i + 1; j < store.size(); j++) {
                const auto& p2 = store[j];
                results[p.first + p2.first] += min(p.second, p2.second);
            }
        }

        auto it = max_element(results.begin(), results.end(), [](const auto& p1, const auto& p2) { return p1.second < p2.second; });
        return it->second;
    }
};

int main() {
    Solution sol;
    vector<int> planks = {59,37,55,90,94};

    int ans = sol.maximumWidth(planks);
    cout << ans << endl;
}