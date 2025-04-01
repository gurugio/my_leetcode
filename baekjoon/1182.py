
import sys

def find(nums, s):
    ret = 0
    for i in range(1, 1<<(len(nums))):
        sum = 0
        #print("i=", i)
        for j in range(len(nums)):
            if (i & (1<<j)) != 0:
                sum += nums[j]
                #print("add:", nums[j])
        if sum == s:
            ret += 1

    return ret


#nums = [-7, -3, -2, 5, 8]
#s = 0

user_line = sys.stdin.readline().split()
n = int(user_line[0])
s = int(user_line[1])

user_line = sys.stdin.readline().split()
nums = [0] * n
for i in range(n):
    nums[i] = int(user_line[i])
print(find(nums, s))