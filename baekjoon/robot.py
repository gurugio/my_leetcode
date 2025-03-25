
board = [[0,0,0,0,2,0,0,0,0,0],
         [0,0,1,1,1,1,1,0,0,0],
         [0,0,1,1,1,1,1,1,0,0],
         [0,0,1,1,1,1,1,0,1,0],
         [0,0,1,1,1,1,1,0,0,0],
         [0,0,0,0,3,0,0,0,1,0]]
min_cost = [[0 for _ in range(len(board[0]))] for _ in range(len(board))]

def go(cur_cost, row, col):
    if row < 0 or col < 0 or row >= len(board) or col >= len(board[0]):
        return
    if board[row][col] == 2:
        return

    if board[row][col] == 0:
        cur_cost += 1
    elif board[row][col] == 1:
        cur_cost += 2
    elif board[row][col] == 3:
        cur_cost += 1
    
    if cur_cost < min_cost[row][col] or min_cost[row][col] == 0:
        print("cur pos:", row, col, "cost:", cur_cost)
        min_cost[row][col] = cur_cost
    else:
        # No need to go ahead
        return
    go(cur_cost, row - 1, col)
    go(cur_cost, row + 1, col)
    go(cur_cost, row, col - 1)
    go(cur_cost, row, col + 1)


cur_cost = 0
row = 0
col = 4
go(cur_cost, row - 1, col)
go(cur_cost, row + 1, col)
go(cur_cost, row, col - 1)
go(cur_cost, row, col + 1)

print(min_cost)
print(min_cost[5][4])