
from random import randint


def gen_small():
    print(1)
    n = 6
    print(n)
    colors = [randint(1, n) for _ in range(n)]
    print(*colors)
    for i in range(2, n+1):
        print(randint(1, i-1), i)
