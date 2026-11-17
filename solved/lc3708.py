class Solution:
    def longestSubarray(self, nums: list[int]) -> int:
        p = 0
        best = min(2, len(nums))
        while p < len(nums):
            s = p
            while s < len(nums):
                if s - p + 1 <= 2 or nums[s - 2] + nums[s - 1] == nums[s]:
                    s += 1
                else:
                    break
            best = max(best, s - p)

            # when we stop at s, it is not enough to assign p = s
            # but rather p = s - 1, as s - 1, s, s + 1 ... can form
            # another fibonacci sequence.
            p = max(p + 1, s - 1)
        return best

sol = Solution()
nums = [1,1,1,2]
print(sol.longestSubarray(nums))


                