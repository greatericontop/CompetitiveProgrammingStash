

from random import randint

def gen_small():
    n = randint(1, 9)
    s = ''.join(['0' if randint(1, 2) == 1 else '1' for i in range(n)])
    if s == '0'*n:
        s = '1' + s[1:]
    print(1)
    print(n)
    print(s)

def gen_big():
    n = 10000
    s = ''.join(['0' if randint(1, 2) == 1 else '1' for i in range(n)])
    print(1)
    print(n)
    print(s)
