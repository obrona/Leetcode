# Choose any sub of s.
# Sort sub in non-decreasing order.
# Replace the chosen subsequence in s with the sorted sub, keeping all other characters unchanged.
# this 3 rules means that 1s can only go right and 0s can only go left.
# a misplaced 0 can only be replaced by a 1 to the left.
# ? are wilcards, a 1 can be used to for remaining_10


# we can use a wildcard 0 to replace a left 01, but we may have to rollback if we need this 01 to replace a 10
def check(s: str, tgt: str) -> bool:
    remaining_10 = 0 # can only be fixed by a left remaining_01 or wildcard_1
    remaining_01 = 0 # can only be fixed by a right remaining_10, so we store this first
    wildcard_1 = 0
    wildcard_0 = 0
    rollback = 0     # means a 01 is replaced by a wildcard 0

    for tc, sc in zip(tgt, s):
        if tc == '?':
            if sc == '0':
                if remaining_01 > 0:
                    rollback += 1
                    remaining_01 -= 1
                else:
                    wildcard_0 += 1
            else:
                wildcard_1 += 1

        elif tc == '1' and sc == '0':
            if remaining_01 > 0:
                remaining_01 -= 1
            elif wildcard_1 > 0:
                wildcard_1 -= 1
            elif rollback > 0:
                rollback -= 1
                wildcard_0 += 1
            else:
                remaining_10 += 1

        elif tc == '0' and sc == '1':
            remaining_01 += 1

    return remaining_10 == 0 and remaining_01 == 0

class Solution:
    def transformStr(self, s: str, strs: list[str]) -> list[bool]:
        return [check(s, tgt) for tgt in strs]
    
s = '101'
t = '0?1'

print(check(s, t))