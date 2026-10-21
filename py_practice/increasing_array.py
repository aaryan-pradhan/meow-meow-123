# Increasing Array (CSES 1094)
# input: n, then x[0..n-1]  ->  print min total +1 moves to make the array non-decreasing
import sys
tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))
    a = [int(next(tok)) for _ in range(n)]
    ans = 0 
    for i in range(1,n):
        co = a[i] - a[i-1]
        if co < 0:
            ans += -co
            a[i] = a[i-1]
    print(ans)

main() 

