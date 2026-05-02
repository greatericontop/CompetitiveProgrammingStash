


import random

random.seed(19)





if __name__ == '__main__':
    n = 25
    print(1)
    print(n)
    print(' '.join(str(random.randint(0, 16)) for _ in range(n)))