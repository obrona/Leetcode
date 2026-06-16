class Solution:
    def checkGoodInteger(self, n: int) -> bool:
        sum_of_digits = sum(map(lambda c: ord(c) - ord('0'), str(n)))
        sum_of_squared = sum(map(lambda c: (ord(c) - ord('0')) ** 2, str(n)))
        return sum_of_squared - sum_of_digits >= 50