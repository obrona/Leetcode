#include <bits/stdc++.h>
using namespace std;

// compare word[i] with word[i + 1]. at index i where word[i][k] != word[i + 1][k], that is a directed edge
// in the partial order.
// comparing consecutive word pairs is sufficient.
// once we get the directed edges, do toposort.

struct PairCharHash {
    std::size_t operator()(const std::pair<char, char>& p) const noexcept {
        return (static_cast<unsigned char>(p.first) << 8) |  static_cast<unsigned char>(p.second);
    }
};

auto get_edges(const vector<string>& words) {
    using Res = unordered_set<pair<char,char>, PairCharHash>;
    Res out;
    for (int i = 0; i < words.size() - 1; i++) {
        const auto &w1 = words[i], &w2 = words[i + 1];
        int lim = min(w1.size(), w2.size());
        int j = 0;
        for (; j < lim; j++) {
            if (w1[j] == w2[j]) continue;
            
            if (out.contains({w2[j], w1[j]})) {
                return optional<Res>();
            } else {
                out.emplace(w1[j], w2[j]);
            }
            break;
        }

        if (j == w2.size() && j < w1.size()) return optional<Res>();
    }
    return make_optional(out);
}

template <typename Hash>
unordered_map<char, vector<char>> make_adj(unordered_set<pair<char,char>, Hash> edges) {
    unordered_map<char, vector<char>> out;
    for (auto [src, dest] : edges) out[src].push_back(dest);
    return out;
}

optional<string> topo_sort(const unordered_map<char, vector<char>>& edges) {
    vector<bool> visit(26, false);
    vector<bool> done(26, false);
    string store;

    function<bool(char)> dfs = [&] (char c) {
        int idx = c - 'a';
        if (done[idx]) return true;
        if (visit[idx]) return false;

        visit[idx] = true;
        if (edges.contains(c)) {
            const auto& nexts = edges.at(c);
            for (char n : nexts) {
                if (!dfs(n)) return false;
            }
        }
       
        store.push_back(c);
        done[idx] = true;
        return true;
    };

    for (const auto& [c, nexts] : edges) {
        if (!dfs(c)) return nullopt;
    }
    reverse(store.begin(), store.end());
    return optional(store);
}

class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        auto edges = get_edges(words);
        if (!edges) return "";
        auto adj = make_adj(edges.value());
        
        auto ans = topo_sort(adj);
        if (!ans) return "";

        auto store = unordered_set<char>(ans.value().begin(), ans.value().end());
        // need to add chars that are in words but do not participate in edges at all.
        for (auto& w : words) {
            for (char c : w) {
                if (!store.contains(c)) {
                    ans.value() += c;
                    store.insert(c);
                }
            }
        }
        return ans.value();
    }
};

int main() {
    Solution sol;
    vector<string> words = {"abcdefgh","bdefghij","cghij","dfghij","efghij","fghij","ghij","hij","ij","j","abcdefghi","bdefghijk","cghijk","dfghijk","efghijk","fghijk","ghijk","hijk","ijk","jk","k"};
    auto ans = sol.foreignDictionary(words);
    cout << ans << endl;
}
