#include <bits/stdc++.h>
using namespace std;

// no need for any fancy data structure.
// only 26 chars, so the distinct characters in a subarray is at most 26.
// consider subarray [i, i], [i, i+1], [i, i+2] ... the number of times the distinct character cnt
// changes is 26.

// for each index, store the left prev index and right next index of the same character.
// when we go from index j to index j + 1, let say the character at index j + 1 is 'a' and the left 
// prev is at index m. 
// then only subarray [m + 1, j], [m + 2, j] changes.
// we update them 1 by 1.
// update the freq cnt 1 by 1

// for the right next index of 'a' at index j + 1, let say at g
// then only subarray [j + 1, j + 1], [j + 1, j + 2] ... [j + 1, g - 1] changes.
// update them 1 by 1.

// time complexity is amortised O(26n).

class Solution {
public:
    long long countMagicalPairs(string s) {
        unordered_map<char, int> left_occ, right_occ;
        vector<int> left_prev(s.size()), right_next(s.size());

        for (int i = 0; i < s.size(); i++) {
            auto it = left_occ.find(s[i]);
            if (it == left_occ.end()) {
                left_prev[i] = -1;
                left_occ[s[i]] = i;
            } else {
                left_prev[i] = it->second;
                it->second = i;
            }
        }

        for (int i = s.size() - 1; i > -1; i--) {
            auto it = right_occ.find(s[i]);
            if (it == right_occ.end()) {
                right_next[i] = s.size();
                right_occ[s[i]] = i;
            } else {
                right_next[i] = it->second;
                it->second = i;
            }
        }

        long long cnt = 0;
        unordered_map<long long, int> left_freqs, right_freqs;
        vector<int> left_store(s.size(), 0), right_store(s.size(), 0);

        left_freqs[0] = right_freqs[0] = s.size();

        for (int i = s.size() - 1; i > 0; i--) {
            int limit = right_next[i];
            for (int j = limit - 1; j >= i; j--) {
                right_freqs[right_store[j]]--;
                right_freqs[++right_store[j]]++;
            }
        }

        for (int j = 0; j < s.size() - 1; j++) {
            // update left
            int limit = left_prev[j];
            for (int m = limit + 1; m <= j; m++) {
                left_freqs[left_store[m]]--;
                left_freqs[++left_store[m]]++;
            }

            // count the triplets
            for (int d = 1; d < 27; d++) {
                cnt += (long long) left_freqs[d] * right_freqs[d];
            }

            // update right;
            limit = right_next[j + 1];
            for (int m = limit - 1; m >= j + 1; m--) {
                right_freqs[right_store[m]]--;
                right_freqs[--right_store[m]]++;
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