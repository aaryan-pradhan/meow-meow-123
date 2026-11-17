# Sum of Four Values (CSES 1642)
# input: n x, then a[1..n]  ->  print 4 distinct 1-based positions whose values sum to x, or IMPOSSIBLE
# example: n=8 x=15, 3 2 5 8 1 3 2 3 -> 2 4 6 7  (any valid answer accepted)
import sys
tok = iter(sys.stdin.read().split())

def solve():
    n = int(next(tok))
    x = int(next(tok))
    v = [0] * (n + 1)
    for i in range(1, n + 1):
        v[i] = int(next(tok))
    m = {}                                  # map<ll, array<ll,2>> -> dict: sum -> (i, j)

    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            m[v[i] + v[j]] = (i, j)

    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            sum_ = v[i] + v[j]
            rem = x - sum_
            if rem in m:                    # m.find(rem) != m.end()
                a, b = m[rem]
                if a != i and a != j and b != i and b != j:
                    print(i, j, a, b)
                    return
    print("IMPOSSIBLE")

solve()