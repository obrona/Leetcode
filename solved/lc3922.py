from  collections import Counter

# just case work I guess.
# intuition is either we chaneg most of the 1s to 0s or 0s to 1s
# we do not mix the 2 changes i.e have flip 1->0 and 0->1
# suppose we have 0..0 1 0 11 0 1 00
# we cannot change the last 1 segment to 0, as then the middle 1 segment '11' have to be 0 now

# case 1: there are 1s at the 2 endpoints pos 0 and n - 1
# then we can change all but the 2 ones at the endpoint to 0
# or change all 0s to 1s

# case 2: at most 1 one at the endpoints
# then either change all but 1 one to 0
# or change all 0 to 1s
# it cannot be that we only change some sections of 0 to 1, as then the new 1s can from 110 or 011 with the
# leftover 0s.

# the final string is either 100...0001
# 0..010..0
# 10...0

class Solution:
    def minFlips(self, s: str) -> int:
        cnter = Counter(s)

        if s[0] == '1' and s[-1] == '1':
            return min(cnter['0'], max(cnter['1'] - 2, 0))
        
        return min(cnter['0'], max(cnter['1'] - 1, 0))
    
print(Solution().minFlips('1010'))
