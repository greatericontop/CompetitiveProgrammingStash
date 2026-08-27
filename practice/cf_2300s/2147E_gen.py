
from random import randint

def gen_xsmall():
    print(1)
    n, q = 3, 1
    print(n, q)
    a = [randint(0, 10) for _ in range(n)]
    print(*a)
    for _ in range(q):
        x = randint(0, 10)
        print(x)


def gen_small():
    print(1)
    n, q = 3, 5
    print(n, q)
    a = [randint(0, 30) for _ in range(n)]
    print(*a)
    for _ in range(q):
        x = randint(0, 30)
        print(x)
