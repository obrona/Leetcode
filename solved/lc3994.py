# replace all elems in arr with 0, 1, 2 
# 0 if is in the left array, 1 if in the mid array and 2 if in the right array.
# we need to sort the array using adjacent swaps.

# an inversion is when i < j but arr[i] > arr[j]
# need to reduce inversion count to 0.
# each swap reduces the # of inversions by 1. 
# so # of swaps needed is >= # of inversions.

# can prove that # of swaps = # of inversions.

class Solution:
    def minAdjacentSwaps(self, nums: list[int], a: int, b: int) -> int:
        cnts = [0] * 3
        out = 0

        for x in nums:
            s = 0 if x < a else 1 if a <= x <= b else 2
            out += sum(cnts[s + 1:])
            cnts[s] += 1

        return out % int(1e9 + 7)
    
sol = Solution()
nums = [1,3,2,4,5,6]
a = 3
b = 4
print(sol.minAdjacentSwaps(nums, a, b))
#print([1,2,3][5:])