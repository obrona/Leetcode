import math

# kind of a 2 pointer solution.
# all single char substring are valid
# suppose start index is 0, we move forward until we see 'abc'
# end is currently at char 'c'
# so add math.comb(end - start, 2)
# then for next iteration, start is at char 'b'


class Solution:
    def countValidSubstrings(self, s: str) -> int:
        cnt = len(s)
        start = 0
        while start < len(s):
            end = start
            while end < len(s) and ((end - start + 1 < 3) or s[end - 2:end + 1] != 'abc'):
                end += 1

          
            cnt += math.comb(end - start, 2)
            
            if end < len(s):
                # there is an 'abc' that is why end is at 'c'
                start = end - 1
            else:
                start = end

            #print(start)

        return cnt

sol = Solution()
s = 'ac'
ans = sol.countValidSubstrings(s)
print(ans)