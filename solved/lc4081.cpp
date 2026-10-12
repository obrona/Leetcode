#include <bits/stdc++.h>
using namespace std;

// dp(i, s) = (sum, num) = maximum sum <= s and minimum num from primes[i:].
// just need to reconstruct solution, so we need to build a routing table.
// smallest lexicographical order means at index i, if selecting and skipping
// returns the same pair, then we select.

vector<int> get_primes(int n) {
    vector<bool> is_prime(n + 1, 1);
    is_prime[0] = is_prime[1] = 0;

    for (int i = 2; i <= (int) sqrt(n); i++) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            is_prime[j] = 0;
        }
    }

    vector<int> out;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) out.push_back(i);
    }

    return out;
}

struct Res {
    int sum;
    int num;
    bool take;
};

class Solution {
public:
    vector<vector<optional<Res>>> store;
    vector<int> primes; // primes from 2 to n, in increasing order.

    Res dp(int i, int s) {
        if (i >= primes.size() || s == 0) {
            return {.sum = 0, .num = 0, .take = 0};
        }

        auto& res = store[i][s];
        if (res) {
            return res.value();
        }

        if (primes[i] > s) {
            res = {.sum = 0, .num = 0, .take = 0};
            return res.value();
        }

        Res notake = dp(i + 1, s);
        Res take = dp(i + 1, s - primes[i]);
        take.sum += primes[i];
        take.num++;
        take.take = 1;

        if (notake.sum > take.sum || notake.sum == take.sum && notake.num < take.num) {
            res = notake;
            res.value().take = 0;
            return res.value();
        } else {
            res = take;
            return res.value();
        }
    }

    vector<int> reconstruct(int s) {
        vector<int> out;
        for (int i = 0; i < primes.size(); i++) {
            Res res = dp(i, s);
            if (res.take) {
                out.push_back(primes[i]);
                s -= primes[i];
            }
        }
        return out;
    }


    vector<int> maxPrimeSubset(int n, int s) {
        primes = get_primes(n);
        store = vector(primes.size(), vector(s + 1, optional<Res>()));
        return reconstruct(s);
    }
};

int main() {
    Solution sol;
    int n = 15, s = 18;

    auto ans = sol.maxPrimeSubset(n, s);
    for (int x : ans) cout << x << " ";
    cout << endl;
}