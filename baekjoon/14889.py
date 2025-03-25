

def get_power(team):
    global matrix
    p = 0
    for i in range(len(team) - 1):
        for j in range(i+1, len(team)):
            p = p + matrix[team[i]][team[j]] + matrix[team[j]][team[i]]
    return p


def go(n, index, startteam, linkteam):
    #global ans
    #global n
    if len(startteam) > n//2 or len(linkteam) > n//2:
        return 1000000
    if index == n:
        if len(startteam) == n//2:
            #print("match:", startteam, linkteam)
            return abs(get_power(startteam) - get_power(linkteam))
    
    t1 = go(n, index + 1, startteam + [index], linkteam)
    t2 = go(n, index + 1, startteam, linkteam + [index])
    if t1 < t2:
        return t1
    return t2

n = int(input())
ans = 1000
matrix = [[0 for _ in range(n)] for _ in range(n)]

for i in range(n):
    nums = list(map(int, input().split()))
    for j in range(n):
        matrix[i][j] = nums[j]

print(go(n, 0, [], []))
