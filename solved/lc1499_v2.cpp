#include <bits/stdc++.h>
using namespace std;

// it is possible to do better from O(nlogn) to O(n)
// by using a monotonic queue.
// however this queue has an offset as we need to do range add to all elems in the monotonic queue.

struct mono_decr_queue {
    struct res {
        int idx;
        int val;

        res() {}

        res(int idx, int val): idx(idx), val(val) {}
    };

    int offset = 0;
    deque<res> q;

    void insert(int idx, int val) {
        while (!q.empty() && q.back().val + offset <= val) q.pop_back();
        q.emplace_back(idx, val - offset);
    }

    void pop_back(int idx) {
        if (q.empty()) return;
        auto l = q.front();
        if (l.idx == idx) q.pop_front();
    }

    void add_to_offset(int val) {
        offset += val;
    }

    int get_max() {
        return (q.empty()) ? -(int) 1e9 : offset + q.front().val;
    }
};

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        sort(points.begin(), points.end(), [] (const auto& p1, const auto& p2) {
            return p1[0] < p2[0];
        });

        int best = -(int) 1e9;
        int p = 1;
        mono_decr_queue store;
        
        for (int i = 0; i < points.size(); i++) {
            auto& curr = points[i];
            
            p = max(p, i + 1);
            while (p < points.size()) {
                auto& next = points[p];
                if (next[0] - curr[0] > k) break;
                store.insert(p, next[0] - curr[0] + next[1] + curr[1]);
                p++;
            }

            int res = store.get_max();
            best = max(best, res);

            if (i < points.size() - 1) {
                store.pop_back(i + 1);
                int delta = points[i + 1][1] - points[i][1] + points[i][0] - points[i + 1][0];
                store.add_to_offset(delta);
            }
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> points = {{1,3}, {2,0}, {5,10}, {6,-10}};
    int k = 1;

    int ans = sol.findMaxValueOfEquation(points, k);
    cout << ans << endl;
}
