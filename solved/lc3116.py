import math
# binary search. the kth number must have exactly k - 1 valid numbers lesser than it.
# however we must use principle of inclusion and exclusion.
# the number we check must be some multiple of c in coins.
# the pie value is the lcm(a, b, c, ... x) and not a * b * c ... x.

def generate_all_nonempty_subsets(coins: list[int]) -> list[tuple[int,int]]:
    out = []
    for bm in range(1, 1 << len(coins)):
        bc = bm.bit_count()
        m = 1
        for i in range(len(coins)):
            if (bm >> i) & 1:
                m = math.lcm(m, coins[i])
        out.append((bc, m))
    return out

def get_count_leq(subsets: list[tuple[int,int]], m: int) -> int:
    s = 0
    for bc, subset in subsets:
        sign = 1 if bc % 2 == 1 else -1
        s += sign * (m // subset)
    return s


class Solution:
    def findKthSmallest(self, coins: list[int], k: int) -> int:
        store = generate_all_nonempty_subsets(coins)
        #print(store)
        #print(get_count_leq(store, 18))

        s = 1
        e = k * min(coins)
        while s < e:
            m = (s + e) // 2
            leq = get_count_leq(store, m)
            valid = any(m % c == 0 for c in coins)
            #print(s, e, m, leq, valid)

            if valid:
                if leq == k:
                    return m
                elif leq < k:
                    s = m + 1
                else:
                    e = m
            else:
                if leq < k:
                    s = m + 1
                else:
                    e = m

        #print(s)
        #s = min(s + (i - (s % i) if s % i != 0 else 0) for i in coins)
        
        return s

sol = Solution()
coins = [6,3]
k = 8

print(sol.findKthSmallest(coins, k))