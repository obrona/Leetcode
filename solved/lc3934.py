from collections import Counter


# suffix array is WRONG
# have to use rolling hash and binary search.
# if can find length of n that is unique, no need to seach n + 1, n + 2.
# if cannot find length of n that is unique, this means all length < n substring is not unique eiher.
# any length (n - k) substring is part of a length n substring which is can be found again later 
# so we can find the length (n - k) substring.



class RollingHash:
    def __init__(self, arr: list[int]):
        self.store = [0] * len(arr)
        self.p = 100003
        self.m = int(1e9 + 7)
        self.inv_p = pow(self.p, -1, self.m)

        for i in range(len(arr)):
            if i == 0:
                self.store[i] = arr[0]
                continue
            self.store[i] = (self.store[i - 1] + arr[i] * pow(self.p, i, self.m)) % self.m


    def get_hash(self, l: int, r: int):
        if l == 0:
            return self.store[r]
        
        tmp = (self.store[r] - self.store[l - 1]) % self.m
        tmp *= pow(self.inv_p, l, self.m)
        tmp %= self.m

        return tmp

class Solution:
    def smallestUniqueSubarray(self, nums: list[int]) -> int:
        s = 1
        e = len(nums)
        rolling_hash = RollingHash(nums)
        cnter = Counter[int]()
        
        while s < e:
            cnter.clear()
            m = (s + e) // 2
            for i in range(0, len(nums) - m + 1):
                hash = rolling_hash.get_hash(i, i + m - 1)
                cnter[hash] += 1

            ans = any(v == 1 for v in cnter.values())
            if ans:
                e = m
            else:
                s = m + 1

        return s
    
sol = Solution()
nums = [1,1,2,2,1]
print(sol.smallestUniqueSubarray(nums))

