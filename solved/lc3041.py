from functools import cache

# dynamic programming.
# but we still can skip elements even when the array is sorted

class Solution:
    def maxSelectedElements(self, nums: list[int]) -> int:
        nums.sort()

        right_greater = [len(nums)] * len(nums)
        stack = []
        for i, x in enumerate(nums):
            while len(stack) > 0 and x > stack[-1][1]:
                p, y = stack.pop()
                right_greater[p] = i
            stack.append((i, x))


        @cache
        def dp(i: int, incr: bool) -> int:
            if i == len(nums):
                return 0
            elif i == len(nums) - 1:
                return 1

            now = nums[i] + incr
            best = 1
            if nums[i + 1] == now + 1:
                best = max(best, 1 + dp(i + 1, 0))
            elif nums[i + 1] == now:
                best = max(best, 1 + dp(i + 1, 1))

            next = right_greater[i]
            if next < len(nums) and next > i + 1:
                if nums[next] == now + 1:
                    best = max(best, 1 + dp(next, 0))
                elif nums[next] == now:
                    best = max(best, 1 + dp(next, 1))

            return best


        return max(max(dp(i, 0), dp(i, 1)) for i in range(len(nums)))

