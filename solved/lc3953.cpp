#include <bits/stdc++.h>
using namespace std;

// for each value x, we want to know how many elems are not coprime.
// this means x and elem share at least 1 common prime factor.
// suppose x's prime factors are 2, 3, 11, 17, 23
// then we use inclusion exclusion principle to find S(2) U S(3) U S(11) ... 

// the largest number we encounter is 10^5, so each number can have at most 6 prime factors.
// so the PIE is quite fast at 2^6 = 64.

// modified Sieve to include the prime factors.
// so this also gives us the prime factors of a number x.
// this means we give up some optimisations.
struct Sieve {
    vector<bool> store;
    vector<vector<int>> my_primes;

    Sieve(int n): store(n + 1, true), my_primes(n + 1, vector<int>()) {
        store[0] = store[1] = false;
        for (int i = 2; i <= n; i++) {
            if (!store[i]) continue;
            
            for (size_t k = i; k <= (size_t) n; k += i) {
                my_primes[k].push_back(i);
                if (k > i) store[k] = false;
            }
        }
    }

    bool is_prime(int n) const {
        return store[n];
    }

    vector<int> get_prime_factors(int n) const {
        return my_primes[n];
    }
};

const Sieve sieve(100000);

class Solution {
public:
    unordered_map<int, int> prime_count;

    // for each n, we get the prime factor, then for each subset we increment the count.
    void process(int n) {
        vector<int> prime_factors = sieve.get_prime_factors(n);
        
        for (int bs = 1; bs < (1 << prime_factors.size()); bs++) {
            int a = 1;
            
            for (int i = bs, pow = 0; i > 0; i >>= 1, pow++) {
                if (i & 1) a *= prime_factors[pow];
            }

            prime_count[a]++;
        }
        
    }

    int find_num_not_coprimes(int n) {
        vector<int> prime_factors = sieve.get_prime_factors(n);
        
        int cnt = 0;
        for (int bs = 1; bs < (1 << prime_factors.size()); bs++) {
            int num_1_bits = popcount<unsigned int>(bs);
            int sign = (num_1_bits % 2 == 1) ? 1 : -1;

            int a = 1;
            for (int i = bs, pow = 0; i > 0; i >>= 1, pow++) {
                if (i & 1) a *= prime_factors[pow];
            }

            cnt += prime_count[a] * sign;
        }

        return cnt;
    }

    int maxScore(vector<int>& nums, int maxVal) {
        unordered_set<int> nums_set(nums.begin(), nums.end());
        for (int x : nums) process(x);
        
        int best = 1; // edge case when x = 1, all elems are coprime to it, so we change nothing.
        for (int i = 2; i <= maxVal; i++) {
            int not_coprime = find_num_not_coprimes(i);

            // a number is not coprime to itself. 
            // we remove all counts of i in nums except 1 which we keep.
            // the rest need to change.
            if (nums_set.contains(i)) not_coprime--; 
            
            if (not_coprime == 0) {
                int to_change = (nums_set.contains(i)) ? 0 : 1;
                best = max(best, i - to_change);
            } else {
                // if i exists, then just need to change all not coprime
                // if i does not exist, then 1 not coprime change to i, everyone else change to coprime.
                // either way num changes is just num of not coprime.
                best = max(best, i - not_coprime);
            }
        }

        for (int x : nums_set) {
            if (x <= maxVal) continue;
            int not_coprime = find_num_not_coprimes(x);

            if (nums_set.contains(x)) not_coprime--; 

            if (not_coprime == 0) {
                int to_change = (nums_set.contains(x)) ? 0 : 1;
                best = max(best, x - to_change);
            } else {
                // if i exists, then just need to change all not coprime
                // if i does not exist, then 1 not coprime change to i, everyone else change to coprime.
                // either way num changes is just num of not coprime.
                best = max(best, x - not_coprime);
            }
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1000};
    int maxVal = 1000;

    int ans = sol.maxScore(nums, maxVal);
    cout << ans << endl;
}