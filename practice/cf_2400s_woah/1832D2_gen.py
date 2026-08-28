
import random


def gen_xxxsmall():
    n = random.randint(1, 2)
    l = [random.randint(1, 10) for _ in range(n)]
    print(n, 1)
    print(*l)
    query = random.randint(0, 20)
    print(query)


def gen_xxsmall():
    n = 3
    l = [random.randint(1, 10) for _ in range(n)]
    print(n, 1)
    print(*l)
    query = random.randint(0, 3)
    print(query)


def gen_xsmall():
    n = 5
    l = [random.randint(1, 20) for _ in range(n)]
    print(n, 1)
    print(*l)
    query = random.randint(0, 7)
    print(query)


def gen_small():
    n = 7
    l = [random.randint(1, 30) for _ in range(n)]
    print(n, 1)
    print(*l)
    query = random.randint(0, 8)
    print(query)
