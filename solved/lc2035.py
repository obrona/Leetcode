from sortedcontainers import SortedSet

# meet in the middle technique.
# divide into 2 arrays of 15 elems each.
# enumerate each possible split i.e (Ai - Bi, num of elems in Ai)
# if (Ai - Bi, # elems) = (1, 3) the pair from the other split must have # of elems = 12
# time complexity is O(2^15 + 2^15)
# in the 2nd half of matching, each val in the 1st and 2nd half is only 'processed' once.

class Solution:
    def minimumDifference(self, nums: list[int]) -> int:
        half = len(nums) // 2

        def helper(arr: list[int]) -> dict[int, set[int]]:
            out = dict[int, set[int]]()
            N = len(arr)
            _sum = sum(arr)
            for bm in range(1 << N):
                a_cnt = bm.bit_count()
                a_sum = 0

                temp = bm
                while temp:
                    low = temp & -temp
                    idx = low.bit_length() - 1
                    a_sum += arr[idx]
                    temp ^= low

                if a_cnt not in out:
                    out[a_cnt] =  set([2 * a_sum - _sum])
                else:
                    out[a_cnt].add(2 * a_sum - _sum)
            return out


        d1 = helper(nums[:half])
        d2 = helper(nums[half:])
        best = int(1e16)

        for k, s1 in d1.items():
            _k = half - k
            if _k not in d2:
                continue

            l1 = list(s1)
            l2 = list(d2[_k])
            l1.sort()
            l2.sort(reverse=True)
            p2 = 0

            # use 2 pointers
            for x in l1:
                curr = abs(x + l2[p2])
                while p2 < len(l2) - 1 and abs(x + l2[p2 + 1]) <= curr:
                    curr = abs(x + l2[p2 + 1])
                    p2 += 1
                best = min(best, curr)



        return best

sol = Solution()
nums = [2, -1, 0, 4, -2, -9]
ans = sol.minimumDifference(nums)
print(ans)
                
