
# track the len of the string after each operation.
# then work backwords.

def get_len_at_each_op(s: str) -> list[int]:
    l = 0
    out = []
    for c in s:
        if c.isalpha() and c.islower():
            l += 1
        elif c == '*':
            l = max(0, l - 1)
        elif c == '#':
            l *= 2
        out.append(l)
    return out

class Solution:
    def processStr(self, s: str, k: int) -> str:
        ls = get_len_at_each_op(s)
        
        if k >= ls[-1]:
            return '.'

        # as long k is valid in the final string, 
        # k must always correspond to some character as we work backwards.
        for c, l in zip(s[::-1], ls[::-1]):
            #print(c, l, k)
            if c.isalpha() and c.islower():
                if k == l - 1:
                    return c
                
            elif c == '*':
                continue

            elif c == '#':
                k = k - l // 2 if k >= l // 2 else k

            elif c == '%':
                k = l - 1 - k

        raise Exception('should not reach here')
    
sol = Solution()
s = "%#*gm#xib"
k = 2
print(sol.processStr(s, k))
            
