#include <bits/stdc++.h>
using namespace std;

// python always TLE, no choice try c++.
// 2 pointer problem.
// at index 0, go as far right as possible.
// at index 1, remove the prime factors from nums[0] and continue as far right as possible.

// need more optimisation.
// need smallest prime factor sieve.
// in sieve, for each number, store the smallest prime factor.
// that builds a 'routing table' we can jump to each prime factor directly instead of testing each prime.
// so factorisation runs in log(n).

vector<int> get_smallest_prime(int n) {
    vector<int> out(n + 1, n + 1);
    iota(out.begin(), out.end(), 0);
    for (int i = 2; i <= n; i++) {
        if (out[i] < i) continue;
        for (long long j = (long long) i * i; j <= n; j += i) out[j] = min(out[j], i);
    }
    return out;
}

unordered_map<int,int> factorise(int x, const vector<int>& smallest_primes) {
    if (x < 2 || x >= smallest_primes.size()) {
        throw invalid_argument("x is out of range");
    }

    int temp = x;
    unordered_map<int,int> out;
    while (temp > 1) {
        out[smallest_primes[temp]] += 1;
        temp /= smallest_primes[temp];
    }
    return out;
}

auto smallest_primes = get_smallest_prime(100000);

class Solution {
public:
    int longestSubarray(vector<int>& nums, int k) {
        unordered_map<int,int> cnter;

        auto add = [&] (const unordered_map<int,int>& factors) {
            for (auto [k, v] : factors) {
                cnter[k] += v;
            }
        };

        auto remove = [&] (const unordered_map<int,int>& factors) {
            for (auto [k, v] : factors) {
                cnter[k] -= v;
                if (!cnter[k]) cnter.erase(k);
            }
        };

        int best = 0;
        int p = 0;
        for (int i = 0; i < nums.size(); i++) {
            p = max(p, i);
            for (; p < nums.size(); p++) {
                auto f = factorise(nums[p], smallest_primes);
                add(f);
                if (cnter.size() > k) {
                    remove(f);
                    break;
                }
            }
            best = max(best, p - i);
            if (p > i) remove(factorise(nums[i], smallest_primes));
        }
        return best;
    }
};

int main() {
    /*for (int i = 0; i < smallest_primes.size(); i++) {
        cout << smallest_primes[i] << endl;
    }*/
    Solution sol;
    vector<int> nums = {7,6,10,12,11};
    int k = 3;
    int ans = sol.longestSubarray(nums, k);
    cout << ans << endl;
}