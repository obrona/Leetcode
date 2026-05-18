import math

class Solution:
    def countKthRoots(self, l: int, r: int, k: int) -> int:
        if k == 1:
            return r - l + 1
        
        s = math.ceil(round(pow(l, 1 / k), 6))
        e = math.floor(round(pow(r, 1 / k), 6))
        return e - s + 1

print(pow(64, 1 / 3))
sol = Solution()
print(sol.countKthRoots(30, 64, 3))
