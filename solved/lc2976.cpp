#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// we want to find the shortest cost to convert char c1 to char c2.
// run floyd warshall for O(V^3) to find pairwise shortest distance.

vector<vector<ll>> make_adj(const vector<char>& src, const vector<char>& dst, const vector<int>& cost) {
    vector<vector<ll>> adj_mat(26, vector(26, (ll) 1e14));
    for (int i = 0; i < src.size(); i++) {
        int s = src[i] - 'a';
        int d = dst[i] - 'a';
        int c = cost[i];
        adj_mat[s][d] = min(adj_mat[s][d], (ll) c);
    }
    return adj_mat;
}

vector<vector<ll>> floyd_warshall(const vector<vector<ll>>& adj_mat) {
    vector<vector<ll>> mat(26, vector(26, (ll) 1e14));
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (i == j) {
                mat[i][j] = 0;
                continue;
            }
            mat[i][j] = adj_mat[i][j];
        }
    }

    for (int v = 0; v < 26; v++) {
        vector<vector<ll>> temp = mat;
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                temp[i][j] = min(mat[i][j], mat[i][v] + mat[v][j]);
            }
        }  
        mat = temp;
    }

    return mat;
}

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        auto adj_mat = make_adj(original, changed, cost);
        auto mat = floyd_warshall(adj_mat);

        ll res = 0;
        for (int i = 0; i < source.size(); i++) {
            res += mat[source[i] - 'a'][target[i] - 'a'];
        }

        return (res >= (ll) 1e14) ? -1 : res;
    }
};

int main() {
    Solution sol;
    string source = "abcd";
    string target = "acbe";
    vector<char> original = {'a', 'b', 'c', 'c', 'e', 'd'};
    vector<char> changed = {'b', 'c', 'b', 'e', 'b', 'e'};
    vector<int> cost = {2, 5, 5, 1, 2, 20};

    ll ans = sol.minimumCost(source, target, original, changed, cost);
    println("Ans: {}", ans);
}