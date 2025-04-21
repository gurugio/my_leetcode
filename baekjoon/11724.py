import collections
import sys

def bfs(start, nodes, visit):
    que = collections.deque()
    que.append(start)

    while len(que) != 0:
        c = que.popleft()
        visit[c] = 1
        #print(f'set {c} <= {counter}')
        for i in nodes[c]:
            if visit[i] == 0:
                que.append(i)

"""n = 6
nodes = [[], [2, 5], [1, 5], [4], [3, 6], [2, 1], [4]]
"""

nums = list(map(int, sys.stdin.readline().split()))
n = nums[0]
m = nums[1]
nodes = [list() for _ in range(n + 1)]
for _ in range(m):
    nums = list(map(int, sys.stdin.readline().split()))
    src = int(nums[0])
    tgt = int(nums[1])
    nodes[src].append(tgt)
    nodes[tgt].append(src)

visited = [0] * (n + 1)
counter = 0
for i in range(1, n + 1):
    if visited[i] == 0:
        counter += 1
        bfs(i, nodes, visited)
print(counter)
