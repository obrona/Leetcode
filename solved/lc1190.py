

# nice problem.
# just use a stack.
# time complexity is O(n^2) because each element is pop and put back at most O(n) times.

class Solution:
    def reverseParentheses(self, s: str) -> str:
        stack = list[str]()

        for c in s:
            if c == ')':
                temp = list[str]()
                while True:
                    prev = stack.pop()
                    if prev == '(':
                        break
                    else:
                        temp.append(prev)
                stack.extend(temp)

            else:
                stack.append(c)

        return ''.join(stack)


sol = Solution()

s = "(ed(et(oc))el)"
print(sol.reverseParentheses(s))

            