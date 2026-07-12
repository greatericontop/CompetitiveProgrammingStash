

from random import randint


def gen_insanelysmall():
    print(1)
    n = 2
    print(n)
    l = [f'{randint(1, 8)}' for _ in range(n)]
    print(' '.join(l))


def gen_xxsmall():
    print(1)
    n = 3
    print(n)
    l = [f'{randint(1, 20)}' for _ in range(n)]
    print(' '.join(l))


def gen_xsmall():
    print(1)
    n = 5
    print(n)
    l = [f'{randint(1, 100)}' for _ in range(n)]
    print(' '.join(l))


def gen_small():
    print(1)
    n = 10
    print(n)
    l = [f'{randint(1, 10000)}' for _ in range(n)]
    print(' '.join(l))


def gen_mid():
    print(1)
    n = 50
    print(n)
    l = [f'{randint(1, 100000)}' for _ in range(n)]
    print(' '.join(l))


def gen_max():
    print(1)
    n = 100000
    print(n)
    l = [f'{randint(1, 100000)}' for _ in range(n)]
    print(' '.join(l))
