
n = int(input())
s = input()

words = s.split()

def count(str):
    a = 0
    for ch in str:
        if ch.isupper():
            a += 1;
    return a

ans = max([count(t) for t in words])

print(ans)