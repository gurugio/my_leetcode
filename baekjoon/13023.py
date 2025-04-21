from collections import deque

def dfs_findmaxdepth(cur, nodes, visit, depth):
    #print(f'cur={cur} depth={depth} nodes={nodes[cur]}')
    if depth >= 4:
        return depth
    d = []
    for i in nodes[cur]:
        if visit[i] == 0:
            visit[i] = 1
            d.append(dfs_findmaxdepth(i, nodes, visit, depth + 1))
            visit[i] = 0
    if len(d) == 0: # no nodes
        return depth
    else:
        return max(d)


nums = list(map(int, input().split()))
n = nums[0]
m = nums[1]
nodes = [list() for _ in range(n)]
for _ in range(m):
    nums = list(map(int, input().split()))
    src = int(nums[0])
    tgt = int(nums[1])
    nodes[src].append(tgt)
    nodes[tgt].append(src)
#print(nodes)

#n = 5
#nodes = [[1], [0, 2], [1, 3], [2, 4], [3]]
#n=5
#nodes = [[1, 3], [0, 2, 4], [1, 3], [2, 0], [1]]
#n = 6
#nodes = [[1,2,3,4,5], [0], [0], [0], [0], [0]]
#n = 8
#nodes = [[4], [7], [7], [7, 4, 5], [7, 3, 6, 0], [3], [4], [1, 3, 4, 2]]

# DFS
visit = [0] * n
max_depth = 0
for i in range(n):
    #print("start:", i)
    visit[i] = 1
    d = dfs_findmaxdepth(i, nodes, visit, 0)
    visit[i] = 0
    if d >= 4:
        print(1)
        exit()

print(0)