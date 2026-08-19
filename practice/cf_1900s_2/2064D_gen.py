
from random import randint

def gen_xsmall():
    print(1)
    n = 4; q = 1
    print(n, q)
    for i in range(n):
        print(randint(0, 15), end=' ')
    print()
    for i in range(q):
        print(randint(0, 15), end=' ')
    print()


def gen_mid():
    print(1)
    n = 10; q = 5
    print(n, q)
    for i in range(n):
        print(randint(0, 2**30-1), end=' ')
    print()
    for i in range(q):
        print(randint(0, 2**30-1), end=' ')
    print()
