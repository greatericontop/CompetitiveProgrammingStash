
from random import randint, choice


def gen_1():
    print(100)
    for t in range(100):
        n = 1
        a = [-1 if i == 0 or i == n else choice([-1, randint(1, n+5)]) for i in range(n+1)]
        print(n)
        print(' '.join(map(str, a)))


def gen_xsmall():
    print(1)
    n = 3
    a = [-1 if i == 0 or i == n else choice([-1, randint(1, n+5)]) for i in range(n+1)]
    print(n)
    print(' '.join(map(str, a)))


def gen_xsmall_2():
    print(1)
    n = 3
    a = [-1 if i == 0 or i == n else choice([-1, -1, randint(1, n+5)]) for i in range(n+1)]
    print(n)
    print(' '.join(map(str, a)))


def gen_small():
    print(1)
    n = 5
    a = [-1 if i == 0 or i == n else choice([-1, -1, -1, randint(1, n+3)]) for i in range(n+1)]
    print(n)
    print(' '.join(map(str, a)))


def gen_mid():
    print(1)
    n = 7
    a = [-1 if i == 0 or i == n else choice([-1, -1, -1, randint(1, n+5)]) for i in range(n+1)]
    print(n)
    print(' '.join(map(str, a)))


def gen_segfault():
    print(1)
    n = 3
    a = [-1 if i == 0 or i == n else choice([-1, randint(1, 1_000_000_000)]) for i in range(n+1)]
    print(n)
    print(' '.join(map(str, a)))
