import collections

def possible(channel, broken):
    if channel == 0:
        if broken[0]:
            return 0
        return 1
    l = 0
    while channel > 0:
        if broken[channel % 10]:
            return 0
        channel //= 10
        l += 1
    return l
        

channel = int(input())
n = int(input())
broken = [False] * 10
if n > 0:
    keys = list(map(int, input().split()))
    for k in keys:
        broken[k] = True

#print(broken)
#print(possible(channel, broken))

ans = abs(channel - 100)
for i in range(0, 1000000):
    n = possible(i, broken)
    if n != 0:
        c = abs(i - channel)
        tmp = n + c
    #print(i, n, c, tmp)
        if ans > tmp:
            ans = tmp

print(ans)