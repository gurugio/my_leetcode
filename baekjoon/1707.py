import collections

def bfs(start, nodes, visit):
    que = collections.deque()
    color = 1
    visit[start] = color
    que.append((start, color))

    while len(que) != 0:
        cur, color = que.popleft()
        for i in nodes[cur]:
            if visit[i] == 0:
                que.append((i, 3 ^ color))
                visit[i] = color

repeat = int(input())
for _ in range(repeat):
    nums = list(map(int, input().split()))
    n = nums[0]
    m = nums[1]

    nodes = [list() for _ in range(n + 1)]
    for _ in range(m):
        nums = list(map(int, input().split()))
        src = int(nums[0])
        tgt = int(nums[1])
        nodes[src].append(tgt)
        nodes[tgt].append(src)

    start = 1
    visit = [0] * (n + 1)
    bfs(1, nodes, visit)

    found = True
    for i in range(1, n):
        if visit[i] != 0 and visit[i+1] != 0 and visit[i] == visit[i+1]:
            found = False
    if found == False:        
        print("NO")
    else:    
        print("YES")
