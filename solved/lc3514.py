
# largest number is 1500 so the max number we can create is 2048.
# we consider all the pairs, at most 2048 numbers.
# then we just brute force again with all numbers in nums.
class Solution:
    def uniqueXorTriplets(self, nums: list[int]) -> int:
        pairs = set[int]()
        for i in range(len(nums)):
            for j in range(i, len(nums)):
                pairs.add(nums[i] ^ nums[j])

        pairs2 = set[int]()
        for x in pairs:
            for y in nums:
                pairs2.add(x ^ y)

        return len(pairs2)
    
sol = Solution()
nums = [6,7,8,9]
print(sol.uniqueXorTriplets(nums))