# 78. Subsets
class Solution:
    def comb(self, nums: List[int], cur: List[int], k: int) -> List[List[int]]:
        #print("nums={} cur={}".format(nums, cur))
        if len(cur) == k:
            return [cur]
        tmp = []
        for i in range(len(nums)):
            tmp += self.comb(nums[i+1:], cur + [nums[i]], k)
        return tmp
        
    def combine(self, nums: List[int], k: int) -> List[List[int]]:
        return self.comb(nums, [], k)

    def subsets(self, nums: List[int]) -> List[List[int]]:
        res = []
        for i in range(len(nums)+1):
            res += self.combine(nums, i)
        return res

# 77. Combinations
class Solution:
    def comb(self, nums: List[int], cur: List[int], k: int) -> List[List[int]]:
        #print("nums={} cur={}".format(nums, cur))
        if len(cur) == k:
            return [cur]
        tmp = []
        for i in range(len(nums)):
            tmp += self.comb(nums[i+1:], cur + [nums[i]], k)
        return tmp
        
    def combine(self, n: int, k: int) -> List[List[int]]:
        nums = [i for i in range(1, n+1)]
        return self.comb(nums, [], k)
# 75. Sort Colors: swap
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        i = 0
        s = 0
        e = len(nums) - 1
        while i <= e:
            #print("i={} nums={}".format(i, nums))
            if nums[i] == 0:
                t = nums[i]
                nums[i] = nums[s]
                nums[s] = t
                s = s + 1
                if s >= i:
                    i = i + 1
            elif nums[i] == 2:
                t = nums[i]
                nums[i] = nums[e]
                nums[e] = t
                e = e - 1
            else:
                i = i + 1
# 75. Sort Colors
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        count = [0] * 3
        for i in range(len(nums)):
            count[nums[i]] += 1
        print(count)
        for i in range(count[0]):
            nums[i] = 0
        for i in range(count[1]):
            nums[i + count[0]] = 1
        for i in range(count[2]):
            nums[i + count[0] + count[1]] = 2
        
        
# 74. Search a 2D Matrix - quick
class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        start = 0
        end = len(matrix) - 1
        last_col = len(matrix[0]) - 1
        middle = math.floor((start + end) / 2)

        while start < middle:
            #print("{} {} {}".format(start, middle, end))
            if target >= matrix[start][0] and target <= matrix[middle][last_col]:
                end = middle
            elif target > matrix[middle][last_col] and target <= matrix[end][last_col]:
                start = middle + 1
            else:
                return False
            middle = math.floor((start + end) / 2)

        return target in matrix[start] or target in matrix[end]

            
# 74. Search a 2D Matrix
class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        for row in matrix:
            if target >= row[0] and target <= row[-1]:
                for i in row:
                    if target == i:
                        return True
                return False
        return False
    
# 73. Set Matrix Zeroes
class Solution:
    def setZeroes(self, matrix: List[List[int]]) -> None:
        clear_first_row = False
        clear_first_col = False

        for r in range(len(matrix)):
            for c in range(len(matrix[r])):
                if matrix[r][c] == 0:
                    if r == 0:
                        clear_first_row = True
                    if c == 0:
                        clear_first_col = True
                    matrix[r][0] = 0
                    matrix[0][c] = 0
        for c in range(1, len(matrix[0])):
            if matrix[0][c] == 0:
                for r in range(1, len(matrix)):
                    matrix[r][c] = 0
        for r in range(1, len(matrix)):
            if matrix[r][0] == 0:
                for c in range(1, len(matrix[r])):
                    matrix[r][c] = 0
        if clear_first_row:
            for c in range(len(matrix[0])):
                matrix[0][c] = 0
        if clear_first_col:
            for r in range(len(matrix)):
                matrix[r][0] = 0
                
# 71. Simplify Path
class Solution:
    def simplifyPath(self, path: str) -> str:
        path_list = []
        index = 0
        if path[index] != '/':
            return None

        index = 1
        while index < len(path):
            next = path.find("/", index)
            if next == -1:
                next = len(path)
            next_path = path[index:next]

            if next_path == '.':
                pass
            elif next_path == '..':
                if path_list:
                    path_list.pop()
            elif next_path:
                path_list.append(next_path)
            else:
                pass

            index = next + 1

        return "/" + "/".join(path_list)   

# 64. Minimum Path Sum: greedy way + memoization
class Solution:
    def go(self, grid: List[List[int]], row: int, col: int, memo) -> int:
        if (row,col) in memo:
            return memo[(row,col)]

        if col == 0 and row == 0:
            sum = grid[0][0]
        elif row > 0 and col > 0:
            sum = grid[row][col] + min(self.go(grid, row-1, col, memo), self.go(grid, row, col-1, memo))
        elif col == 0:
            sum = grid[row][col] + self.go(grid, row-1, col, memo)
        elif row == 0:
            sum = grid[row][col] + self.go(grid, row, col-1, memo)

        memo[(row,col)] = sum
        return sum
            
    def minPathSum(self, grid: List[List[int]]) -> int:
        return self.go(grid, len(grid) - 1, len(grid[0]) - 1, memo={})
    
# 64. Minimum Path Sum: greedy way
# failed: Time Limit Exceeded
class Solution:
    def go(self, grid: List[List[int]], row: int, col: int) -> int:
        if col == 0 and row == 0:
            return grid[0][0]
        elif row > 0 and col > 0:
            return grid[row][col] + min(self.go(grid, row-1, col), self.go(grid, row, col-1))
        elif col == 0:
            return grid[row][col] + self.go(grid, row-1, col)
        elif row == 0:
            return grid[row][col] + self.go(grid, row, col-1)
        else:
            print("error")
            return 0
            
    def minPathSum(self, grid: List[List[int]]) -> int:
        return self.go(grid, len(grid) - 1, len(grid[0]) - 1)

# 64. Minimum Path Sum: brute force way
# failed: Time Limit Exceeded
class Solution:
    def go(self, grid: List[List[int]], row: int, col: int, sum: int, sum_matrix: List[List[int]]) -> int:
        sum += grid[row][col]
        if sum_matrix[row][col] == 0:
            sum_matrix[row][col] = sum
        elif sum_matrix[row][col] > sum:
            sum_matrix[row][col] = sum
        else:
            return;
        
        last_row = len(grid) - 1
        last_col = len(grid[0]) - 1
        if col == last_col and row == last_row:
            return;
        if col == last_col:
            self.go(grid, row+1, col, sum, sum_matrix)
        elif row == last_row:
            self.go(grid, row, col+1, sum, sum_matrix)
        else:
            self.go(grid, row+1, col, sum, sum_matrix)
            self.go(grid, row, col+1, sum, sum_matrix)
    
    def minPathSum(self, grid: List[List[int]]) -> int:
        sum_matrix = [[9999999] * len(grid[0]) for i in range(len(grid))]
        self.go(grid, 0, 0, 0, sum_matrix)
        return sum_matrix[len(grid)-1][len(grid[0])-1]
    
# 63. Unique Paths II
class Solution:
    def go(self, grid: List[List[int]], row: int, col: int, memo={}) -> int:
        if grid[row][col] == 1:
            return 0

        key = "{}.{}".format(row, col)
        if key in memo:
            return memo[key]

        if row == (len(grid) - 1) and col == (len(grid[0]) - 1):
            return 1
        elif row == (len(grid) - 1):
            ret = self.go(grid, row, col+1, memo)
        elif col == (len(grid[0]) - 1):
            ret = self.go(grid, row+1, col, memo)
        else:
            ret = self.go(grid, row+1, col, memo) + self.go(grid, row, col+1, memo)
        memo[key] = ret
        return ret
        
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        return self.go(obstacleGrid, 0, 0, {})
    
# 62. Unique Paths
class Solution:
    def path(self, m: int, n:int, memo={}) -> int:
        if m == 1 or n == 1:
            return 1
        key = "{},{}".format(m,n)
        if key in memo:
            return memo[key]
        ret = self.path(m-1, n, memo) + self.path(m, n-1, memo)
        memo[key] = ret
        return ret
    def uniquePaths(self, m: int, n: int) -> int:
        return self.path(m, n)

# 59. Spiral Matrix II
class Solution:
    def next_dir(self, dir: int):
        return (dir + 1) % 4

    def go_one(self, r, c, direction):
        nc = c
        nr = r
        if direction == 0: # right
            nc = (nc + 1)
        elif direction == 1: # down
            nr = (nr + 1)
        elif direction == 2: # left
            nc = (nc - 1)
        elif direction == 3: # up
            nr = (nr - 1)
        return (nr, nc)
    
    def go(self, ret: List[List[int]], n: int, cur_row: int, cur_col: int, direction: int, index: int):
        nr, nc = self.go_one(cur_row, cur_col, direction)

        if nc >= n or nr >= n or ret[nr][nc] != 0:
            direction = self.next_dir(direction)
            nr, nc = self.go_one(cur_row, cur_col, direction)
            if nc >= n or nr >= n or ret[nr][nc] != 0:
                return
            self.go(ret, n, cur_row, cur_col, direction, index)
        else:
            #print("{},{}={}".format(nr, nc, index))
            ret[nr][nc] = index + 1
            self.go(ret, n, nr, nc, direction, index + 1)
            
    def generateMatrix(self, n: int) -> List[List[int]]:
        ret = [[0] * n for i in range(n)]
        ret[0][0] = 1
        self.go(ret, n, 0, 0, 0, 1)
        return ret
   
# 57. Insert Interval
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        # sort intervals by first number
        intervals.sort(key=lambda x: x[0])
        ret = [intervals[0]]
        j = 0
        i = 1
        while i < len(intervals):
            if ret[j][0] <= intervals[i][0] and ret[j][1] >= intervals[i][1]:
                #print("new:", ret)
                i += 1
            elif ret[j][1] >= intervals[i][0]: # overlapped exclusively
                # intervals = intervals[:i] + [[intervals[i][0], intervals[i+1][1]]] + intervals[i+2:]
                ret[j] = [ret[j][0], intervals[i][1]]
                #print("new:", ret)
                i += 1
            else:
                ret += [intervals[i]]
                j += 1
                i += 1
        return ret
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        return self.merge(intervals + [newInterval])
   
# 56. Merge Intervals
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        # sort intervals by first number
        intervals.sort(key=lambda x: x[0])
        ret = [intervals[0]]
        j = 0
        i = 1
        while i < len(intervals):
            if ret[j][0] <= intervals[i][0] and ret[j][1] >= intervals[i][1]:
                print("new:", ret)
                i += 1
            elif ret[j][1] >= intervals[i][0]: # overlapped exclusively
                # intervals = intervals[:i] + [[intervals[i][0], intervals[i+1][1]]] + intervals[i+2:]
                ret[j] = [ret[j][0], intervals[i][1]]
                print("new:", ret)
                i += 1
            else:
                ret += [intervals[i]]
                j += 1
                i += 1
        return ret

# 49. Group Anagrams
class Solution:
    def groupAnagrams(self, strs):
        d = {}
        for w in sorted(strs):
            key = "".join(sorted(w))
            #print('key={}'.format(key))
            d[key] = d.get(key, []) + [w]
        return list(d.values())

# 49. Group Anagrams
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        found = [False] * len(strs)
        words = ["".join(sorted(s)) for s in strs]
        ret = []
        for i in range(len(strs)):
            if not found[i]:
                target = words[i]
                found_words = []
                for j in range(i, len(strs)):
                    if target == words[j]:
                        found[j] = True
                        found_words += [strs[j]]

                ret += [found_words.copy()]
                
        return ret
    
# 47. Permutations II
class Solution:
    def do_permute(self, cur: List[int], nums: List[int]) -> List[List[int]]:
        if len(nums) == 1:
            return [cur + [nums[0]]]

        ret = []
        i = 0
        while i < len(nums):
            ret += self.do_permute(cur + [nums[i]], nums[:i] + nums[i+1:])
            while i + 1 < len(nums) and nums[i + 1] == nums[i]:
                i += 1
            i += 1
        return ret
    
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        return self.do_permute([], nums)
# 46. Permutations
class Solution:
    def extract(self, nums: List[int], index: int) -> List[int]:
        ret = nums.copy()
        ret.pop(index)
        return ret

    def do_permute(self, cur: List[int], nums: List[int]) -> List[List[int]]:
        if len(nums) == 1:
            return [cur + [nums[0]]]

        ret = []
        for i in range(len(nums)):
            ret += self.do_permute(cur + [nums[i]], nums[:i] + nums[i+1:])
        return ret
    
    def permute(self, nums: List[int]) -> List[List[int]]:
        return self.do_permute([], nums)
   
# 40. Combination Sum II
class Solution:
    def combi(self, cur: List[int], nums: List[int], target: int) -> List[List[int]]:
        #print('cur={} nums={} target={}'.format(cur, nums, target))
        if target == 0:
            #print('    ret=', cur)
            return [cur]
        elif target < 0:
            return []
        elif not nums:
            return []

        k = 0
        while len(nums) > k and nums[0] == nums[k]:
            k += 1

        ret = []
        for i in range(k + 1):
            ret += self.combi(cur, nums[k:], target)
            cur = cur + [nums[0]]
            target = target - nums[0]
        return ret
    
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        return self.combi([], candidates, target)

# 39. Combination Sum
class Solution:
    def combi(self, cur: List[int], nums: List[int], target: int) -> List[List[int]]:
        #print('cur={} nums={} target={}'.format(cur, nums, target))
        if not nums:
            return []
        elif nums[0] == target:
            #print('    ret=', cur + [nums[0]])
            return [cur + [nums[0]]]
        elif nums[0] < target:
            return self.combi(cur + [nums[0]], nums, target - nums[0]) + self.combi(cur, nums[1:], target)
        else:
            #print('    none')
            return []
    
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        return self.combi([], candidates, target)

# 22. Generate Parentheses
class Solution:
    def gen(self, n: int, cur: str, open: int, close: int) -> List[str]:
        ret1 = []
        ret2 = []
        if open < n:
            ret1 = self.gen(n, cur + '(', open + 1, close)
        if close < open:
            ret2 = self.gen(n, cur + ')', open, close + 1)

        #print("cur={} ret1={} ret2={}".format(cur, ret1, ret2))
        if ret1 or ret2: # cur is not complete set, need to add something
            return ret1 + ret2;
        else: # cur is a complete set, so just return it
            return [cur]

    def generateParenthesis(self, n: int) -> List[str]:
        cur = ''
        return self.gen(n, cur, 0, 0)

# 18. 4Sum
class Solution:
    def threeSum(self, nums: List[int], target) -> List[List[int]]:
        ret = []
        if len(nums) < 3:
            return []

        nums.sort()

        for cur in range(len(nums) - 2):
            left = cur + 1
            right = len(nums) - 1

            # skip duplicated numbers
            if cur > 0 and nums[cur] == nums[cur - 1]:
                continue
        
            while (left < right):
                sum = nums[cur] + nums[left] + nums[right]
                if sum > target:
                    right = right - 1
                elif sum < target:
                    left = left + 1
                else:
                    ret.append([nums[cur], nums[left], nums[right]])

                    # skip duplicated numbers
                    while left < right and nums[left] == nums[left + 1]:
                        left = left + 1
                    left = left + 1
                    while left < right and nums[right - 1] == nums[right]:
                        right = right - 1
                    right = right - 1
        return ret
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        if len(nums) < 4:
            return []
        ret = []
        nums.sort()
        for cur in range(len(nums) - 3):
            # no duplicated
            if cur > 0 and nums[cur] == nums[cur - 1]:
                continue

            tmp = self.threeSum(nums[cur + 1:], target - nums[cur])
            if tmp:
                ret = ret + [[nums[cur]] + x for x in tmp]
        return ret
    
# 16. 3Sum Closest
class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        nums.sort()
        closest = 99999

        for i in range(len(nums) - 2):
            left = i + 1
            right = len(nums) - 1

            while (left < right):
                s = nums[i] + nums[left] + nums[right]
                if abs(s - target) < abs(closest - target):
                    closest = s
                #print("i={} left={} right={} closest={} s={}".format(i, left, right, closest, s))

                if s > target:
                    right = right - 1
                elif s < target:
                    left = left + 1
                else:
                    return closest # same to target
        return closest
                    

# 15. 3Sum
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        ret = []
        if len(nums) < 3:
            return []

        nums.sort()

        for cur in range(len(nums) - 2):
            left = cur + 1
            right = len(nums) - 1

            # skip duplicated numbers
            if cur > 0 and nums[cur] == nums[cur - 1]:
                continue
        
            while (left < right):
                sum = nums[cur] + nums[left] + nums[right]
                if sum > 0:
                    right = right - 1
                elif sum < 0:
                    left = left + 1
                else:
                    ret.append([nums[cur], nums[left], nums[right]])

                    # skip duplicated numbers
                    while left < right and nums[left] == nums[left + 1]:
                        left = left + 1
                    left = left + 1
                    while left < right and nums[right - 1] == nums[right]:
                        right = right - 1
                    right = right - 1
        return ret
