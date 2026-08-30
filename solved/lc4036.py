# b needs 2^1 'a'.
# c needs 2^2 'a'.
# ...
# z needs 2^25 'a'.
# just greedily try to add z, y, x ... until no more counts.

class Solution:
    def largestString(self, nums: list[int]) -> list[str]:
        out = []
        for x in nums:
            res = []
            for p in range(25, -1, -1):
                while x >= (1 << p):
                    res.append(chr(ord('a') + p))
                    x -= 1 << p
            out.append(''.join(res))
        return out

sol = Solution()
nums = [2,5,7]
print(sol.largestString(nums))