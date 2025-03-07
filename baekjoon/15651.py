tmp = list(map(int, input().split()))
m = tmp[0]
n = tmp[1]

nums = []
for i in range(1, m + 1):
    nums.append(i)

def find(nums, ret, depth):
    #print("===", nums, ret, depth)
    if depth == 0:
        for i in ret:
            print(i, end=' ')
        print()
        return
    for i in range(0, len(nums)):
        find(nums, ret + [nums[i]], depth - 1)

find(nums, [], n)