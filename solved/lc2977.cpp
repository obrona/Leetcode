#include <bits/stdc++.h>
#include <ranges>
using namespace std;
using ll = long long;

// cannot use string hashing too slow.
// use trie, build a trie for both original and changed.
// let dp(i) = min cost to convert source[i..n-1] to target[i..n-1]
// traverse the trie and check if source[i..j] is a substring in original and target[i..j] is a substring in changed.

// hash the strings in original, changed into 0, 1, 2, 3 ... 2n - 1
// use dijkstra for pair-wise shortest distance, it is better since the number of edges is small.

struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        auto [a, b] = p;
        return (ll) a + ((ll) b << 32);
    }
};

vector<vector<pair<int,int>>> get_adj_list(
    int n,
    const vector<int>& original, 
    const vector<int>& changed, 
    const vector<int>& cost
) {
    unordered_map<pair<int,int>, int, PairHash> store;
    for (int i = 0; i < original.size(); i++) {
        int src = original[i], dst = changed[i], c = cost[i];
        if (!store.contains({src, dst})) {
            store[{src, dst}] = c;
        } else {
            store[{src, dst}] = min(store[{src, dst}], c);
        }
    }

    vector<vector<pair<int,int>>> adj_list(n, vector<pair<int,int>>());
    for (const auto& [k, v] : store) {
        auto [src, dst] = k;
        adj_list[src].emplace_back(dst, v);
    }

    return adj_list;
}

// matrix[i][j] = -1 if no path.
vector<vector<int>> pair_wise_dijkstra(int n, const vector<vector<pair<int,int>>>& adj_list) {
    vector<vector<int>> out(n, vector<int>(n, -1));

    auto cmp = [] (const pair<int,int>& p1, const pair<int,int>& p2) { 
        return p1.second > p2.second; 
    };

    for (int i = 0; i < n; i++) {
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
        pq.emplace(i, 0);

        while (!pq.empty()) {
            auto [v, d] = pq.top(); pq.pop();
            if (out[i][v] != -1) continue;
            
            out[i][v] = d;
            for (auto [next, c] : adj_list[v]) {
                if (out[i][next] != -1) continue;
                pq.emplace(next, d + c);
            }
        }
    }

    return out;
}

struct Trie {
    int id = -1;
    array<Trie*, 26> nexts{};
};

void insert(Trie *curr, const string& s, int id, int i = 0) {
    if (i == s.size()) {
        curr->id = id;
        return;
    }

    int c = s[i] - 'a';
    Trie *&next = curr->nexts[c];
    if (next == nullptr) next = new Trie();
    insert(next, s, id, i + 1);
}

void cleanup(Trie *t) {
    if (!t) return;
    for (auto p : t->nexts) cleanup(p);
    delete t;
}

class Solution {
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        unordered_map<string, int> domain;
        for (const auto& s : original) {
            if (domain.contains(s)) continue;
            domain[s] = domain.size();
        }
        for (const auto& s : changed) {
            if (domain.contains(s)) continue;
            domain[s] = domain.size();
        }

        vector<int> original_id, changed_id;
        for (const auto& s : original) original_id.push_back(domain[s]);
        for (const auto& s : changed) changed_id.push_back(domain[s]);

        auto adj_list = get_adj_list(domain.size(), original_id, changed_id, cost);
        auto pair_wise_dist = pair_wise_dijkstra(domain.size(), adj_list);

        Trie *o_trie = new Trie(), *c_trie = new Trie();
        for (const auto& s : original) {
            insert(o_trie, s, domain[s]);
        }
        for (const auto& s : changed) {
            insert(c_trie, s, domain[s]);
        }

        vector<ll> store(source.size() + 1, 0); // + 1 to indicate out of string.
        for (int i = source.size() - 1; i > -1; i--) {
            bool same = true;
            auto curr_o_trie = o_trie;
            auto curr_c_trie = c_trie;
            ll &best = store[i] = 1e14;

            for (int j = i; j < source.size(); j++) {
                same = same && source[j] == target[j];

                curr_o_trie = (curr_o_trie == nullptr) ? nullptr : curr_o_trie->nexts[source[j] - 'a'];
                curr_c_trie = (curr_c_trie == nullptr) ? nullptr : curr_c_trie->nexts[target[j] - 'a'];

                if (same) {
                    best = min(best, store[j + 1]);
                    continue;
                }

                int o_id = (curr_o_trie == nullptr) ? -1 : curr_o_trie->id;
                int c_id = (curr_c_trie == nullptr) ? -1 : curr_c_trie->id;
                
                if (o_id != -1 && c_id != -1) {
                    ll d = pair_wise_dist[o_id][c_id];
                    if (d == -1) continue;
                    
                    best = min(best, d + store[j + 1]);
                }  
            }
        }

        cleanup(o_trie);
        cleanup(c_trie);

        return (store[0] >= 1e14) ? -1 : store[0];
    }
};

int main() {
    Solution sol;
    string source = "abcd";
    string target = "acbe";
    vector<string> original = {"a", "b", "c", "c", "e", "d"};
    vector<string> changed = {"b","c","b","e","b","e"};
    vector<int> cost = {2,5,5,1,2,20};

    ll ans = sol.minimumCost(source, target, original, changed, cost);
    println("Ans: {}", ans);
}