from functools import reduce

# consider all elements that are out of order.
# if a & b = c & d = k, then a & b & c & d = k
# this can be extended for all the swap pairs so we have a & b & c & d ... = k
# all out of order elems will appear in the expression.
# a & a = a, so we can rearrange and then remove elems that appear > 1.
# introducing an element that is already in the rught position only decreases k.

# suppose k != any of the elems in a, b, c, d ...
# it is okay this means we have to use an elem in the right position.

class Solution:
    def sortPermutation(self, nums: list[int]) -> int:
        is_sorted = all(x <= y for x, y in zip(nums, nums[1:]))
        if is_sorted:
            return 0
        return reduce(lambda a, x: a & x, (x for i, x in enumerate(nums) if x != i))