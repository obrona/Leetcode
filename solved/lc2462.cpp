#include <vector>
#include <set>
#include <optional>
#include <stdexcept>
#include <iostream>
using namespace std;

// use 2 priority queue for the left candidates and the right candidates.
// just handle the cases (eg left candidate is the better one, right candidate is the better one)
// carefully.

struct pair_cmp {
    bool operator()(const pair<int,int>& p1, const pair<int,int>& p2) const {
        if (p1.second != p2.second) {
            return p1.second < p2.second;
        } else {
            return p1.first < p2.first;
        }
    }
};

class Solution {
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        set<pair<int,int>, pair_cmp> left_store, right_store;
        vector<int> used(costs.size(), -1);
        auto cmp = pair_cmp{};
        long long score = 0;
        int LEFT = 0, RIGHT = 1;
        int left_idx = candidates;
        int right_idx = costs.size() - 1 - candidates;

        for (int i = 0; i < candidates; i++) {
            left_store.emplace(i, costs[i]);
            used[i] = LEFT;
        }

        for (int i = costs.size() - 1; i > costs.size() - 1 - candidates; i--) {
            if (used[i] != -1) break;
            right_store.emplace(i, costs[i]);
            used[i] = RIGHT;
        }

        for (int i = 0; i < k; i++) {
            optional<pair<int,int>> lres, rres;
            bool popped_left = false, popped_right = false;
            if (!left_store.empty()) lres = *left_store.begin();
            if (!right_store.empty()) rres = *right_store.begin();

            if (lres && rres) {
                if (cmp(lres.value(), rres.value())) {
                    popped_left = true;
                    score += lres.value().second;
                } else {
                    popped_right = true;
                    score += rres.value().second;
                }
            } else if (lres) {
                popped_left = true;
                score += lres.value().second;
            } else if (rres) {
                popped_right = true;
                score += rres.value().second;
            } else {
                throw runtime_error("k <= costs.size(), so there should always be an worker for every round.");
            }

            if (popped_left) {
                left_store.erase(left_store.begin());
                if (left_idx < costs.size() && used[left_idx] == -1) {
                    left_store.emplace(left_idx, costs[left_idx]);
                    used[left_idx] = LEFT;
                    left_idx++;
                }
            }

            if (popped_right) {
                right_store.erase(right_store.begin());
                if (right_idx > -1 && used[right_idx] == -1) {
                    right_store.emplace(right_idx, costs[right_idx]);
                    used[right_idx] = RIGHT;
                    right_idx--;
                }
            }
        }

        return score;
    }
};

int main() {
    Solution sol;
    vector<int> costs = {17,12,10,2,7,2,11,20,8};
    int k = 3;
    int candidates = 4;

    long long ans = sol.totalCost(costs, k, candidates);
    cout << ans << endl;
}