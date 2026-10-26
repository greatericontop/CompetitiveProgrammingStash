
import math

m, n, p = map(int, input().split())


def fresh():
    return [[0 for inner in range(m+2)] for outer in range(m+2)]


dpprev = fresh()
dpprev[2*n][0] = 1
dpnext = fresh()

if n == 0:
    if p == 0:
        print('1/1')
    else:
        print('0/1')
    exit()


for round in range(0, p):  # 0 to after p (p-1 transitioning to p)
    #print(f'Round {round} (transitioning to {round+1})')

    for unclaimed_ct in range(0, m+2, 2):
        for claimed_ct in range(0, m+2):
            blank_ct = (m-round) - unclaimed_ct - claimed_ct
            state_ct = dpprev[unclaimed_ct][claimed_ct]
            if blank_ct < 0:
                assert state_ct == 0
                continue
            # Taking an unclaimed: lose 2 unclaimed, gain 1 claimed, -1 total
            if unclaimed_ct > 0:
                dpnext[unclaimed_ct-2][claimed_ct+1] += state_ct * unclaimed_ct
            # Taking a claimed
            if claimed_ct > 0:
                dpnext[unclaimed_ct][claimed_ct-1] += state_ct * claimed_ct
            # Taking a blank
            if blank_ct > 0:
                dpnext[unclaimed_ct][claimed_ct] += state_ct * blank_ct
            # In total, our state spreads by a factor of m-p, as intended with the factorial

    #print('Totals:')
    #for unclaimed_ct in range(0, m+2, 2):
    #    print(f'{unclaimed_ct}: claimed ct: {" ".join(map(str, dpprev[unclaimed_ct]))}')

    if round == p-2:  # p-2 -> p-1
        # Prune all that have 0 unclaimed, so the next round only reads the unfinished ones into the finished ones
        for claimed_ct in range(0, m+2):
            dpnext[0][claimed_ct] = 0

    dpprev = dpnext
    dpnext = fresh()


total_ok = sum(dpprev[0])
#print('Number that work: ', total_ok)
total2 = 1
for round in range(1, p+1):
    total2 *= m+1-round

g = math.gcd(total_ok, total2)

num = total_ok//g
denom = total2//g

print(f'{num}/{denom}')

