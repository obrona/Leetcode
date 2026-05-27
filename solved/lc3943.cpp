#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// use sqrt decomposition.
// each sqrt blk has a offset for lazy adding and a hashmap storing the frequency of a value.
// when range adding, if a full sqrt blk is inside, just add to offset, else update individual affected elements.
// since the query is the whole range, just query each block.

// blk size is 256. So max is 5 * 10^4 / 256 = 196, just put 200
// why 256, because it is a power of 2, so taking modulo is very fast
const int POW = 10;
const int BLK_SIZE = (1 << POW);
const int MASK = (1 << POW) - 1;
ll offset[200];
unordered_map<ll, int> stores[200];
vector<ll> nums;

void init(int len, const vector<int>& arr) {
    int l = ((len + BLK_SIZE) >> POW) + 1;
    for (int i = 0; i < l; i++) {
        offset[i] = 0;
        stores[i].clear();
    }
    
    nums = vector<ll>(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); i++) {
        int blk = i >> POW;
        stores[blk][arr[i]]++;
    }
}

// we consider ranges as [x, y) as it is easier to process
// x <= y

// returns [l, r) of the left stub
// if x is align to the start of the blk then this range is empty
pair<int,int> left_stub(int x, int y) {
    if ((x & MASK) == 0) {
        return make_pair(x, x);
    }
    int i = x >> POW;
    return make_pair(x, min(y, (i << POW) + BLK_SIZE));  
}

pair<int,int> right_stub(int x, int y) {
    int i = y >> POW;
    return make_pair(max(x, i << POW), y);
}

// the middle ranges are also [l, r)
pair<int,int> middle_ranges(int x, int y) {
    int l = (x >> POW) + bool(x & MASK);
    int r = y >> POW;
    return make_pair(l, r);
}

void update(int x, int y, int val) {
    auto [l1, r1] = left_stub(x, y);
    for (int i = l1; i < r1; i++) {
        int blk = i >> POW;
        stores[blk][nums[i]]--;
        stores[blk][nums[i] + val]++;
        nums[i] += val;
    }

    auto [l2, r2] = right_stub(x, y);
    if (l2 != l1 || r2 != r1) {
        for (int i = l2; i < r2; i++) {
            stores[i >> POW][nums[i]]--;
            stores[i >> POW][nums[i] + val]++;
            nums[i] += val;
        }
    }

    auto [l3, r3] = middle_ranges(x, y);
    for (int i = l3; i < r3; i++) {
        offset[i] += val;
    }
}

int query(const vector<int>& arr, ll tot, int len) {
    int sum = 0;
    int limit = ((len + BLK_SIZE) >> POW) + 1;
    for (int x : arr) {
        for (int i = 0; i < limit; i++) {
            ll target = tot - x;
            sum += stores[i][target - offset[i]];
        }
    }
    return sum;
}

class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        init(nums2.size(), nums2);
        vector<int> out;
        for (auto& q : queries) {
            if (q[0] == 1) {
                update(q[1], q[2] + 1, q[3]);
            } else {
                int ans = query(nums1, q[1], nums2.size());
                out.push_back(ans);
            }
        }
        return out;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {1,2};
    vector<int> nums2 = {3,4};
    vector<vector<int>> queries = {{2,5},{1,0,0,2},{2,5}};

    vector<int> ans = sol.numberOfPairs(nums1, nums2, queries);
    for (int x : ans) cout << x << " ";
    cout << endl;

}





