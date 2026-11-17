# Maximum Difference
# input: n (>= 2), then arr[0..n-1]  ->  print max arr[j] - arr[i] over i < j  (can be negative)
import sys
tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))
    a = [int(next(tok)) for _ in range(n)]
    me = a[0]
    md = a[1] - a[0]
    for i in range(1,n):
        md = max(md , a[i] - me)
        me = min(a[i], me)
    print(md)
main()

