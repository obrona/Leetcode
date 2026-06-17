# reduce the problem to largest rectangle in histogram.
# then check for each row.

# for largest rectangle in histogram, for each bar we find
# the first bar < this bar to the left and to the right.
# use a monotonic stack for this.

# for the matrix, do some preprocessing.
# namely for each pos (i, j) find the length of consecutive '1s' in the column upwards.

# time complexity is O(nm)

def first_shorter_bar_left(nums: list[int]) -> list[int]:
    stack: list[tuple[int,int]] = []
    out = []
    for i, x in enumerate(nums):
        while len(stack) > 0 and stack[-1][1] >= x:
            stack.pop()
        
        if len(stack) == 0:
            out.append(-1)
        else:
            out.append(stack[-1][0])
        stack.append((i, x))

    return out

def first_shorter_bar_right(nums: list[int]) -> list[int]:
    stack = []
    out = [-1] * len(nums)
    for i in range(len(nums) - 1, -1, -1):
        while len(stack) > 0 and stack[-1][1] >= nums[i]:
            stack.pop()
        
        if len(stack) == 0:
            out[i] = len(nums)
        else:
            out[i] = stack[-1][0]
        stack.append((i, nums[i]))

    return out

def largest_rectangle_in_histogram(nums: list[int]) -> list[int]:
    left = first_shorter_bar_left(nums)
    right = first_shorter_bar_right(nums)
    return max(map(lambda i: (right[i] - left[i] - 1) * nums[i], range(len(nums))))

class Solution:
    def maximalRectangle(self, matrix: list[list[str]]) -> int:
        R, C = len(matrix), len(matrix[0])
        temp = [[0 for _ in range(C)] for _ in range(R)]
        
        for r in range(R):
            for c in range(C):
                temp[r][c] = 0 if matrix[r][c] == '0' else 1 + (temp[r - 1][c] if r > 0 else 0)

        return max(map(largest_rectangle_in_histogram, temp))
 
sol = Solution()
matrix =  [["1"]]
print(sol.maximalRectangle(matrix))