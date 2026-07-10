

# monotonic stack.

class Solution:
    def dailyTemperatures(self, temperatures: list[int]) -> list[int]:
        stack: list[tuple[int,int]] = []
        out = [0] * len(temperatures)

        for i in range(len(temperatures) - 1, -1, -1):
            while len(stack) > 0 and stack[-1][1] <= temperatures[i]:
                stack.pop()
            if len(stack) > 0:
                out[i] = stack[-1][0] - i
            stack.append((i, temperatures[i]))

        return out

sol = Solution()
temperatures = [73,74,75,71,69,72,76,73]
print(sol.dailyTemperatures(temperatures))
