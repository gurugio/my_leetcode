
k = int(input())


counter = [0]*1000001
counter[0] = 1000000
counter[1] = 1
counter[2] = 1
counter[3] = 1

for i in range(4, k+1):
    temp = []
    temp.append(counter[i - 1] + 1)
    if (i % 3) == 0:
        temp.append(counter[i // 3] + 1)
    if (i % 2) == 0:
        temp.append(counter[i // 2] + 1)
    counter[i] = min(temp)

print(counter[k])
