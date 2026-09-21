import itertools

# lexicographically largest means greedy.
# we start at index 0 which means we are processing bit 14th
# split the nums into 2 groups, those with bit 14 set and not set.
# then we recurse on these 2 groups.
# the idea is that for the 1st group they have all 1s at idx, so the order 
# within that group does not matter, therefore the same logic to maximise the 
# length of prefix 1s is the same.

def helper(bit_string: list[str], idx: int, store: list[int], reaches_end: list[bool]):
    if len(bit_string) == 0 or idx == 15:
        return

    can_continue = reaches_end[idx]
    case1: list[str] = []
    case2: list[str] = []
    for x in bit_string:
        if can_continue and x[idx] == '1':
            case1.append(x)
        else:
            case2.append(x)

    store[idx] += len(case1) if can_continue else 0
    reaches_end[idx] = can_continue[idx] and len(case2) == 0

    helper(case1, idx + 1, store, reaches_end)
    helper(case2, idx + 1, store, reaches_end)

   



class Solution:
    def largestPower(self, nums: list[int]) -> list[int]:
        lst = [f'{n:015b}' for n in nums]
        store = [0] * 15
        reaches_end = [True] * 15
        helper(lst, 0, store, reaches_end)
        return store

sol = Solution()
nums = [6,5,13]
ans = sol.largestPower(nums)
print(ans)

    

    


