
def go(n):
    if n == 1:
        return 1
    if n == 2:
        return 2
    nums = [0] * (n + 1)
    nums[0] = 1
    nums[1] = 1
    nums[2] = 2

    for i in range(3, n+1):
        nums[i] = nums[i-1] + nums[i-2] + nums[i-3]
    return nums[i]

repeat = int(input())
for _ in range(repeat):
    n = int(input())
    print(go(n))

