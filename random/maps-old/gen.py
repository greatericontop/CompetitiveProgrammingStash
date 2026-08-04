
import contextlib
import random


def gen_large():
    n = 500_000
    q = 500_000
    maxval = 1_000_000_000
    keys = random.sample(range(maxval), n)
    data = [(k, random.randint(0, maxval)) for k in keys]
    print(n)
    print(q)
    for k, v in data:
        print(k, v)
    random.shuffle(data)
    for k, v in data:
        print(k)


if __name__ == '__main__':
    f = open('gen.in', 'w')
    with contextlib.redirect_stdout(f):
        gen_large()