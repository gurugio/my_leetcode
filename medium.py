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
