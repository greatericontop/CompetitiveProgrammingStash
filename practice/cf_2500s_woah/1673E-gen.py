from random import *


# def gen_xsmall():
#     n = 3
#     k = choice([0, 0, 1, 1, 2, 2, 3])
#     print(n, k)
#     b = [choice([1, 1, 1, 2, 3]) for _ in range(n)]
#     print(*b)


def gen_small():
    n = 7
    k = choice([0, 0, 1, 1, 2, 2, 3, 4, 5, 6])
    print(n, k)
    b = [choice([1, 1, 1, 2, 3, 4]) for _ in range(n)]
    print(*b)

