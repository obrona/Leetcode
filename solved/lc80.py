# simple 2 pointers

class Solution:
    def removeDuplicates(self, nums: list[int]) -> int:
        place, next = 0, 0 # place is where we are placing, next is the idx of number we are considering.
        prev = -int(1e9) # to know whether nums[next] is seen before or a new number.
        prev_cnt = 0
        cnt = 0

        while next < len(nums):
            if nums[next] == prev:
                if prev_cnt >= 2:
                    next += 1
                else:
                    nums[place] = nums[next]
                    prev_cnt += 1
                    cnt += 1
                    place += 1
                    next += 1

            else:
                nums[place] = nums[next]
                prev = nums[next]
                prev_cnt = 1
                cnt += 1
                place += 1
                next += 1


        return cnt
    

sol = Solution()
nums = [0,0,0,1,1,2]
k = sol.removeDuplicates(nums)
print(nums, k)