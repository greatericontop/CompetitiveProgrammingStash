
from random import randint

MAX = 10**18


# def gen_small_interval():
#     left = randint(1, 10000)
#     right = left + randint(1, 1000)
#     right = min(right, MAX)
#     print(1)
#     print(left, right)
#
#
# def gen_big_interval():
#     left = randint(1, MAX)
#     right = left + randint(1, 100000)
#     right = min(right, MAX)
#     print(1)
#     print(left, right)


def gen_borderline_interval():
    left = randint(10**18 - 500, 10**18)
    right = left + randint(1, 500)
    right = min(right, MAX)
    print(1)
    print(left, right)


def gen_tiny_interval():
    left = randint(1, 10)
    right = left + randint(0, 10)
    right = min(right, MAX)
    print(1)
    print(left, right)