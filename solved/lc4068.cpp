#include <bits/stdc++.h>
using namespace std;

// just a tedious bottom up dp.
// compress the start times to 0, 1, 2, ... n - 1.
// key idea is at snapshot i,
// the values are best(i),  j - i + best(j), j' - i + best(j')
// i.e we consider the 'beginning time' to be time i.
// if the best is at index k, it will always be the max even when the start time moves left.
// this is only for meetings that start at time t or later.
// if we introduce new meetings that start earlier the max must be recomputed.

function<int(int)> compress(const vector<int>& sorted_vals) {
    auto shared = make_shared<unordered_map<int,int>>();
    
    for (int i = 0; i < sorted_vals.size(); i++) {
        if (i == 0) {
            (*shared)[sorted_vals[i]] = 0;
        } else if (sorted_vals[i] != sorted_vals[i - 1]) {
            (*shared)[sorted_vals[i]] = (*shared)[sorted_vals[i - 1]] + 1;
        }   
    }

    return [shared] (int i) {
        auto it = shared->find(i);
        if (it == shared->end()) {
            return -1;
        } else {
            return it->second;
        }
    };
}

class Solution {
public:
    long long maxEarnings(vector<vector<int>>& meetings) {
        map<int, vector<vector<int>>> grouped;
        for (auto& m : meetings) {
            grouped[m[0]].push_back(m);
        }

        vector<int> start_times;
        for (auto& m : meetings) {
            start_times.push_back(m[0]);
        }
        sort(start_times.begin(), start_times.end());

        auto compressor = compress(start_times);
        int N = unordered_set<int>(start_times.begin(), start_times.end()).size();

        long long best = 0;
        vector<long long> store(N, -1LL);
        vector<long long> snapshot(N, 0);

        for (auto it = grouped.rbegin(); it != grouped.rend(); it++) {
            const auto& [start, meets] = *it;
            long long this_best = 0;

            for (const auto& m : meets) {
                int end = m[1];
                auto next_start_it = lower_bound(start_times.begin(), start_times.end(), end);
                
                if (next_start_it == start_times.end()) {
                    long long curr_best = m[2];
                    this_best = max(this_best, curr_best);
                } else {
                    int next_start = *next_start_it;
                    int idx = compressor(next_start);
                    
                    long long curr_best = m[2] + snapshot[idx] + next_start - end;
                    this_best = max(this_best, curr_best);

                }
            }

            int idx = compressor(start);
            auto next_start_it = upper_bound(start_times.begin(), start_times.end(), start);

            if (next_start_it == start_times.end()) {
                snapshot[idx] = this_best;
            } else {
                snapshot[idx] = max(this_best, *next_start_it - start + snapshot[idx + 1]);
            }

            best = max(best, this_best);
        }

        return best;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> meetings = {{3,5,4}, {4,7,8}, {8,10,3}};

    long long ans = sol.maxEarnings(meetings);
    cout << ans << endl;
}