from random import *


def gen_xsmall():
    n = 3
    nums = [randint(0, 10) for _ in range(n)]
    print(1)
    print(n)
    print(*nums)


def gen_small():
    n = 5
    nums = [randint(0, 15) for _ in range(n)]
    print(1)
    print(n)
    print(*nums)


def gen_largenum_1():
    n = 2
    nums = [randint(0, 200000) for _ in range(n)]
    print(1)
    print(n)
    print(*nums)


def gen_largenum_2():
    n = 10
    nums = [randint(0, 200000) for _ in range(n)]
    print(1)
    print(n)
    print(*nums)


def gen_largenum_special():
    n = 10
    nums = [choice([0, randint(1, 700), randint(1, 700), randint(700, 200000)]) for _ in range(n)]
    print(1)
    print(n)
    print(*nums)
