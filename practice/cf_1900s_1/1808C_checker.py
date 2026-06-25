
with open('gen.in', 'r') as f:
    f.readline()
    left, right = map(int, f.readline().split())

with open('1.out', 'r') as f:
    ans1 = int(f.readline().strip())

with open('2.out', 'r') as f:
    ans2 = int(f.readline().strip())


s1 = [int(c) for c in str(ans1)]
s2 = [int(c) for c in str(ans2)]

l1 = max(s1) - min(s1)
l2 = max(s2) - min(s2)

assert left <= ans1 <= right
assert left <= ans2 <= right

if l1 != l2:
    print('WA luckinesses are different')
    exit(10)
