# Missing Coin Sum (CSES 2183)
# input: n, then x[0..n-1] (coin values)  ->  smallest sum that cannot be made from a subset of the coins
# example: 2 9 1 2 7 -> 6
import sys
tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))

    x = [int(next(tok)) for _ in range(n)]

    x.sort()

    r = 0
    for i in range(n):
        if x[i] > r + 1: break
        r += x[i]

    print(r + 1)

main()