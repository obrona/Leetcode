#include <bits/stdc++.h>
using namespace std;

/*
 * Approach: pick the peak, then two memoised DPs (one per side)
 * ================================================================
 *
 * When is it impossible?
 * ----------------------
 * A mountain needs a peak with at least one element on each side, so n >= 3.
 * There is no upper limit on values, so for n >= 3 we can always build a
 * mountain (for example by raising the middle elements high enough). The only
 * -1 case is n < 3.
 *
 * Splitting the problem at the peak
 * ---------------------------------
 * Fix the peak index i (1 <= i <= n-2) and its final value v. Then:
 *   - nums[0..i-1] must become strictly increasing with every value <= v-1,
 *   - nums[i+1..n-1] must become strictly decreasing with every value <= v-1,
 *   - every value must stay >= 1.
 * The two sides do not affect each other once v is fixed, so
 *
 *   cost(i, v) = |nums[i] - v| + left_dp(i-1, v-1) + right_dp(i+1, v-1)
 *
 * and the answer is the minimum of cost(i, v) over all peaks i and values v.
 *
 * left_dp(i, ceiling)
 * -------------------
 * The minimum number of operations to make nums[0..i] strictly increasing,
 * with nums[i] <= ceiling and every element >= 1.
 *
 * Base cases:
 *   - i < 0          -> 0        (nothing left to fix)
 *   - ceiling < 1    -> INVALID  (element i would have to be below 1)
 *
 * Transition. Element i either equals the ceiling or sits strictly below it:
 *   - match:    set nums[i] = ceiling, which costs |nums[i] - ceiling|. The
 *               element before it must then be <= ceiling-1:
 *                 |nums[i] - ceiling| + left_dp(i-1, ceiling-1)
 *   - no_match: nums[i] ends up < ceiling, which is the same as solving with
 *               a ceiling one lower:
 *                 left_dp(i, ceiling-1)
 *   left_dp(i, ceiling) = min(match, no_match)
 *
 * "no_match" turns "value <= ceiling" into "value == ceiling for some
 * ceiling", so each state does O(1) work and we never loop over all
 * candidate values for nums[i].
 *
 * Strictness comes from the "ceiling - 1" passed to the previous index. The
 * ">= 1" rule comes from the ceiling < 1 base case. It also makes short
 * ceilings infeasible on its own: index i needs a value of at least i+1, and a
 * smaller ceiling runs out before i drops below 0.
 *
 * right_dp(i, ceiling)
 * --------------------
 * This is the mirror image for the suffix nums[i..n-1]: make it strictly
 * decreasing with nums[i] <= ceiling and every element >= 1. It walks i+1
 * instead of i-1, and the base case is i >= n.
 *
 * Bounding the values
 * -------------------
 * We only try values up to hi = max(nums) + n. An optimal solution never needs
 * a value above that: the "staircase" max(nums)+1, +2, ... already rises above
 * every original element within n steps, and climbing any higher only adds
 * cost. The ceiling dimension of each memo table therefore has size hi+1.
 *
 * Main loop
 * ---------
 * For each peak index i in [1, n-2] and peak value v in [2, hi], compute
 * cost(i, v) with the two DPs and keep the minimum. v starts at 2 because both
 * neighbours must be >= 1 and strictly smaller than the peak.
 *
 * Complexity
 * ----------
 * Let H = max(nums) + n (at most about 2000).
 *   - Each DP has n * H states with O(1) work each: O(n * H).
 *   - The main loop makes n * H calls, and each one is a memo hit after its
 *     first evaluation: O(n * H).
 *   Time:  O(n * (max(nums) + n)), about 2e6 states per table.
 *   Space: O(n * (max(nums) + n)) for the two memo tables. The recursion
 *          depth is at most about n + H, which is fine for the stack.
 */

class Solution {
public:
    int INVALID = 1000000000;
    vector<int> nums;
    vector<vector<optional<int>>> left_store;
    vector<vector<optional<int>>> right_store;

    int left_dp(int i, int ceiling) {
        if (i < 0) return 0;
        if (ceiling < 1) return INVALID;

        auto& ans = left_store[i][ceiling];
        if (ans) return ans.value();

        int match = abs(nums[i] - ceiling) + left_dp(i - 1, ceiling - 1);
        int no_match = left_dp(i, ceiling - 1);

        ans = min(match, no_match);
        return ans.value();
    }

    int right_dp(int i, int ceiling) {
        if (i >= nums.size()) return 0;
        if (ceiling < 1) return INVALID;

        auto& ans = right_store[i][ceiling];
        if (ans) return ans.value();

        int match = abs(nums[i] - ceiling) + right_dp(i + 1, ceiling - 1);
        int no_match = right_dp(i, ceiling - 1);

        ans = min(match, no_match);
        return ans.value();
    }

    int minOperations(vector<int>& nums) {
        if (nums.size() < 3) return -1;

        this->nums = nums;
        int hi = *max_element(nums.begin(), nums.end()) + nums.size();
        left_store = right_store = vector(nums.size(), vector<optional<int>>(hi + 1, nullopt));

        int best = INVALID;
        for (int i = 1; i < nums.size() - 1; i++) {
            for (int v = 2; v <= hi; v++) {
                int res = abs(nums[i] - v) + left_dp(i - 1, v - 1) + right_dp(i + 1, v - 1);
                best = min(best, res);
            }
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {9,4,9};
    int ans = sol.minOperations(nums);
    println("{}", ans);
}