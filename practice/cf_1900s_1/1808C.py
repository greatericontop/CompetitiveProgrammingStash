t = int(input())

for tt in range(t):
    left, right = map(int, input().split())

    best_luckiness = 1000
    which_num = None

    for i in range(left, right + 1):
        s = [c for c in str(i)]
        s.sort()
        luckiness = int(s[-1]) - int(s[0])
        if luckiness < best_luckiness:
            best_luckiness = luckiness
            which_num = i

    print(which_num)