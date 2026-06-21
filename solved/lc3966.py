import functools

# digit dp.

@functools.cache
def dp(digits_left: int, is_first: bool, prev_digit: int, k: int) -> int:
    if digits_left == 0:
        return 1
    
    if is_first:
        return sum(dp(digits_left - 1, False, i, k) for i in range(1, 10))
    else:
        return sum(dp(digits_left - 1, False, i, k) for i in range(10) if abs(i - prev_digit) <= k)
    
def helper(num: str, i: int, k: int) -> int:
    if i == len(num):
        return 1
    
    curr_d = int(num[i])
    ans = 0
    if i == 0:
        ans += sum(dp(num_digit, True, -1, k) for num_digit in range(1, len(num)))
        ans += sum(dp(len(num) - 1, False, d, k) for d in range(1, curr_d))
        ans += helper(num, i + 1, k)

    else:
        prev_d = int(num[i - 1])
        ans += sum(dp(len(num) - i - 1, False, d, k) for d in range(curr_d) if abs(d - prev_d) <= k)
        
        if abs(curr_d - prev_d) <= k:
            ans += helper(num, i + 1, k)
    
    return ans


class Solution:
    def goodIntegers(self, l: int, r: int, k: int) -> int:
        return helper(str(r), 0, k) - (0 if l == 1 else helper(str(l - 1), 0, k))
    
print(helper('100',  0, 1))