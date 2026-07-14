from collections.abc import Iterable

# just get prefix suffix of 0s and 1s count.

def get_prefix_count[T](arr: Iterable[T], item: T) -> list[int]:
    out: list[int] = []
    cnt: int = 0
    for x in arr:
        cnt += x == item
        out.append(cnt)
    return out



class Solution:
    def minFlipsMonoIncr(self, s: str) -> int:
        suffix_0 = get_prefix_count(s[::-1], '0')[::-1]
        prefix_1 = get_prefix_count(s, '1')

        best = 999999999
        for i in range(len(s) + 1):
            left_cnt = prefix_1[i - 1] if i > 0 else 0
            right_cnt = suffix_0[i] if i < len(s) else 0
            best = min(best, left_cnt + right_cnt)
        return best
    
sol = Solution()
s = '00110'
print(sol.minFlipsMonoIncr(s))

#print(get_prefix_count([0, 0, 1, 1, 0]))