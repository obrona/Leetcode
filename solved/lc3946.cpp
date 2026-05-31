#include <bits/stdc++.h>
using namespace std;

// knapsack dp.
// dp(idx, 1st time, budget left)
// for each item find how many free items it can get for the 1st time.

struct Store {
    int factor = 0;
    int price = 0;
    int num_free = 0;
};

class Solution {
public:

    vector<int> store;

    function<int(int,int,int)> to_pos;

    vector<Store> process(const vector<vector<int>>& items) {
        vector<Store> out;
        for (int i = 0; i < items.size(); i++) {
            Store& s = out.emplace_back();
            s.factor = items[i][0];
            s.price = items[i][1];
            for (int j = 0; j < items.size(); j++) {
                if (i == j) continue;
                if (items[j][0] % s.factor == 0) s.num_free++;
            }
        }
        return out;
    }

    int dp(int i, int b, int budget, const vector<Store>& items) {
        if (i == items.size() || budget == 0) return 0;
        
        int pos = to_pos(i, b, budget);
    
        int& ans = store[pos];
        if (ans != -1) return ans;

        int notake = dp(i + 1, true, budget, items);

        const auto& [_, price, num_free] = items[i];
        int take = 0;
        if (price <= budget) {
            take = ((b) ? 1 + num_free : 1) + dp(i, false, budget - price, items);
        }

        return ans = max(notake, take);
    }

    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        store = vector(2 * items.size() * (budget + 1), -1);
        to_pos = [budget] (int i, bool b, int bud) { return i * 2 * (budget + 1) + b * (budget + 1) + bud; };
        auto processed_items = process(items);

        int ans = dp(0, true, budget, processed_items);
        return ans;
    }   
};

int main() {
    Solution sol;
    vector<vector<int>> items = {{6,2}, {2,6}, {3,4}};
    int budget = 9;

    int ans = sol.maximumSaleItems(items, budget);
    println("{}", ans);
}