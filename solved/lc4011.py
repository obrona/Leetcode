# brute force can work.

class Solution:
    def countRatioSubarrays(self, nums: list[int], a: int, b: int) -> int:
        cnt = 0
        for i in range(len(nums)):
            even, odd = 0, 0
            for j in range(i, len(nums)):
                if nums[j] % 2 == 0:
                    even += 1
                else:
                    odd += 1

                if odd > 0 and even / odd <= a / b:
                    cnt += 1
        return cnt