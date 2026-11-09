
# if index i is valid then
# nums[0:i] == target[0:i] and target[i:] is sorted in decreasing order and
# nums[i:] and target[i:] have the same multiset.

class Store:
    def __init__(self):
        self.not_equal_cnt = 0
        self.store: dict[int, int] = {}

    def add_target_elem(self, x: int):
        c = self.store.get(x, 0)
        self.store[x] = c - 1
        
        if c == 0:
            self.not_equal_cnt += 1
        elif c == 1:
            self.not_equal_cnt -= 1

    def add_nums_elem(self, x: int):
        c = self.store.get(x, 0)
        self.store[x] = c + 1

        if c == -1:
            self.not_equal_cnt -= 1
        elif c == 0:
            self.not_equal_cnt += 1

    def is_multisets_same(self) -> bool:
        return self.not_equal_cnt == 0

 

class Solution:
    def countSuffix(self, nums: list[int], target: list[int]) -> int:
        N = len(nums)
        prefix_equal = [True] * N
        suffix_desc = [True] * N
        store = Store()
        suffix_multiset_same = [True] * N

        for i, (x, y) in enumerate(zip(nums, target)):
            if i == 0:
                prefix_equal[i] = x == y
            else:
                prefix_equal[i] = prefix_equal[i - 1] and (x == y)

        for i, x, y in zip(range(N - 2, -1, -1), target[-2::-1], target[-1::-1]):
            suffix_desc[i] = suffix_desc[i + 1] and x >= y

        for i, x, y in zip(range(N - 1, -1, -1), nums[::-1], target[::-1]):
            store.add_nums_elem(x)
            store.add_target_elem(y)
            suffix_multiset_same[i] = store.is_multisets_same()

        return (int(suffix_desc[0] and suffix_multiset_same[0]) 
                + sum(x and y and z for x, y, z in zip(prefix_equal, suffix_desc[1:], suffix_multiset_same[1:])))

sol = Solution()
nums = [1,2,3]
target = [3,2,1]
ans = sol.countSuffix(nums, target)
print(ans)
