#include <bits/stdc++.h>
using namespace std;

// just use bfs.
// to reduce time complexity for each val (arr[i]), we store a value to indicate whether it has been search.
// i.e arr[1] = 5, for all arr[i] = 5, we do not search same_vals again.

class Solution {
public:
    int minJumps(vector<int>& arr) {
        unordered_map<int, vector<int>> same_vals;
        unordered_set<int> seen_vals;
        vector<int> visited(arr.size(), -1);
        deque<int> q;
        int wave = 0;

        for (int i = 0; i < arr.size(); i++) {
            same_vals[arr[i]].push_back(i);
        }

        q.emplace_back(0);
        while (!q.empty()) {
            for (int len = q.size(); len > 0; len--) {
                int i = q.front();
                q.pop_front();

                if (visited[i] != -1) continue;
                visited[i] = wave;
                if (i == arr.size() - 1) return wave;

                if (i - 1 >= 0) {
                    q.push_back(i - 1);
                }

                if (i + 1 < arr.size()) {
                    q.push_back(i + 1);
                }

                if (!seen_vals.contains(arr[i])) {
                    seen_vals.insert(arr[i]);
                    for (int x : same_vals[arr[i]]) {
                        if (x == i || visited[x] != -1) continue;
                        q.push_back(x);
                    }   
                }
            }
            wave++;
        }

        throw logic_error("unreacable");
    }
};