#include <vector>
#include <numeric>
#include <unordered_set>
#include <optional>
#include <iostream>
using namespace std;

// compute prefix and suffix gcd.
// the number of times prefix gcd can decrease is log(max value).
// because when gcd decreases, a prime factor of >= 2 is knocked off.
// thus we only need to consider indexes where the prefix/suffix gcd changes.
// at most 2log(max_val) indices, we can just recompute everything and check again in O(n).

// consider the unmodified array.
// ans is sum(prefix[i] == suffix[i + 1] for i in [0, len - 1]).
// suppose i is not a changning index.
// means prefix[i - 1] = prefix[i] and suffix[i] = suffix[i + 1].
// we removed index i.
// then only pair we remove is (prefix[i], suffix[i + 1]).
// and now we have (prefix[i - 1], sufix[i + 1])
// which is the same is (prefix[i - 1], suffix[i]).
// and the num of split indices is no better from the result of the unmodifed array.
// because instead of ... (p[i - 1], s[i]), (p[i], s[i + 1]) ...
// we have ... (p[i - 1], s[i + 1]) ...
// remember p[i - 1] = p[i + 1] and s[i] = s[i + 1].
// basically we just lost 1 pair.
// the left and right side are not affected.

int count_split_pos(const vector<int>& prefix_gcd, const vector<int>& suffix_gcd) {
    int cnt = 0;
    for (int i = 0; i < prefix_gcd.size() - 1; i++) {
        cnt += prefix_gcd[i] == suffix_gcd[i +1];
    }
    return cnt;
}

vector<int> get_prefix_gcd(const vector<int>& arr, optional<unordered_set<int>*> store = nullopt) {
    vector<int> out(arr.size(), arr[0]);
    for (int i = 1; i < arr.size(); i++) {
        out[i] = gcd(out[i - 1], arr[i]); 
        
        if (store && out[i] != out[i - 1]) {
            store.value()->insert(i);
        }
    }
    return out;
}

vector<int> get_suffix_gcd(const vector<int>& arr, optional<unordered_set<int>*> store = nullopt) {
    vector<int> out(arr.size(), arr.back());
    for (int i = arr.size() - 2; i > -1; i--) {
        out[i] = gcd(out[i + 1], arr[i]);

        if (store && out[i] != out[i + 1]) {
            store.value()->insert(i);
        }
    }
    return out;
}

class Solution {
public:
    int maxValidSplits(vector<int>& nums) {
        unordered_set<int> indices;
        auto p = get_prefix_gcd(nums, make_optional(&indices));
        auto s = get_suffix_gcd(nums, make_optional(&indices));

        int best = count_split_pos(p, s);
        
        for (int i : indices) {
            vector<int> temp;
            temp.insert(temp.end(), nums.begin(), nums.begin() + i);
            temp.insert(temp.end(), nums.begin() + i + 1, nums.end());

            auto p = get_prefix_gcd(temp);
            auto s = get_suffix_gcd(temp);
            int res = count_split_pos(p, s);
            
            best = max(best, res);
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2,10,14};
    int ans = sol.maxValidSplits(nums);
    cout << ans << endl;
}