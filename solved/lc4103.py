

# for ach group you need to remove groupSize[t] elems and this cannot change.
# think about stack.
# when encountering new elems, see if can merge with previous elems. When can remove, just remove. 

class Solution:
    def canRemoveAll(self, types: list[int], colors: list[int], groupSize: list[int]) -> bool:
        stack: list[list[int]] = []
        for t, c in zip(types, colors):
            if len(stack) > 0 and stack[-1][0] == t and stack[-1][1] == c:
                l = stack[-1]
                l[2] += 1
                l[2] %= groupSize[t]
                if l[2] == 0:
                    stack.pop()

            else:
                if groupSize[t] != 1:
                    stack.append([t, c, 1])

        return len(stack) == 0

sol = Solution()
types = [0,1,1,0]
colors = [5,3,3,5]
groupSize = [2,2]

ans = sol.canRemoveAll(types, colors, groupSize)
print(ans)
