import sys

class BitSet:
    def __init__(self):
        self.set = 0

    def add(self, n):
        self.set |= (1<<n)

    def check(self, n):
        if (self.set & (1<<n)) == 0:
            return 0
        return 1

    def remove(self, n):
        self.set &= ~(1<<n)

    def toggle(self, n):
        self.set ^= (1<<n)

    def all(self):
        self.set = 0x1ffffe

    def empty(self):
        self.set = 0


myset = BitSet()
count = int(input())
for _ in range(count):
    user_line = sys.stdin.readline().split()

    if user_line[0] == "add":
        arg = int(user_line[1])
        myset.add(arg)
    elif user_line[0] == "remove":
        arg = int(user_line[1])
        myset.remove(arg)
    elif user_line[0] == "check":
        arg = int(user_line[1])
        print(myset.check(arg))
    elif user_line[0] == "toggle":
        arg = int(user_line[1])
        myset.toggle(arg)
    elif user_line[0] == "all":
        myset.all()
    elif user_line[0] == "empty":
        myset.empty()
