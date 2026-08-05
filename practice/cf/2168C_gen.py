
import sys

with open('gen.in', 'w') as f:
    sys.stdout = f
    print('first')
    print(32768)
    for i in range(1, 32769):
        print(i)

