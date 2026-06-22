#include <bits/stdc++.h>
using namespace std;

// let f(i, j) be the cost to convert source[i..j] to target[i..j].
// to find the mininum cost to convert source to target, O(n^2) dp is easy to see.
// use bottom up dp for fun?

// hash the strings and then run floyd warshall to find shortest path.

long long mulmod(long long a, long long b, long long m) {
    return (__int128)a * b % m;
}

long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long modInverse(long long a, long long mod) {
    long long x, y;
    long long g = extgcd(a, mod, x, y);
    // g != 1 means inverse doesn't exist
    return (x % mod + mod) % mod;
}

long long power(long long x, long long p, long long m) {
    long long result = 1;
    x %= m;
    while (p > 0) {
        if (p & 1) result = (__int128)result * x % m;  
        x = (__int128)x * x % m;                       
        p >>= 1;
    }
    return result;
}

long long string_hash(const string& s) {
    static const long long p = 31, m = 1e9 + 7, inv = modInverse(p, m);
    long long acc = 0;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a' + 1; // must add 1 otherwise a becomes 0, causes hash collision eg "aa" and "a"
        acc = (acc + c * power(p, i, m)) % m;
    }
    return acc;
}

struct StringHash {
    long long p = 31, m = 1e9 + 7, inv = modInverse(p, m);
    vector<long long> prefix_hash;
    vector<long long> inv_arr;

    StringHash(const string& s): prefix_hash(s.size(), 0), inv_arr(s.size() + 1, 1) {
        long long acc = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a' + 1;
            acc = (acc + c * power(p, i, m)) % m;
            prefix_hash[i] = acc;
        }

        inv_arr[1] = inv;
        for (int i = 2; i < inv_arr.size(); i++) {
            inv_arr[i] = mulmod(inv_arr[i - 1], inv, m);
        }

    }

    long long get_string_hash_val() {
        return prefix_hash.back();
    }

    long long get_substring_hash_val(int l, int r) {
        long long lres = (l == 0) ? 0 : prefix_hash[l - 1];
        long long rres = prefix_hash[r];
        long long ans = (rres - lres + m) % m;
        long long div = inv_arr[l];
        return mulmod(ans, div, m);
    }   
};

unordered_map<long long, unordered_map<long long, long long>> get_adj_mat(
    const vector<long long>& original, 
    const vector<long long>& changed,
    const vector<int>& cost
) {
    unordered_map<long long, unordered_map<long long, long long>> mat;

    for (int i = 0; i < original.size(); i++) {
        long long h1 = original[i], h2 = changed[i];
        if (mat[h1].contains(h2)) {
            mat[h1][h2] = min(mat[h1][h2], (long long) cost[i]);
        } else {
            mat[h1][h2] = cost[i];
        }
    }

    return mat;
}

unordered_map<long long, unordered_map<long long, long long>> floyd_warshall(
    const unordered_map<long long, unordered_map<long long, long long>>& mat,
    const unordered_set<long long>& domain
) {
    unordered_map<long long, unordered_map<long long, long long>> store;
    
    for (long long src : domain) {
        for (long long dest : domain) {
            if (src == dest) {
                store[src][dest] = 0;
            }  
            
            else if (!mat.contains(src) || !mat.at(src).contains(dest)) {
                store[src][dest] = 1e14;
            }

            else {
                store[src][dest] = mat.at(src).at(dest);
            }
            
            
            
        }
    }

    for (long long v : domain) {
        //auto temp = store;
        for (long long src : domain) {
            for (long long dest : domain) {
                store[src][dest] = min(store[src][dest], store[src][v] + store[v][dest]);
            }
        }
    }

    return store;
}

class Solution {
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        vector<long long> original_hash, changed_hash;
        for (const string& s : original) original_hash.push_back(string_hash(s));
        for (const string& s : changed) changed_hash.push_back(string_hash(s));

        unordered_set<long long> domain;
        domain.insert(original_hash.begin(), original_hash.end());
        domain.insert(changed_hash.begin(), changed_hash.end());

        auto adj_mat = get_adj_mat(original_hash, changed_hash, cost);
        auto dists = floyd_warshall(adj_mat, domain);

        auto helper = [&dists] (long long src, long long dst) -> long long {
            if (src == dst) return 0LL;
            if (!dists.contains(src) || !dists.at(src).contains(dst)) return 1e14;
            return dists.at(src).at(dst);
        };

        StringHash source_hash{source}, target_hash{target};
        vector<long long> store(source.size(), 1e14);
        
        for (int i = source.size() - 1; i >= 0; i--) {
            long long best = 1e14;
            for (int j = i; j < source.size(); j++) {
                auto h1 = source_hash.get_substring_hash_val(i, j);
                auto h2 = target_hash.get_substring_hash_val(i, j);
                auto next = (j + 1 >= source.size()) ? 0 : store[j + 1];
                best = min(best, helper(h1, h2) + next);
            }

            store[i] = best;
        }

        return store[0] >= 1e14 ? -1 : store[0];
    }
};

int main() {
    Solution sol;
    auto source = "abcd";
    auto target = "acbe";
    vector<string> original = {"a","b","c","c","e","d"};
    vector<string> changed = {"b","c","b","e","b","e"};
    vector<int> cost = {2,5,5,1,2,20};

    auto ans = sol.minimumCost(source, target, original, changed, cost);
    println("Ans: {}", ans);
}