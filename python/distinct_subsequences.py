# Distinct Subsequences (CSES 2429)
# input: n, then x[0..n-1]  ->  print count of non-empty subsequences with all elements distinct, mod 1e9+7
# example: 1 2 1 3 -> 11
import sys
tok = iter(sys.stdin.read().split())
MOD = 10**9 + 7
def madd(a, b):
    return (a%MOD + b%MOD)%MOD
def msub(a, b):
    return (a%MOD - b%MOD + MOD)%MOD
def mmul(a, b):
    return (a%MOD * b%MOD)%MOD

def main():
    n = int(next(tok))
    x = [int(next(tok)) for _ in range(n)]
    f = {}
    for i in range(n):
        f[x[i]] = f.get(x[i],0) + 1 
    ans = 1 
    for val , fr in f.items():
        ans = mmul(ans , fr + 1)
    ans = msub(ans , 1)
    print(ans)




    

main()
