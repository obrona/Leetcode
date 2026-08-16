
# first we find how many digits in the number that contains the kth digit, let it be d
# then we minus from k, then divide by d to find out what block the kth digit is in.
# then we slowly minus and find.

class Solution:
    def kthDigit(self, k: int) -> int:
        # step 1: get num of digits
        p = 1
        while True:
            num_digits = p * 9 * pow(10, p - 1)
            if k - num_digits < 0:
                break
            else:
                k -= num_digits
                p += 1

        if p == 1:
            return k

        #print(p)

        # step 2: get start block number
        block = pow(10, p - 2) + k // (10 * p)
        k = k % (10 * p)

        #print(block)

        # step 3: get number in block, then digit.
        if block % 2 == 0:
            for i in range(0, 10):
                if k > p:
                    k -= p
                else:
                    s = str(10 * block + i)
                    return int(s[k - 1])
        else:
            for i in range(9, -1, -1):
                if k > p:
                    k -= p
                else:
                    s = str(10 * block + i)
                    return int(s[k - 1])

sol = Solution()
print(sol.kthDigit(11))
