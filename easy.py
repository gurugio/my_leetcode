# 1221. Split a String in Balanced Strings
class Solution:
    def balancedStringSplit(self, s: str) -> int:
        counter = 0
        ret = 0
        for c in s:
            if c == 'R':
                counter += 1
            else:
                counter -= 1
                
            if counter == 0:
                ret += 1
        return ret


