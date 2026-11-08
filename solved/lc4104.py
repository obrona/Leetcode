from sortedcontainers import SortedList

# 2 pointer solution.
# suppose [s, e) does not have 'abc' as a subsequence. 
# then any subarray in [s, e) also does not have 'abc' as a subsequence.

class Solution:
    def countValidSubstrings(self, s: str) -> int:
        cnt = 0
        a_list = SortedList[int]()
        b_list = SortedList[int]()
        c_list = SortedList[int]()
        ptr = 0

        def has_abc_subsequence() -> bool:
            if len(a_list) == 0 or len(b_list) == 0 or len(c_list) == 0:
                return False
            a_idx = a_list[0]
            
            b_idx = b_list.bisect_right(a_idx)
            if b_idx >= len(b_list):
                return False
            b_idx = b_list[b_idx]

            c_idx = c_list.bisect_right(b_idx)
            if c_idx >= len(c_list):
                return False

            return True

        
        for i in range(len(s)):
            while ptr < len(s):
                c = s[ptr]
                if c == 'a':
                    a_list.add(ptr)
                elif c == 'b':
                    b_list.add(ptr)
                else:
                    c_list.add(ptr)

                if has_abc_subsequence():
                    if c == 'a':
                        a_list.pop()
                    elif c == 'b':
                        b_list.pop()
                    else:
                        c_list.pop()
                    break

                ptr += 1

            cnt += ptr - i

            c = s[i]
            if c == 'a':
                a_list.pop(0)
            elif c == 'b':
                b_list.pop(0)
            else:
                c_list.pop(0)

        return cnt


sol = Solution()
s = 'abac'
ans = sol.countValidSubstrings(s)
print(ans)