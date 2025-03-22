

def go(ops, nums, used, k, inequation):
    global max
    global min
    if len(inequation) == k + 1:
        res = False
        print(inequation)
        for i in range(len(ops)):
            op = ops[i]
            left = inequation[i]
            right = inequation[i+1]
            print(left, op, right)
            if op == '>' and left > right:
                res = True
            elif op == '<' and left < right:
                res = True
            else:
                res = False
                break
        if res == True:
            print("found true====")
            print(f"cur min={min} max={max}")
            if inequation < min:
                print("set min:", inequation)
                min = inequation
            if inequation > max:
                print("set max:", inequation)
                max = inequation
        return

    for i in range(len(nums)):
        if used[i] == False:
            used[i] = True
            go (ops, nums, used, k, inequation + nums[i])
            used[i] = False


k = 2
nums = "0123456789"
used = [False] * 10
ops = "<>"
max = "0"*(k+1)
min = "9"*(k+1)

go(ops, nums, used, k, "")
print(max, min)
    
    

