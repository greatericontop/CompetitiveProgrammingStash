
import contextlib
import random


def gen_large():
    q = 2_000_000
    maxval = 1_000_000_000
    print(q)
    keys = [random.randint(1, maxval) for i in range(q)]
    for i in range(q):
        op = random.choice(['=', '?'])
        if op == '=':
            k = keys[random.randint(0, q-1)]
            print(op, k, random.randint(1, maxval))
        elif op == '?':
            k = keys[random.randint(0, q-1)]
            print(op, k)


if __name__ == '__main__':
    f = open('gen.in', 'w')
    with contextlib.redirect_stdout(f):
        gen_large()
