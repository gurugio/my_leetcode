repeat = int(input())
for _ in range(0, repeat):
    nums = list(map(int, input().split()))
    M = nums[0]
    N = nums[1]
    x = nums[2]
    y = nums[3]
    modx = x - 1
    mody = y - 1
    found = 0

    for i in range(0, 40000):
        try_year = i * M + modx
        if try_year % N == mody:
            print(try_year + 1)
            found = 1
            break
    if found == 0:
        print(-1)
