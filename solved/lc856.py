
# just another parsing question.

def match_braces(s: str) -> dict[int,int]:
    out = {}
    stack = []
    for i, c in enumerate(s):
        if c == '(':
            stack.append(i)
        else:
            out[stack.pop()] = i
    return out



def parse(s: str, l: int, r: int, braces: dict[int,int]) -> int:
    score = 0
    
    i = l
    while i <= r:
        c = s[i]
        if c == ')':
            i += 1
        elif c == '(':
            end = braces[i]
            if end == i + 1:
                score += 1
            else:
                score += 2 * parse(s, i + 1, end - 1, braces)
            i = end + 1
            
    return score

class Solution:
    def scoreOfParentheses(self, s: str) -> int:
        braces = match_braces(s)
        res = parse(s, 0, len(s) - 1, braces)
        return res

sol = Solution()
s = '(())()'
print(sol.scoreOfParentheses(s))
                
                