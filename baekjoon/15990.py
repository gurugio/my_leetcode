
def go_recursive(n, last, table):
    if n <= 3:
        return table[n][last]

    if table[n][last] != -1:
        #print(f'get {n}-{last}={table[n][last]}')
        return table[n][last]
    if last == 1:
        t = go_fix(n - 1, 2, table) + go_fix(n - 1, 3, table)
    elif last == 2:
        t = go_fix(n - 2, 1, table) + go_fix(n - 2, 3, table)
    elif last == 3:
        t = go_fix(n - 3, 1, table) + go_fix(n - 3, 2, table)
    table[n][last] = t % 1000000009
    #print(f'set {n}-{last}={table[n][last]}')
    return t


def go_loop(n, table):
    for i in range(4, n + 1):
        table[i][1] = (table[i - 1][2] + table[i - 1][3]) % 1000000009
        table[i][2] = (table[i - 2][1] + table[i - 2][3]) % 1000000009
        table[i][3] = (table[i - 3][1] + table[i - 3][2]) % 1000000009
    return (table[n][1] + table[n][2] + table[n][3]) % 1000000009

table = [[0] * 4 for i in range(100002)]
table[1][1] = 1
table[2][2] = 1
table[3][1] = 1
table[3][2] = 1
table[3][3] = 1
go_loop(100001, table)

repeat = int(input())
for _ in range(repeat):
    n = int(input())
    print((table[n][1] + table[n][2] + table[n][3]) % 1000000009)
    