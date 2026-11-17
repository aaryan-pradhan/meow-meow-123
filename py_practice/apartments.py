# Apartments (CSES 1084)
# input: n m k, then a[0..n-1] (desired sizes), b[0..m-1] (apartment sizes)
#   ->  max applicants matched; applicant takes apartment of size in [a-k, a+k], each apartment used once
# example: n=4 m=3 k=5, a = 60 45 80 60, b = 30 60 75 -> 2
import sys
tok = iter(sys.stdin.read().split())

def main():
    n, m, k = int(next(tok)), int(next(tok)), int(next(tok))

    a = [int(next(tok)) for _ in range(n)]
    b = [int(next(tok)) for _ in range(m)]

    a.sort()
    b.sort()

    i, j, count = 0, 0, 0
    while i < n and j < m:
        if b[j] < a[i] - k: j += 1
        elif b[j] > a[i] + k: i += 1        # else if -> elif
        else: count += 1; i += 1; j += 1

    print(count)

main()