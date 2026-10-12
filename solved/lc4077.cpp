#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// main problem per node is
// given k sets, determine the permutation that results in the least amount of inversions between sets.
// for each node, we get the set for each children.
// let c[i][j] be the num of inversions if set[i] is ordered before set[j].

// have to do bitset dp of time complexity O(k^2 * 2^k)
// dp(bm) = optimal way to order all sets in bm
// for dp(bm) the last set can be a, b, c, so test them all.
// dp(bm) = min(dp(bm - 1 << last) + sum(c[i][last] for i in rest of sets in bm))

// can optimise it to O(k * 2^k).
// precompute c'[mask][j] (cost of appending j back to sets contained in mask, the sets can be arranged in any order)
// c'[mask][j] = c'[mask - i][j] + c[i][j] for any i in mask
// then for each last set we are going to check, we do not need to sum ovr the rest of the sets in bitmask.

// some constant factor optimisations.
// c[j][i] = size_i * size_j - c[i][j]
// use flat array instead of 2d array.
// cannot use pbds, use a sorted vector.
// this is because length of word is <= 20.
// the trie depth is at most 20.
// but we have 10^4 leaves, so each node on average must branch 3.5 times. (20^3.5 around 10000).
// so each idx is merge around 20 * 4 times.

template <typename T>
using ordered_set = tree<
    T,                          // key type
    null_type,                  // mapped type (null_type = set, not map)
    less<T>,                    // comparator
    rb_tree_tag,                // underlying tree structure
    tree_order_statistics_node_update  // the "policy" that maintains subtree sizes
>;



// count number of inversions when a is ordered before b.
// a, b are mutually exclusive.
int count_inversion(const vector<int>& a, const vector<int>& b) {
    int cnt = 0;
    int p2 = b.size() - 1;
    for (int p1 = a.size() - 1; p1 > -1; p1--) {
        while (p2 > -1 && a[p1] < b[p2]) p2--;
        cnt += p2 + 1;
    }
    return cnt;
}

int find_optimal_ordering(const vector<vector<int>>& sets) {
    int N = sets.size();
    vector<vector<int>> c(sets.size(), vector<int>(N, 0));
    for (int i{0}; i < N; i++) {
        for (int j{i + 1}; j < N; j++) {
            if (i == j) continue;
            c[i][j] = count_inversion(sets[i], sets[j]);
            c[j][i] = sets[i].size() * sets[j].size() - c[i][j];
        }
    }

    //vector<vector<int>> cost(1 << N, vector<int>(N, 0));
    vector<int> cost((1 << N) * N, 0);
    for (unsigned int bm = 1; bm < (1 << N); bm++) {
        for (int j = 0; j < N; j++) {
            if ((bm >> j) & 1) continue;
            
            // take lsb.
            int i = countr_zero(bm);
            int prev = bm & (bm - 1);
            cost[bm * N + j] = cost[prev * N + j] + c[i][j];
        }
    }

    vector<int> store(1 << N, 0);
    for (unsigned int bm = 1; bm < (1 << N); bm++) {
        int best = int(1e8);
        for (auto mask = bm; mask; mask &= mask - 1) {
            int last = countr_zero(mask);
            int prev = bm - (1 << last);
            best = min(best, store[prev] + cost[prev * N + last]);
        }
        store[bm] = best;
    }

    return store.back();    
}



struct Res {
    vector<int> nums;
    int inversions = 0;
};

struct node {
    optional<int> word_idx;
    array<unique_ptr<node>, 10> nexts;

    void insert(const string& s, int idx, int i = 0) {
        if (i == s.size()) {
            word_idx = idx;
            return;
        }

        char c = s[i];
        auto& next = nexts[c - 'a'];

        if (!next) {
            next = make_unique<node>();
        }

        next->insert(s, idx, i + 1);
    }


    Res dfs() {
        vector<node*> children;
        for (auto& uptr : nexts) {
            if (uptr) children.push_back(uptr.get());
        }

        if (children.size() == 0) {
            Res res;
            res.nums.emplace_back(word_idx.value());
            return res;
        }

        if (children.size() == 1) {
            Res res = children[0]->dfs();
            if (word_idx) {
                res.inversions += lower_bound(res.nums.begin(), res.nums.end(), word_idx.value()) - res.nums.begin();
                res.nums.push_back(word_idx.value());
                inplace_merge(res.nums.begin(), res.nums.end() - 1, res.nums.end());
            }
            return res;
        }

        int inversions = 0;
        vector<vector<int>> sets;
        for (auto c : children) {
            Res cres = c->dfs();
            inversions += cres.inversions;

            if (word_idx) {
                inversions += lower_bound(cres.nums.begin(), cres.nums.end(), word_idx.value()) - cres.nums.begin();
            }

            sets.push_back(move(cres.nums));
        }

        inversions += find_optimal_ordering(sets);

        auto& curr = sets[0];
        for (size_t i = 1; i < sets.size(); i++) {
            auto& s = sets[i];
            int sz = curr.size();
            curr.insert(curr.end(), s.begin(), s.end());
            inplace_merge(curr.begin(), curr.begin() + sz, curr.end());
        }

        if (word_idx) {
            curr.emplace_back(word_idx.value()); 
            inplace_merge(curr.begin(), curr.end() - 1, curr.end());
        }

        return Res{
            .nums = move(curr),
            .inversions = inversions
        };
    }
    
};




class Solution {
public:
    int minInversions(vector<string>& words, vector<int>& target) {
        auto root = make_unique<node>();
        unordered_map<int, int> mapper;
        
        for (int i = 0; i < target.size(); i++) {
            mapper[target[i]] = i;
        }
        
        for (int i = 0; i < words.size(); i++) {
            root->insert(words[i], mapper[i]);
        }

        Res res = root->dfs();
        return res.inversions;
    }
};


int main() {
    Solution sol;
    vector<string> words = {"bad", "bag", "fig", "fed"};
    vector<int> target = {3,1,0,2};

    int ans = sol.minInversions(words, target);
    cout << ans << endl;

}