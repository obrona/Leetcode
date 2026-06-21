import math

# longest length is just 1500 so a O(n^2) solution can pass.
# use some math strings to get 1st digit of a number without converting to string

class Solution:
    def countValidSubarrays(self, nums: list[int], x: int) -> int:
        cnt = 0
        for i in range(len(nums)):
            s = 0
            for j in range(i, len(nums)):
                s += nums[j]
                if s % 10 == x and (s // 10 ** int(math.log10(s))) == x:
                    cnt += 1
        return cnt