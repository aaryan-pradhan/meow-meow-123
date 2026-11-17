# Sum of Three Values (CSES 1641)
# input: n x, then a[1..n]  ->  print 3 distinct 1-based positions whose values sum to x, or IMPOSSIBLE
# example: n=4 x=8, 2 7 5 1 -> 1 3 4  (any valid answer accepted)
import sys
tok = iter(sys.stdin.read().split())

def solve():
    n = int(next(tok))
    x = int(next(tok))
    v = [(0, 0)] * n                        # vector<pll>: tuples (fr, sc)
    for i in range(n):
        v[i] = (int(next(tok)), i + 1)       # tuples are immutable: build the whole pair 
    v.sort(key=lambda p: p[0])              # comparator a.fr < b.fr -> key = first field
    for i in range(n):
        l, r = i + 1, n - 1
        while l < r:
            sum_ = v[i][0] + v[l][0] + v[r][0]    # .fr -> [0], .sc -> [1]; "sum" is a builtin, so sum_
            if sum_ == x:
                print(v[i][1], v[l][1], v[r][1])  # print(a, b, c) puts spaces between
                return
            elif sum_ < x:
                l += 1
            else:
                r -= 1
    print("IMPOSSIBLE")

solve()

# how to solve 2 SUM