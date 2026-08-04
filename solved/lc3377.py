import math
import heapq

# just normal dijkstra.

class Sieve:
    def __init__(self, n: int):
        self.is_prime = [False, False] + [True for _ in range(2, n + 1)]

        limit = math.floor(math.sqrt(n))
        for i in range(2, limit + 1):
            if not self.is_prime[i]:
                continue
            for j in range(i * i, n + 1, i):
                self.is_prime[j] = False

    def isprime(self, num: int) -> bool:
        return self.is_prime[num]
    
sieve = Sieve(10000)
    
def get_neighbours(x: int) -> list[int]:
    x_str = str(x)
    num_digits = len(x_str)
    out = []
    for i in range(num_digits):
        d = ord(x_str[num_digits - 1 - i]) - ord('0')
        if d < 9:
            out.append(x + 10 ** i)
        if (i < num_digits - 1 and d > 0) or d > 1:
            out.append(x - 10 ** i)
    return out

class Solution:
    def minOperations(self, n: int, m: int) -> int:
        if sieve.isprime(n):
            return -1
        
        seen: dict[int, int] = {}
        pq = []
        
        heapq.heappush(pq, (n, n))
        while len(pq) > 0:
            d, x = heapq.heappop(pq)
            #print(d, x)
            if x in seen:
                continue
            seen[x] = d
            if x == m:
                return d
            for next in get_neighbours(x):
                if next in seen or sieve.isprime(next):
                    continue
                heapq.heappush(pq, (next + d, next))

        return -1


print(get_neighbours(10))
sol = Solution()
n = 10
m = 12
ans = sol.minOperations(n, m)
print(ans)