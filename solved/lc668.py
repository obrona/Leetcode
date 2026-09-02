
# obviously it is binary search.
# search range is [1, 2, 3 ... mn].
# for each number we need to find how many numbers <= x and whether x is in the matrix.
# move left/right accordingly.
# must be careful about numbers that appear multiple times.
# suppose x is in the matrix and x appears 10 times and cnt_leq = 50
# the valid range is 41, 42, 43 ... 50

class Solution:
    def findKthNumber(self, m: int, n: int, k: int) -> int:
        def inside_matrix(x: int) -> bool:
            return any(x % i == 0 and x // i <= n for i in range(1, m + 1))

        def sum_leq(x: int) -> int:
            return sum(min(x // i, n) for i in range(1, m + 1))

        def sum_eq(x: int) -> int:
            return sum(x % i == 0 and x // i <= n for i in range(1, m + 1))

        s = 1
        e = m * n

        while s < e:
            mid = (s + e) >> 1
            is_inside = inside_matrix(mid)
            cnt = sum_leq(mid)
            cnt_eq = sum_eq(mid)
    
            if is_inside:
                if (cnt - cnt_eq + 1) <= k <= cnt:
                    return mid
                elif k < cnt - cnt_eq + 1:
                    e = mid - 1
                else:
                    s = mid + 1

            else:
                assert(cnt_eq == 0)
                if k <= cnt:
                    e = mid - 1
                else:
                    s = mid + 1


        return s

sol = Solution()
ans = sol.findKthNumber(11, 13, 57)
print(ans)
