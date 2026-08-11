
with open('gen.in', 'r') as f:
    f.readline()
    n = int(f.readline().strip())
    a = list(map(int, f.readline().strip().split()))
    assert len(a) == n

with open('1.out', 'r') as f:
    k = int(f.readline().strip())
    assert k <= 31
    for _op in range(k):
        i, j = map(int, f.readline().strip().split())
        a[i-1] += a[j-1]
    for i in range(len(a) - 1):
        if a[i] > a[i + 1]:
            print(f'WA {a=}')
            exit(1)

