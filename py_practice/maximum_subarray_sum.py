# Maximum Subarray Sum (CSES 1643)
# input: n, then x[0..n-1]  ->  print best contiguous non-empty sum
import sys
tok = iter(sys.stdin.read().split())



def main():
    n = int(next(tok))
    x = [] 
    for _ in range(n):
        y = int(next(tok))
        x.append(y)
    c , b = x[0] , x[0]
    for i in range(1,n):
        c = max(x[i],c + x[i])
        b = max(b , c)
    print(b)


main()