
# we try out all left rotations and pick the best 1.
# suppose the optimal solution has interleaved increment and left rotate,
# we can transform it into an sequence of operation where the left rotate are all done first.
# once we fixed a rotation, num of ops to make it a palindrome using operation 1.
# is simply min(make left char == right char, make right char == left char).

class Solution:
    def minOperations(self, s: str) -> int:
        def helper(start_idx: int) -> int:
            ans = 0
            for i in range(len(s) // 2):
                actual_left_idx = (start_idx + i) % len(s)
                actual_right_idx = (start_idx + len(s) - 1 - i) % len(s)

                ord_left = ord(s[actual_left_idx]) - ord('a')
                ord_right = ord(s[actual_right_idx]) - ord('a')

                best = min((ord_left - ord_right + 26) % 26, (ord_right - ord_left + 26) % 26)
                ans += best 
            return ans
        return min(i + helper(i) for i in range(len(s)))

sol = Solution()
s = 'abc'
ans = sol.minOperations(s)
print(ans)