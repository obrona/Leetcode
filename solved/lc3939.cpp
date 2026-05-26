#include <bits/stdc++.h>
using namespace std;


// more difficult tree dp
// dp(v, c, target, is_parent_taken, is_v_taken)
// c means we are considering adj[v][c:].
// target is the target sum (mod k) we are trying to get.

// we can only choose to take v when c = 0
// otherwise the decision is already made and we cannot change it

// at each state, for children[c], we find how many ways to achieve target sum of x
// and for the remaining children we find how many ways to achieve a target sum of y
// s.t x + y = 0 (mod k).

// the time complexity is O(nk^2) which is correct but is so strict

// 0 <= parent[i] < i for all i > 0 which is useless because we can always relabel
// but we use this fact in our botttom up dp.

const int MOD = 1e9 + 7;

/*struct Hash {
    inline size_t operator()(const std::tuple<int, int, int, bool, bool>& tup) const {
        auto [a, b, c, d, e] = tup;
        return a + (b << 10) + (c << 20) + (d << 27) + (e << 28);
    }
};*/



inline int add(int a, int b, int k = MOD) {
    return (a + b) % k;
}

// return (a - b) mod k
inline int sub(int a, int b, int k) {
    return (a - b + k) % k;
}

inline int mult(int a, int b) {
    long long ans = (long long) a * b;
    return (ans < MOD) ? ans : ans % MOD;
}

// max length is 2000 * 100 * 2 * 2 = 400000
int store[8000000] = {-1};

class Solution {
public:
    // tree adj list
    int N;
    vector<vector<int>> adj;
    // modulo k already
    vector<int> nums; 
    int k;

    int row_len;
    vector<int> prefix_sums;

    // have to compress because the total number of (v, c) pairs is O(n) not O(n^2)
    // so compress using prefix sums
    inline int get_pos(int v, int c, int target, int b1, int b2) {
        return prefix_sums[v] + c + row_len * ((target << 2) | (b1 << 1) | b2);
    }

    vector<vector<int>> waves;

    void dfs(int v, int d) {
        waves[d].push_back(v);
        for (int c : adj[v]) {
            dfs(c, d + 1);
        }
    }



    void make_tree_adj(vector<int>& parent) {
        adj = vector(parent.size(), vector<int>());
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] == -1) continue;
            adj[parent[i]].push_back(i);
        }
    }


    // top down dp TLE, this question has very tight time limit.
    int dp(int v, int c, int target, bool is_parent_taken, bool is_v_taken) {
        auto& children = adj[v];
        
        if (children.size() == 0) {
            return (target == 0) + (!is_parent_taken && nums[v] == target);
        }

        if (c == children.size()) {
            return target == 0;
        }

        int key = get_pos(v, c, target, is_parent_taken, is_v_taken);
        if (store[key] != -1) return store[key];
        int total = 0;

        // notake
        for (int t = 0; t < k; t++) {
            int d = target - t;
            if (d < 0) d += k;
            
            int x = dp(children[c], 0, t, is_v_taken, false);
            int y = dp(v, c + 1, d, is_parent_taken, is_v_taken);
            
            total += mult(x, y);
            if (total >= MOD) total -= MOD;
        }
 
        // take
        if (!is_parent_taken && c == 0) {
            int new_target = target - nums[v];
            if (new_target < 0) new_target += k;

            for (int t = 0; t < k; t++) {
                int d = new_target - t;
                if (d < 0) d += k;
                
                int x = dp(children[c], 0, t, true, false);
                int y = dp(v, c + 1, d, is_parent_taken, true);
                
                total += mult(x, y);
                if (total >= MOD) total -= MOD;
            }
        } 

        return store[key] = total;
    }

    // try to avoid modulo as much as possible, only after removing as much modulo as possible can I pass
    // the test cases.
    // we check the value if it is invalid (eg for substract, result is < 0) we change accordingly.
    void bottom_up_dp() {
        for (int v = N - 1; v >= 0; v--) {
            auto& children = adj[v];
            
            for (int c = children.size(); c >= 0; c--) {

                for (int target = 0; target < k; target++) {

                    for (int is_parent_taken = 0; is_parent_taken < 2; is_parent_taken++) {

                        for (int is_v_taken = 0; is_v_taken < 2; is_v_taken++) {

                            int pos = get_pos(v, c, target, is_parent_taken, is_v_taken);
                            int& total = store[pos] = 0;

                            if (children.size() == 0) {
                                total = (target == 0) + (!is_parent_taken && nums[v] == target);
                                continue;
                            }

                            if (c == children.size()) {
                                total = (target == 0);
                                continue;
                            }

                            // no take
                            for (int t = 0; t < k; t++) {
                                int d = target - t;
                                if (d < 0) d += k;
            
                                int x = store[get_pos(children[c], 0, t, is_v_taken, false)];
                                int y = store[get_pos(v, c + 1, d, is_parent_taken, is_v_taken)];
                                
                                total += mult(x, y);
                                if (total >= MOD) total -= MOD;
                            }

                            // take
                            if (!is_parent_taken && c == 0) {
                                int new_target = target - nums[v];
                                if (new_target < 0) new_target += k;

                                for (int t = 0; t < k; t++) {
                                    int d = new_target - t;
                                    if (d < 0) d += k;
                                    
                                    int x = store[get_pos(children[c], 0, t, true, false)];
                                    int y = store[get_pos(v, c + 1, d, is_parent_taken, true)];
                                    
                                    total += mult(x, y);
                                    if (total >= MOD) total -= MOD;
                                }
                            } 


                        }
                    }
                }
            }
        }
    }

    int countValidSubsets(vector<int>& parent, vector<int>& nums, int k) {

        N = parent.size();
        make_tree_adj(parent);
        this->nums = std::move(nums);
        for (int& x : this->nums) x %= k;
        this->k = k;

        row_len = 2 * parent.size() - 1; // actually number of states of (v, child) is just number of edges
        prefix_sums = vector(parent.size(), 0);
        for (int i = 0; i < parent.size(); i++) {
            if (i == 0) {
                prefix_sums[i] = 0;
            } else {
                prefix_sums[i] = prefix_sums[i - 1] + adj[i - 1].size() + 1;
            }
        }

        /*for (int v = N - 1; v >= 0; v--) {
            auto& children = adj[v];
            
            for (int c = children.size(); c >= 0; c--) {

                for (int target = 0; target < k; target++) {

                    for (int is_parent_taken = 0; is_parent_taken < 2; is_parent_taken++) {

                        for (int is_v_taken = 0; is_v_taken < 2; is_v_taken++) {

                           store[get_pos(v, c, target, is_parent_taken, is_v_taken)] = -1;

                        }
                    }
                }
            }
        }*/

        //int ans = dp(0, 0, 0, false, false);
        bottom_up_dp();
        int ans = store[get_pos(0, 0, 0, false, false)];
        return (ans == 0) ? 1000000006 : ans - 1;  // the empty set is also taken but we dont want that so ans is at least 1.
    }
};

int main() {
    Solution sol;
    vector<int> parent = {-1,0,0,0};
    vector<int> nums = {2,1,2,1};
    int k = 3;
    int ans = sol.countValidSubsets(parent, nums, k);
    cout << ans << endl;
}