# do it step by step.
# bring all the 0 to the front.
# recurse on the remaining array.

class Solution:
    def sortColors(self, nums: list[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        def bring_to_front(arr: list[int], x: int, s: int, e: int):
            p = s
            for i in range(s, e + 1):
                if arr[i] != x:
                    continue

                if p == i:
                    p += 1
                    continue
                else:
                    while p <= e and arr[p] == x:
                        p += 1
                    assert(p < i)
                    arr[p], arr[i] = arr[i], arr[p]
                    p += 1
            return p

        s = 0
        for x in range(0, 3):
            s = bring_to_front(nums, x, s, len(nums) - 1)
            #print(x, s, nums)


sol = Solution()
arr = [2,1,2,2,0]
sol.sortColors(arr)
print(arr)
        