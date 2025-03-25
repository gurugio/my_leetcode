
def count_vowel(s):
    ret = 0
    for c in s:
        if c in "aeiou":
            ret += 1
    return ret

def go(chars, cur, target, vowel):
    if len(cur) == target:
        #c = count_vowel(cur)
        #if c >= 1 and (target - c) >= 2:
        if vowel >= 1 and (target - vowel) >= 2:
            print(cur)
    elif len(cur) > target or len(chars) == 0:
        return
    else:
        if chars[0] in "aeiou":
            go(chars[1:], cur + chars[0], target, vowel + 1)
        else:
            go(chars[1:], cur + chars[0], target, vowel)
        go(chars[1:], cur, target, vowel)


nums = list(map(int, input().split()))
l = nums[0]
c = nums[1]
chars = "".join(input().split())
go(sorted(chars), "", l, 0)
