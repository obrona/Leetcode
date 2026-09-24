from sortedcontainers import SortedDict
# greedy problem.
# start with the smallest value, assign 1 candy
# move to next smallest value.
# check the neighbors value, if the value is already assigned then set the value to +1
# if not then set to 1.

class Solution:
    def candy(self, ratings: list[int]) -> int:
        store: SortedDict[int, list[int]] = SortedDict()

        for i, x in enumerate(ratings):
            store.setdefault(x, []).append(i)

        out = [0] * len(ratings)
        for _, lst in store.items():
            for idx in lst:
                left = 0 if idx == 0 or ratings[idx - 1] == ratings[idx] else out[idx - 1]
                right = 0 if idx == len(ratings) - 1 or ratings[idx + 1] == ratings[idx] else out[idx + 1]
                out[idx] = max(left, right) + 1

        return sum(out)

sol = Solution()

ratings = [1,2,2]

ans = sol.candy(ratings)
print(ans)