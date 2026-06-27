
from random import *


# def gen_sample():
#     print(1)
#     print(3)
#     print('p', 1)
#     print('p', 2)
#     print('p', 3)


def gen_small_rng():
    print(1)
    n = 10
    print(n)
    perm = list(range(1, n+1))
    shuffle(perm)

    prefix_invs = 0
    for i in range(n):
        for j in range(i):
            if perm[j] > perm[i]:
                prefix_invs += 1
        if randint(1, 2) == 1:
            print('p', perm[i])
        else:
            print('s', prefix_invs)


def gen_mid_rng():
    print(1)
    n = 400
    print(n)
    perm = list(range(1, n+1))
    shuffle(perm)

    prefix_invs = 0
    for i in range(n):
        for j in range(i):
            if perm[j] > perm[i]:
                prefix_invs += 1
        if randint(1, 2) == 1:
            print('p', perm[i])
        else:
            print('s', prefix_invs)
