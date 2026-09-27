
# as long as sum(arr1) = sum(arr2), it is possible.
# use proof by induction on length n.
# intuition is that the operation never changes the initial sum of arr[i] + arr[j].

class Solution:
    def canTransform(self, source: list[int], target: list[int]) -> bool:
        return sum(source) == sum(target)