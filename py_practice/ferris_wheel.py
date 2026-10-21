# Ferris Wheel (CSES 1090)
# input: n x, then p[0..n-1]  ->  min gondolas; each holds 1 or 2 children with total weight <= x
# example: n=4 x=10, 7 2 3 9 -> 3

import sys
tok = iter(sys.stdin.read().split())

def main():
    n, x = int(next(tok)), int(next(tok))

    p = [int(next(tok)) for _ in range(n)]

    p.sort()

    i, j, count = 0, n - 1, 0
    while i <= j:
        if p[i] + p[j] <= x: i += 1
        j -= 1
        count += 1

    print(count)

main()