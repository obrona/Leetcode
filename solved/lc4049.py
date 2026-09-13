# for each value, store its positions where the value appears.
# then do the processing.

class Solution:
    def countSpecialIntegers(self, nums: list[int]) -> int:
        store: dict[int, list[int]] = {}
        for i, x in enumerate(nums):
            if x not in store:
                store[x] = []
            store[x].append(i)

        cnt = 0
        for _, positions in store.items():
            if len(positions) < 3:
                continue

            space = positions[1] - positions[0]
            res = True
            for i in range(len(positions) - 1):
                if positions[i + 1] - positions[i] != space:
                    res = False
                    break

            cnt += res

        return cnt

sol = Solution()
nums = [1,8,1,5,1,5,8,5]
ans = sol.countSpecialIntegers(nums)
print(ans)
            
