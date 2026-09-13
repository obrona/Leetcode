from collections import deque

# we precomupte all palindromes.
# a palidrome is uniquely determined by its 1st half.
# since 1 <= nums[i] <= 1e9,
# the max is 1000000001 -> 1st half is 10000
# the min is 1 1st half is 1.
# total of 2 * 1e4 palindromes need to be generated.
# use a generator class to generate the palindromes.

def is_power_of_10(n: int) -> bool:
    if n < 1:
        return False

    while n % 10 == 0:
        n //= 10

    return n == 1

class palindrome_generator:
    def __init__(self):
        self.curr_state = 'odd'
        self.odd_half = 1
        self.even_half = 1

    def step(self) -> int:
        if self.curr_state == 'odd':
            s = str(self.odd_half)
            x = int(s + s[-2::-1])

            self.odd_half += 1
            if is_power_of_10(self.odd_half):
                self.curr_state = 'even'

            return x
        else:
            s = str(self.even_half)
            x = int(s + s[-1::-1])

            self.even_half += 1
            if is_power_of_10(self.even_half):
                self.curr_state = 'odd'

            return x
   
        

class Solution:
    def minOperations(self, nums: list[int]) -> int:
        gen = palindrome_generator()
        even_palindromes = deque[int]()
        odd_palindromes = deque[int]()
        cnt = 0

        nums.sort()

        def step():
            n = gen.step()
            if n % 2 == 0:
                even_palindromes.append(n)
            else:
                odd_palindromes.append(n)

        while len(even_palindromes) < 2:
            step()

        while len(odd_palindromes) < 2:
            step()


        for x in nums:
            if x % 2 == 0:
                while True:
                    if even_palindromes[0] <= x and x < even_palindromes[1]:
                        break
                    else:
                        even_palindromes.popleft()
                        while len(even_palindromes) < 2:
                            step()

                #print(even_palindromes)
                cnt += min(x - even_palindromes[0], even_palindromes[1] - x) // 2

            else:
                while True:
                    if odd_palindromes[0] <= x and x < odd_palindromes[1]:
                        break
                    else:
                        odd_palindromes.popleft()
                        while len(odd_palindromes) < 2:
                            step()

                while len(odd_palindromes) < 2:
                    step()

                #print(odd_palindromes)
                cnt += min(x - odd_palindromes[0], odd_palindromes[1] - x) // 2

        return cnt


sol = Solution()
nums = [9,10,11,10]
ans = sol.minOperations(nums)
print(ans)