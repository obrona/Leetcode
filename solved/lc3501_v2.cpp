#include <vector>
#include <ranges>
#include <print>
#include <iostream>
using namespace std;

// just use segment tree, but just tedious
// for each 1s grup surrounded by 0s group on both side, store the counts of 0s on both sides in a segtree
// for each query [l, r] need to edit the 1s group affected.
// then use segment tree, with the correct range query to get the max num of new 1s we can get.


struct segtree {
    int len;
    vector<int> tree;

    int left(int p) { return (p << 1) + 1; }

    int right(int p) { return (p << 1) + 2; }

    int mid(int s, int e) { return (s + e) >> 1; }

    segtree(int len): len(len), tree(4 * len, 0) {}

    segtree(const vector<int>& arr): len(arr.size()), tree(4 * len, 0) {
        if (arr.size() == 0) return;
        build(arr);
    }

    void build(const vector<int>& arr, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = arr.size() - 1;
        if (s == e) {
            tree[p] = arr[s];
            return;
        }
        int m = mid(s, e);
        build(arr, left(p), s, m);
        build(arr, right(p), m + 1, e);
        tree[p] = max(tree[left(p)], tree[right(p)]);
    }

    void add_point(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == e) {
            tree[p] += v;
            return;
        }
        int m = mid(s, e);
        if (i <= m) {
            add_point(i, v, left(p), s, m);
        } else {
            add_point(i, v, right(p), m + 1, e);
        }
        tree[p] = max(tree[left(p)], tree[right(p)]);
    }

    int query_range(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len -1;
        
        if (s == l && e == r) return tree[p];
        
        int m = mid(s, e);
        if (r <= m) {
            return query_range(l, r, left(p), s, m);
        } else if (l > m) {
            return query_range(l, r, right(p), m + 1, e);
        } else {
            return max(query_range(l, m, left(p), s, m), query_range(m + 1, r, right(p), m + 1, e));
        }

    }
};

struct p {
    char c;
    int i, start, end;
};

// returns vector of {char, start_idx, end_idx}.
// the interval is [start_idx, end_idx).
vector<p> group_consecutive(const string& s) {
    vector<p> out;
    int cnt = 0;
    for (int i = 0; i < s.size();) {
        char c = s[i];
        int start = i;
        while (s[i] == c) i++;
        out.emplace_back(c, cnt, start, i);
        cnt += c == '1';
    }
    return out;
}

bool is_in_range(int i, int start, int end) {
    return start <= i && i < end;
}

int get_idx_of_covering_range(const vector<p>& ranges, int i) {
    int s = 0, e = ranges.size() - 1;
    while (s <= e) {
        int m = (s + e) >> 1;
        auto [_c, _i, start, end] = ranges[m];
        if (is_in_range(i, start, end)) return m;
        if (i < start) {
            e = m - 1;
        } else {
            s = m + 1;
        }
    }
    return -1;
}

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        auto ranges = group_consecutive(s);
        //for (auto [c, i, start, end] : ranges) println("{} {} {} {}", c, i, start, end);
        int num_of_ones = ranges::distance(s | views::filter([] (char c) { return c == '1'; }));
        
        vector<int> scores;
        for (auto [i, p] : ranges | views::enumerate) {
            if (p.c == '0') continue;
            
            if (i == 0 || i == ranges.size() - 1) {
                scores.push_back(0);
                continue;
            }

            int score = ranges[i - 1].end - ranges[i - 1].start + ranges[i + 1].end - ranges[i + 1].start;
            scores.push_back(score);
        }
        
        //for (int x : scores) cout << x << " ";
        //cout << endl;
        
        segtree st(scores);
        //cout << st.query_range(0, 0) << endl;
        vector<int> out;

        for (const auto& query : queries) {
            int l = query[0], r = query[1];

            int l_idx = -1, l_edit = -1, r_idx = -1, r_edit = -1;

            int _lidx = get_idx_of_covering_range(ranges, l);
            if (ranges[_lidx].c == '1') {
                l_idx = ranges[_lidx].i + 1;
                l_edit = 0;
            } else {
                l_idx = ranges[_lidx].i;
                l_edit = l - ranges[_lidx].start;
                
            }

            //cout << l_idx << " " << l_edit << endl;
 
            int _ridx = get_idx_of_covering_range(ranges, r);
            if (ranges[_ridx].c == '1') {
                r_idx = ranges[_ridx].i - 1;
                r_edit = 0;
            } else {
                r_idx = ranges[_ridx].i - 1;
                r_edit = ranges[_ridx].end - r - 1;
            }

            //cout << r_idx << " " << r_edit << endl;

            int res = 0;
            if (l_idx == -1 || r_idx == -1 || l_idx >= scores.size() || r_idx < 0 || l_idx > r_idx) {
                res = num_of_ones;
            } else {
                st.add_point(l_idx, -l_edit);
                st.add_point(r_idx, -r_edit);
                int edit = st.query_range(l_idx, r_idx);
                res = num_of_ones + edit;

                st.add_point(l_idx, l_edit);
                st.add_point(r_idx, r_edit);
            }
            out.push_back(res);
        }

        return out;
    }
};

int main() {
    Solution sol;
    string s = "0101";
    vector<vector<int>> queries = {{0,3}};

    vector<int> ans = sol.maxActiveSectionsAfterTrade(s, queries);
    for (int x : ans) print("{} ", x);
    println();

}