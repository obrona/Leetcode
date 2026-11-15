class Solution:
    def countConsistent(self, nums: list[int]) -> int:
        cnt = 0
        for i in range(len(nums)):
            for j in range(i, len(nums)):
                m = nums[i]
                a = nums[i]
                for k in range(i + 1, j + 1):
                    m = min(m, nums[k])
                    a = a & nums[k]
                cnt += m == a
        return cnt