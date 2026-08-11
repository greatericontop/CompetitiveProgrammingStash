
import random


# def gen_special():
#     n = 6
#     l, r = random.choice([[-4, 0], [0, 4]])
#     print(1)
#     print(n)
#     for i in range(n):
#         print(random.randint(l, r), end=' ' if i < n-1 else '\n')

def gen_max():
    n = 20
    l = -20; r = 20
    print(1)
    print(n)
    for i in range(n):
        print(random.randint(l, r), end=' ' if i < n-1 else '\n')

