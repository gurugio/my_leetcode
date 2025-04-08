
def go(curr, prices, n, memo):
    if curr < 0:
        return -1
    elif curr == 0:
        return 0
    
    if memo[curr] != -1:
        #print("return memo:", curr, memo[curr])
        return memo[curr]

    ret = []
    for i in range(1, n + 1):
        t = go(curr - i, prices, n, memo)
        if t >= 0:
            ret.append(t + prices[i])

    memo[curr] = min(ret)
    #print("memo", curr, memo[curr])
    return memo[curr]


n = int(input())
p = [0] * (n + 1)
temp = list(map(int, input().split()))
for i in range(1, n + 1):
    p[i] = temp[i-1]
memo = [-1] * (n + 1)    
print(go(n, p, n, memo))