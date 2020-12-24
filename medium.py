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
