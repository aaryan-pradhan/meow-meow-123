# Nearest Smaller Values (CSES 1645)
# input: n, then x[1..n]  ->  for each i print the nearest position j < i with x[j] < x[i], or 0 if none
# example: 2 5 1 4 8 3 2 5 -> 0 1 0 3 4 3 3 7
import sys
tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))
    v = [0] * (n + 1)
    for i in range(1,n+1):
        v[i] = int(next(tok))
    c = []
    ans = []
    for i in range(1,n+1):
        while c and v[c[-1]] >= v[i]:
            c.pop()
        if not c:
            ans.append(0)
        else:
            ans.append(c[-1])
        c.append(i)
    print(*ans)


main()
