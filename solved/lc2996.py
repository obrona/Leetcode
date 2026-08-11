import itertools

def first_missing_int(start: int, store: set[int]) -> int:
    return next(x for x in itertools.count(start) if x not in store)

class Solution:
    def missingInteger(self, nums: list[int]) -> int:
        l = 1
        for i in range(l, len(nums)):
            if nums[l] == nums[l - 1] + 1:
                l += 1

        return first_missing_int(sum(nums[:l]), set(nums))