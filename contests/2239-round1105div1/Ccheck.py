


with open('gen.in', 'r') as f:
    _ = f.readline()  # number of multitests
    n = int(f.readline().strip())
    data = []
    for _ in range(n):
        char, val = f.readline().strip().split()
        data.append((char, int(val)))


with open('1.out', 'r') as f:
    perm = list(map(int, f.readline().strip().split()))


# Ensure perm is a permutation
for i in range(1, n+1):
    assert i in perm


prefix_invs = 0
for i in range(n):
    for j in range(i):
        if perm[j] > perm[i]:
            prefix_invs += 1
    char, val = data[i]
    if char == 'p':
        assert perm[i] == val
    elif char == 's':
        assert prefix_invs == val


exit(0)
