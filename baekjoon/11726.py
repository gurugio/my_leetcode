

def go(n):
    if n < 0:
        print("minus")
    if n == 0:
        return 1
    elif n == 1:
        return go(n-1)

    return go(n-1) + go(n-2)

n = int(input())
print(go(n))
