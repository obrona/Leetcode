import math

# basically just find the ranges not covered by any light.
# a range [l, r] needs ceil((r - l + 1) / 3) to cover.



def get_unlighted_ranges(lights: list[int]) -> list[tuple[int,int]]:
    stack = []
    end = -1

    for i, l in enumerate(lights):
        if l == 0:
            if i > end:
                stack.append(i)
        else:
            while len(stack) > 0 and stack[-1] >= i - l:
                stack.pop()
            end = max(end, i + l)

    covered = [True] * len(lights)
    for x in stack:
        covered[x] = False

    out = []
    i = 0
    while i < len(covered):
        if covered[i]:
            i += 1
            continue
        else:
            start = i
            while i < len(covered) and not covered[i]:
                i += 1
            out.append([start, i - 1])
    
    return out



class Solution:
    def minLights(self, lights: list[int]) -> int:
        it = get_unlighted_ranges(lights)
        #print(it)
        it = map(lambda x: math.ceil((x[1] - x[0] + 1) / 3), it)
        ans = sum(it)
        return ans


sol = Solution()
lights = [0,0,1,0,1,4]
ans = sol.minLights(lights)
print(ans)