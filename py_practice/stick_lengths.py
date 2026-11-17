# Stick Lengths (CSES 1074)
# input: n, then p[0..n-1]  ->  min total cost to make all sticks equal length; changing a stick by d costs |d|
# example: 2 3 1 5 2 -> 5
import sys
tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))

    p = [int(next(tok)) for _ in range(n)]

    p.sort()
    median = p[n // 2]                      # n / 2 on ints -> n // 2 (single / gives a float)

    cost = 0
    for i in range(n): cost += abs(p[i] - median)

    print(cost)

main()