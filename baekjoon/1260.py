import collections

def dfs(cur, nodes, visit):
    visit[cur] = 1
    print(cur, end=" ")
    for i in sorted(nodes[cur]):
        if visit[i] == 0:
            dfs(i, nodes, visit)

def bfs(start, nodes, visit):
    que = collections.deque()
    que.append(start)
    visit[start] = 1

    while len(que) != 0:
        c = que.popleft()
        print(c, end=" ")
        for i in sorted(nodes[c]):
            if visit[i] == 0:
                visit[i] = 1
                que.append(i)


nums = list(map(int, input().split()))
n = nums[0]
m = nums[1]
v = nums[2]

nodes = [list() for _ in range(n + 1)]
for _ in range(m):
    nums = list(map(int, input().split()))
    src = int(nums[0])
    tgt = int(nums[1])
    nodes[src].append(tgt)
    nodes[tgt].append(src)
#print(nodes)


#v = 1
#n = 4
#nodes = [[], [2, 3, 4], [1, 4], [1, 4], [1, 2, 3]]

#v=3
#n=5
#nodes=[[], [2, 3], [5, 1], [4, 1], [5, 3], [4, 2]]
dfs(v, nodes, [0] * (n + 1))
print("")
bfs(v, nodes, [0] * (n + 1))
print("")