import collections

directions = [[-1, 0], [0, -1], [1, 0], [0, 1]]

def checkxy(x, y, n):
    return x >= 0 and x < n and y >= 0 and y < n

def bfs(matrix, n, i, j, visit, count):
    que = collections.deque()
    que.append((i, j))

    while len(que) != 0:
        x, y = que.popleft()
        visit[x][y] = count
        for dx, dy in directions:
            if checkxy(dx + x, dy + y, n):
                if matrix[dx + x][dy + y] == 1 and visit[dx+x][dy+y] == 0:
                    que.append((dx + x, dy + y))

"""matrix = [[0,1,1,0,1,0,0],
[0,1,1,0,1,0,1],
[1,1,1,0,1,0,1],
[0,0,0,0,1,1,1],
[0,1,0,0,0,0,0],
[0,1,1,1,1,1,0],
[0,1,1,1,0,0,0]]
"""

n = int(input())
matrix = [[0] * n for _ in range(n)]
for i in range(n):
    l = input()
    for j in range(n):
        matrix[i][j] = int(l[j])

#print(matrix)
visit = [[0] * n for _ in range(n)]
count = 0

for i in range(n):
    for j in range(n):
        if matrix[i][j] == 1 and visit[i][j] == 0:
            count += 1
            bfs(matrix, n, i, j, visit, count)

#print(visit)
num_house = [0] * (count + 1)

for i in range(n):
    for j in range(n):
        if visit[i][j] != 0:
            num_house[visit[i][j]] += 1

num_house.sort()
print(count)
for i in range(1, count + 1):
    print(num_house[i])