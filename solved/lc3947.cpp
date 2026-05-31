#include <bits/stdc++.h>
using namespace std;

// greedy.
// for certain elements, paying the original price gets you 2 items.
// sometimes we can get 1 element at x price or 2 elements at y price.
// use a priority queue, the top element is the element with the lowest per unit price.

// the greedy proof is quite easy, always take the 'package' with the lower per unit price
// unless you cannot afford it or you run out of the '2 items package'.
// works because the '1 item package' is infinite.

struct S {
    bool is_2 = false;
    int max_cnt = 0;
    double per_unit_price = 0;
};

struct CmpS {
    bool operator()(S s1, S s2) {
        return s1.per_unit_price > s2.per_unit_price;
    }
};

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        unordered_map<int,int> m1;
        for (auto& item : items) {
            m1[item[0]] += 1;
        }

        unordered_map<int,int> m2;
        for (auto [k, v] : m1) {
            m2[k] = v - 1;
            for (int p = 2 * k; p <= items.size(); p += k) {
                if (!m1.contains(p)) continue;
                m2[k] += m1[p];
            }
        }

        priority_queue<S, vector<S>, CmpS> pq1;
        for (auto& item : items) {
            if (m2.contains(item[0])) {
                pq1.emplace(true, m2[item[0]], item[1] / 2.0);
            }

            pq1.emplace(false, -1, item[1]);
        }

        int total = 0;
        while (budget > 0 && !pq1.empty()) {
            S s = pq1.top();
            pq1.pop();
            
            int price = (s.is_2) ? s.per_unit_price * 2 : s.per_unit_price;
            if (price > budget) continue;

            if (s.is_2) {
                int max_buys = min(budget / price, s.max_cnt);
                total += 2 * max_buys;
                budget -= max_buys * price;
            } else {
                int max_buys = budget / price;
                total += max_buys;
                budget -= max_buys * price;
            }
        }

        return total;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> items = {{1,6}, {2,4}, {3,5}};
    int budget = 19;
    int ans = sol.maximumSaleItems(items, budget);
    println("{}", ans);
}