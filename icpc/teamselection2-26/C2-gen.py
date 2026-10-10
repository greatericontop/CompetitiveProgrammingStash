

from random import randint

def gen_1():
    n = 10000
    s = ''.join(['0' if randint(1, 2) == 1 else '1' for i in range(n)])
    print(1)
    print(n)
    print(s)
