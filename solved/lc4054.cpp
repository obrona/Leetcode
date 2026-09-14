#include <bits/stdc++.h>
using namespace std;

// use a monotonic stack to find for each index i, the earliest index to the right k
// s.t arr[k] < arr[i].
// problem reduces to in arr[i+1:k-1] (inclusive of both ends) find how many elems > arr[i].
// use a persistent segment tree to answer this query.

vector<int> find_earliest_right_less_index(const vector<int>& arr) {
    vector<int> out(arr.size(), arr.size());
    vector<pair<int,int>> store;

    for (int i = 0; i < arr.size(); i++) {
        int curr = arr[i];
        while (store.size() > 0 && store.back().second > curr) {
            auto [idx, val] = store.back(); 
            store.pop_back();
            out[idx] = i;
        }
        store.emplace_back(i, curr);
    }
    
    return out;
}

struct node {
    int cnt = 1;
    node *left = 0, *right = 0;

    node() {}

    node (int cnt): cnt(cnt) {}
};

int mid(int s, int e) {
    return s + ((e - s) >> 1);
}

template <typename... Args>
node* allocate(vector<node>& pool, Args&&... args) {
    pool.emplace_back(std::forward<Args>(args)...);
    return &pool.back();
}


node* insert(int val, int s, int e, node *curr, vector<node>& pool) {
    if (s == e) {
        return allocate(pool, curr ? curr->cnt + 1 : 1);
    }

    int m = mid(s, e);
    auto new_curr = allocate(pool, (curr) ? curr->cnt + 1 : 1);
    if (val <= m) {
        new_curr->left = insert(val, s, m, (curr) ? curr->left : curr, pool);
        if (curr) new_curr->right = curr->right;
    } else {
        if (curr) new_curr->left = curr->left;
        new_curr->right = insert(val, m + 1, e, (curr) ? curr->right : curr, pool);
    }
    return new_curr;
}

int query(int l, int r, int s, int e, node *later, node *earlier) {
    if (s == l && e == r) {
        int later_cnt = later ? later->cnt : 0;
        int earlier_cnt = earlier ? earlier->cnt : 0;
        return later_cnt - earlier_cnt;
    }

    int m = mid(s, e);
    if (r <= m) {
        return query(l, r, s, m, later ? later->left : later, earlier ? earlier->left : earlier);
    } else if (l > m) {
        return query(l, r, m + 1, e, later ? later->right : later, earlier ? earlier->right : earlier);
    } else {
        return query(l, m, s, m, later ? later->left : later, earlier ? earlier->left : earlier)
            + query(m + 1, r, m + 1, e, later ? later->right : later, earlier ? earlier->right : earlier);
    }
}

pair<int, unordered_map<int,int>> compress(const vector<int>& nums) {
    auto temp = nums;
    sort(temp.begin(), temp.end());
    int p = 0;
    unordered_map<int,int> out;
    for (int i = 0; i < temp.size(); i++) {
        if (i > 0 && temp[i] != temp[i - 1]) p++;
        out[temp[i]] = p;
    }

    return {p + 1, out};
}

class Solution {
public:
    long long shadowPairs(vector<int>& nums) {
        vector<node> pool;
        pool.reserve(20 * nums.size());
        
        vector<node*> roots(nums.size());
        
        vector<int> next_less_idxs = find_earliest_right_less_index(nums);
        
        auto [p, compressed_vals] = compress(nums);
        
        for (int i = nums.size() - 1; i >= 0; i--) {
            node *earlier = (i == nums.size() - 1) ? nullptr : roots[i + 1];
            roots[i] = insert(compressed_vals[nums[i]], 0, p, earlier, pool);
        }
        
        long long cnt = 0;
        for (int i = 0; i < nums.size(); i++) {
            int limit = next_less_idxs[i];
            auto later = (i == nums.size() - 1) ? nullptr : roots[i + 1];
            auto earlier = (limit == nums.size()) ? nullptr : roots[limit];

            int res = query(compressed_vals[nums[i]] + 1, p, 0, p, later, earlier);
            cnt += res;
        }

        return cnt;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {3,1,4,1,5};
    long long ans = sol.shadowPairs(nums);
    cout << ans << endl;
}