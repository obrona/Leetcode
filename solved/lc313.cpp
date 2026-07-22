#include <queue>
#include <vector>
#include <climits>
#include <iostream>
#include <unordered_set>
using namespace std;
using ll = long long;

// n <= 10^5, so we do manual simulation with a min-heap.
// state is {val, i} where i is the largest prime index used in val's factorization.
// {val, i} can transition to {val * primes[i], i}, {val * primes[i + 1], i + 1} ... {val * primes[len - 1], len - 1}.
// somehow this optimisation goes from TLE to Accepted.

// but the correct solution is mergina k lists (here k can increase)
// let the lists be
// 1: [2, 3, 7, 19]
// 2: 2 * [2, 3, 7, 19]
// 4: 4 * [2, 3, 7, 19]
// each ugly number is some previous ugly number * one of the primes in array.
// so state is {val, what ugly number list, next idx}
// when we pop state S, add the next element of the respective ugly number list.
// eg {8, 4, 1} so we add {12, 4, 2}
// then the time complexity is Nlog(# of prime numbers).

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        auto cmp = [] (const pair<ll, int>& p1, const pair<ll, int>& p2) {
            return p1.first > p2.first || (p1.first == p2.first && p1.second > p2.second);
        };
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, decltype(cmp)> pq(cmp);
        unordered_set<int> seen;
        int temp = n;

        pq.emplace(1, 0);
        while (n > 0) {
            auto [v, i] = pq.top(); pq.pop();
            if (!seen.contains(v)) temp--;
            if (temp == 0) return v;

            for (int j = i; j < primes.size(); j++) {
                ll next = v * primes[j];
                if (next >= INT_MAX) break;
                pq.emplace(next, j);
            }
            
        }
        return -1;
    }
};

int main() {
    Solution sol;
    int n = 12;
    vector<int> primes = {2,7,13,19};
    int ans = sol.nthSuperUglyNumber(n, primes);
    cout << ans << endl;
}
