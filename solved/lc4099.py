from sortedcontainers import SortedList

# 1st ensure k >= # of positions whose initial elem is wrong + locked pos with correct elem but is involved in an inversion.
# sorting with adjacent swaps = # of inversion.

def need_unlocking(nums: list[int], locked: list[int]) -> list[bool]:
    store = [False] * len(nums)

    for i, x in enumerate(nums):
        if x != i + 1 and locked[i]:
            store[i] = True

    sl = SortedList[int]()
    for i, x in enumerate(nums):
        if locked[i] and len(sl) - sl.bisect_right(x) > 0:
            store[i] = True
        sl.add(x)

    sl.clear()
    for i, x in reversed(list(enumerate(nums))):
        if locked[i] and sl.bisect_left(x) > 0:
            store[i] = True
        sl.add(x)

    return store

class Solution:
    def minOperations(self, nums: list[int], locked: list[int], k: int) -> int:
        cnt = sum(need_unlocking(nums, locked))
        #print(cnt)
        if cnt > k:
            return -1

        sl = SortedList[int]()
        num_inversions = 0
        for x in nums:
            num_inversions += len(sl) - sl.bisect_right(x)
            sl.add(x)

        #print(num_inversions)

        return cnt + num_inversions

sol = Solution()
nums = [2,3,1]
locked = [1,0,0]
k = 0
ans = sol.minOperations(nums, locked, k)
print(ans)

        


        
