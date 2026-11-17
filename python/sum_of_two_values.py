# Sum of Two Values (CSES 1640)
# input: n x, then a[1..n]  ->  print 2 distinct 1-based positions whose values sum to x, or IMPOSSIBLE
# example: n=4 x=8, 2 7 5 1 -> 2 4  (any valid answer accepted)
import sys
tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))
    x = int(next(tok))
    v = [0] * (n + 1)
    f = {}
    for i in range(1 , n+1):
        v[i] = int(next(tok))
        f[v[i]] = i 
    for i in range(1 , n+1):
        r= x - v[i]
        fr = f.get(r , 0)
        if fr != 0 and fr != i :
            print(i , fr)
            return

    print("IMPOSSIBLE")




main()
