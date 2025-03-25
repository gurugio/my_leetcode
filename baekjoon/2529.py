

def go(ops, nums, used, k, inequation):
    global max
    global min
    if len(inequation) == k + 1:
        res = False
        for i in range(len(ops)):
            op = ops[i]
            left = inequation[i]
            right = inequation[i+1]
            if op == '>' and left > right:
                res = True
            elif op == '<' and left < right:
                res = True
            else:
                res = False
                break
        if res == True:
            if inequation < min:
                min = inequation
            if inequation > max:
                max = inequation
        return

    for i in range(len(nums)):
        if used[i] == False:
            used[i] = True
            go (ops, nums, used, k, inequation + nums[i])
            used[i] = False


#k = 2
#k = 9
#ops = "<>"
#ops = "><<<>>><<"

k = int(input())
ops = list(input().split())
ops = "".join(ops)
nums = "0123456789"
used = [False] * 10
max = "0"*(k+1)
min = "9"*(k+1)
go(ops, nums, used, k, "")
print(max)
print(min)
    
    

