from collections.abc import Sequence, Callable
import random

"""
Explanation: Z-function + longest non-increasing run + multiset hashing.

------------------------------------------------------------------------------
1. When does sorting suffix i produce a window w = target[k : k + N]?
------------------------------------------------------------------------------
Sorting nums[i..N-1] in non-increasing order gives

        nums[0..i-1]  +  sorted_desc(nums[i..N-1])
        (untouched)      (sorted part)

This equals w exactly when ALL three hold:

  (A) w[0..i-1] == nums[0..i-1]                     (prefix is unchanged)
  (B) w[i..N-1] is non-increasing                   (it looks sorted)
  (C) multiset(w[i..N-1]) == multiset(nums[i..N-1]) (same elements)

(B) + (C) together say w[i..N-1] IS sorted_desc(nums[i..N-1]), because there
is only one non-increasing arrangement of a multiset.

------------------------------------------------------------------------------
2. Turning each condition into a range of valid i
------------------------------------------------------------------------------
  (A) Let p = length of the longest common prefix of w and nums (capped at N).
      (A) holds  <=>  i <= p.
      p comes from the Z-function of nums + target: z at position N + k is the
      LCP of target[k:] with nums (it may run past N, hence min(N, ...)).

  (B) Let L = length of the longest non-increasing run of target that ENDS at
      w's last element, target[k + N - 1]. Then the last L elements of w are
      non-increasing (L may be longer than the window, hence the max(0, ...)).
      Let s = max(0, N - L).
      (B) holds  <=>  i >= s.

  (C) This looks like it depends on i, but it does not -- for any i <= p:
      w and nums agree on positions i..p-1 (by definition of p), so

          multiset(w[i..N-1])    = multiset(w[i..p-1])    + multiset(w[p..N-1])
          multiset(nums[i..N-1]) = multiset(nums[i..p-1]) + multiset(nums[p..N-1])
          but note that multiset(nums[i..p-1]) = multiset(w[i..p-1]) because nums[0..p-1] = w[0..p-1]

      so (C) holds for every i in [0, p]  <=>  multiset(w[p..N-1]) ==
      multiset(nums[p..N-1]). ONE hash comparison decides it for the whole
      range. The multiset hash is sum(random_weight[v]) mod 2^61 - 1, which
      is order-independent and O(1) per range via prefix sums.

So the valid i are exactly the integers in [s, p] (if the hash check passes),
giving p - s + 1 of them, or 0 if p < s or the hashes differ.

Edge case: i must be a real index, 0 <= i <= N - 1. If p == N (the window
equals nums exactly), the range [s, N] includes i = N, which isn't a valid
suffix start, so subtract 1. (s <= N - 1 always since L >= 1, so the range
still contains i = N - 1.) When p == N the hash check compares two empty
ranges, both 0, so it passes, as it should.

Everything is O(N + M).

------------------------------------------------------------------------------
3. Worked example
------------------------------------------------------------------------------
    nums   = [4, 1, 3, 2, 2]                 N = 5
    target = [5, 4, 3, 2, 2, 1, 4, 1, 3]     M = 9
    answer = [0, 2, 0, 0, 0]

All suffix sorts of nums (brute force, for reference):
    i = 0: sort [4,1,3,2,2]  -> [4, 3, 2, 2, 1]
    i = 1: [4] + sort [1,3,2,2] -> [4, 3, 2, 2, 1]
    i = 2: [4,1] + sort [3,2,2] -> [4, 1, 3, 2, 2]
    i = 3: [4,1,3] + [2,2]      -> [4, 1, 3, 2, 2]
    i = 4: [4,1,3,2] + [2]      -> [4, 1, 3, 2, 2]

Pick k = 1:  w = target[1:6] = [4, 3, 2, 2, 1].  Expected answer: 2 (i=0, 1).

    index:   0  1  2  3  4
    w    :   4  3  2  2  1
    nums :   4  1  3  2  2
             ^  x
    p: w[0] == nums[0] = 4, w[1] = 3 != nums[1] = 1, so p = 1.
       (z_func(nums + target)[N + 1] = 1.)
       -> condition (A) gives i <= 1. Any i >= 2 would leave nums[1] = 1
          untouched at position 1, but w has a 3 there.

    s: the non-increasing run ending at target[5] = 1 is
       target[0..5] = 5,4,3,2,2,1, so L = 6 (longer than the window!).
       s = max(0, 5 - 6) = 0.
       -> condition (B) gives i >= 0: the whole window already looks sorted.

    p >= s, so check the hash of the part after the common prefix:
       multiset(nums[1..4]) = {1, 3, 2, 2}
       multiset(w[1..4])    = {3, 2, 2, 1}   -> equal, check passes.
       By the argument in (C) that also covers i = 0: adding the shared
       element 4 (nums[0] == w[0]) to both sides keeps them equal.

    p != N, so no correction.
    ans[1] = p - s + 1 = 1 - 0 + 1 = 2   (i = 0 and i = 1)

Compare k = 4: w = [2, 1, 4, 1, 3]. p = 0 (2 != 4). The run ending at
target[8] = 3 is just [3] (1 < 3), so L = 1, s = 4. p < s -> 0.
"""

def z_func[T](arr: Sequence[T]) -> list[int]:
    N = len(arr)
    z = [0] * N
    l, r = 0, 0
    for i in range(1, N):
        if i < r:
            z[i] = min(r - i, z[i - l])
        while i + z[i] < N and arr[i + z[i]] == arr[z[i]]:
            z[i] += 1
        if i + z[i] > r:
            l, r = i, i + z[i]
    return z


MOD = (1 << 61) - 1
_weight: dict[int, int] = {}


def _w(v: int) -> int:
    if v not in _weight:
        _weight[v] = random.randrange(1, MOD)
    return _weight[v]


def prefix_multiset_hash(arr: list[int]) -> Callable[[int, int], int]:
    N = len(arr)
    res = [0] * N
    for i in range(N):
        if i == 0:
            res[i] = _w(arr[i])
        else:
            res[i] = (res[i - 1] + _w(arr[i])) % MOD

    def subarray_hash(l: int, r: int) -> int:
        lres = 0 if l == 0 else res[l - 1]
        return (res[r] - lres) % MOD

    return subarray_hash


def get_longest_suffix_desc(arr: list[int]) -> list[int]:
    N = len(arr)
    res = [1] * N
    for i in range(1, N):
        if arr[i] <= arr[i - 1]:
            res[i] = 1 + res[i - 1]
        else:
            res[i] = 1
    return res

class Solution:
    def countSuffix(self, nums: list[int], target: list[int]) -> list[int]:
        N = len(nums)
        M = len(target)
        longest_same_prefix = z_func(nums + target)[len(nums):]
        nums_hasher = prefix_multiset_hash(nums)
        target_hasher = prefix_multiset_hash(target)
        longest_suffix_desc = get_longest_suffix_desc(target)

        res = [0] * (M - N + 1)
        for i in range(M - N + 1):
            p = min(N, longest_same_prefix[i])
            s = max(0, N - longest_suffix_desc[i + N - 1])

            if p < s:
                continue
            else:
                res[i] = p - s + 1 if nums_hasher(p, N - 1) == target_hasher(i + p, i + N - 1) else 0

                # if longest prefix length == len(nums) need to -1 because need to sort >= 1 elem
                if p == N:
                    res[i] -= 1

        return res

sol = Solution()
nums = [7,5]
target = [10,2,3,7,5]
ans = sol.countSuffix(nums, target)
print(ans)
