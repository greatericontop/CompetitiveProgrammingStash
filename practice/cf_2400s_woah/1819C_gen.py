
import random

def gen_small():
    n = 6
    l = list(range(1, n+1))
    random.shuffle(l)
    print(n)
    for i in range(1, n):
        print(l[i], l[random.randint(0, i-1)])


def gen_mid():
    n = 100
    l = list(range(1, n+1))
    random.shuffle(l)
    print(n)
    for i in range(1, n):
        print(l[i], l[random.randint(0, i-1)])
