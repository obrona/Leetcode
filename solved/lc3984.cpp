#include <bits/stdc++.h>
using namespace std;

// get all prime numbers in [1, 1e6].
// then for each number, get its prime factors. time is < O(sqrt(N)) for each number.
// so 10^3 * 10^3 should be fine.

// k has to be a prime number.
// suppose k is not prime, take a prime factor of k.
// will only have more numbers divisble by k, so score difference gets bigger.
// if arr[i] is divisble by k, leave as it, if not make it neg.
// use kadane algo to find the max subarray.

const int M = 1000000007;

struct Sieve {
    vector<bool> store;
    vector<int> primes;

    Sieve(int n): store(n + 1, true) {
        store[0] = store[1] = false;

        int lim = (int) floor(sqrt(n));
        for (int i = 2; i <= n; i++) {
            if (i > lim) break;
            if (store[i]) {
                for (int j = i * i; j <= n; j += i) {
                    store[j] = false;
                }
            }
        }

        for (int i = 2; i <= n; i++) {
            if (store[i]) {
                primes.push_back(i);
            }
        }
    }
};

const Sieve sieve(1000000);

int kadane(const vector<int>& arr) {
    vector<int> store(arr.size(), 0);
    for (int i = 0; i < arr.size(); i++) {
        int prev = i == 0 ? -2e9 - 1 : store[i - 1];
        store[i] = max(arr[i], arr[i] + prev);
    }
    return *max_element(store.begin(), store.end());
}

class Solution {
public:
    int divisibleGame(vector<int>& nums) {
        unordered_set<int> poss;
        for (int x : nums) {
            if (sieve.store[x]) {
                poss.insert(x);
                continue;
            }

            for (int p : sieve.primes) {
                if (p > x) break;
                while (x % p == 0) {
                    x /= p;
                    poss.insert(p);
                }
            }
        }

        // if no prime candidates at all, then all go to Bob.
        // k only choice is 2.
        if (poss.size() == 0) {
            int ans = 2 * -*min_element(nums.begin(), nums.end());
            return (ans + M) % M;
        }

        int max_diff = -2e9;
        int k = -1;
        auto arr = nums;

        for (int p : poss) {
            for (int& x : arr) {
                if (x % p != 0) x = -x;
            }

            int res = kadane(arr);
            if (res > max_diff || res == max_diff && p < k) {
                max_diff = res;
                k = p;
            }
            //println("{} {}", p, res);
            for (int& x : arr) x = abs(x);
        }
        return ((long long) k * max_diff + M) % M;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,1,1,1,1};
    cout << sol.divisibleGame(nums) << endl;
}