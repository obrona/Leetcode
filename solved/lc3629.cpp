#include <bits/stdc++.h>
using namespace std;

// not that complicated.
// don't immediately think dp, it is just bfs.
// for nums[i] if not prime only go to neighbour nums[i - 1] or nums[i + 1]
// for prime nums[i], check nums[i] * 2, nums[i] * 3...

struct Sieve {
    vector<bool> store;

    Sieve(int n): store(n + 1, true) {
        store[0] = store[1] = false;
        for (int i = 2; i <= n; i++) {
            if (!store[i]) continue;
            for (long long j = (long long) i * i; j <= n; j += i) store[j] = false;
        }
    }

    bool is_prime(int n) const {
        return store[n];
    }
};

class Solution {
public:
    inline const static Sieve sieve{1000000};

    int minJumps(vector<int>& nums) {
        // we only procss primes 1 time only.
        // suppose nums[i] = nums[j] = prime number and we visit nums[i] 1st.
        // when we reach nums[j] no need to check for all nums[k] s.t nums[k] % nums[i] = 0.
        // the distance will always be larger then if we go from nums[i] to nums[k].
        unordered_set<int> visited_primes;
        vector<bool> visited(nums.size(), false);
        vector<int> ds(nums.size(), -1);
        int largest = *max_element(nums.begin(), nums.end());
        
        unordered_map<int, vector<int>> store;
        for (int i = 0; i < nums.size(); i++) {
            store[nums[i]].push_back(i);
        }
        
        int wave = 0;
        deque<int> q;
        
        visited[0] = 1;
        q.push_back(0);

        while (!q.empty()) {
            for (int len = q.size(); len > 0; len--) {
                int i = q.front(); q.pop_front();
                
                ds[i] = wave;

                if (i == nums.size() - 1) return wave;

                if (i > 0 && !visited[i - 1]) {
                    visited[i - 1] = 1;
                    q.push_back(i - 1);
                }

                if (i < nums.size() - 1 && !visited[i + 1]) {
                    visited[i + 1] = true;
                    q.push_back(i + 1);
                }

                if (sieve.is_prime(nums[i]) && !visited_primes.contains(nums[i])) {
                    visited_primes.insert(nums[i]);
                    for (int j = nums[i]; j <= largest; j += nums[i]) {
                        if (!store.contains(j)) continue;
                        for (int next : store[j]) {
                            if (visited[next]) continue;
                            visited[next] = true;
                            q.push_back(next);
                        }
                    }
                }
            }
            wave++;
        }
        assert(false);
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {975,1997,1764,2813,1072,3731,2327,175,221,102,1979,2618,2523,1997,571,3136,3693,1026,2697,3544,1637,3485,1083,1244,2190,2521,247,101,570,3493,3248,3989,175,1833,1786,1079,3451,498,2775,2823,1690,1879,4050,2228,25,1157,1503,2210,1150,3749,2479,3226,2514,1000,758,3279,158,2452,4054,2134,2171,2045,3093,1962,545};
    int ans = sol.minJumps(nums);
    println("{}", ans);
}