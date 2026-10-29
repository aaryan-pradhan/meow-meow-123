# Problem: Two Sets II — Python practice
# Link: https://cses.fi/problemset/task/1093
# Pattern: 0/1 knapsack counting (subset-sum ways) + modular inverse of 2
# Time: O(n * S), S = n(n+1)/4  (~31M steps at n = 500, ~4 s in CPython: TLE on CSES)
# Space: O(n * S)
#
# Count the ways the numbers 1, 2, ..., n can be divided into two sets of
# equal sum. Print the answer modulo 1e9+7.
# For n = 7 there are four solutions:
#   {1,3,4,6} and {2,5,7}
#   {1,2,5,6} and {3,4,7}
#   {1,2,4,7} and {3,5,6}
#   {1,6,7}   and {2,3,4,5}
#
# Input:   n
# Output:  one integer, the number of ways modulo 1e9+7
# Limits:  1 <= n <= 500, time limit 1 s
# Sample:  7  ->  4
#
# Run:  python3 dp/Two_Sets_II_practice.py           -> self-check (sample + brute tests)
#       echo 7 | python3 dp/Two_Sets_II_practice.py  -> reads CSES-format stdin
import sys

MOD = 10**9 + 7

def madd(a , b):
    return (a%MOD + b%MOD)%MOD
def mmul(a , b):
    return (a%MOD * b%MOD) %MOD
def mpow(a , b):
    res = 1 
    while(b):
        if (b & 1):
            res = mmul(res , a)
        a = mmul(a , a)
        b >>= 1
    return res
def minv(a):
    return mpow(a , MOD - 2)
def mdiv(a , b):
    return a * minv(b) % MOD
def solve(n):
    s = n * ( n + 1 ) // 2 
    if (s%2 == 1):
        return 0 
 
    s = s // 2 
    dp = [[0] * (s + 1) for _ in range(2)]
    for i in range(n + 1, 0, -1):
        for l in range(s+1):
            if (i == (n+1)):
                if (l > 0):
                    dp[(i&1)][l] = 0
                    continue
                else:
                    dp[(i&1)][l] = 1
                    continue
            ans = 0 
            t = 0 
            if ((l-i) >= 0):
                t = dp[(i+1)&1][l-i]
            nt = dp[(i+1)&1][l]
            ans = madd(t , nt)
            dp[(i&1)][l] = ans 
    return mdiv(dp[1][s] , 2)


def brute(n):
    """Every split of 1..n — only for checking small n."""
    total = n * (n + 1) // 2
    ways = 0
    for mask in range(1 << n):
        s = sum(i + 1 for i in range(n) if mask >> i & 1)
        if 2 * s == total:
            ways += 1
    return ways // 2


def check():
    assert solve(7) == 4, "sample"
    for n in range(1, 17):
        got, want = solve(n), brute(n)
        assert got == want, (n, got, want)
    print("all tests pass")


if __name__ == "__main__":
    if sys.stdin.isatty():
        check()
    else:
        print(solve(int(sys.stdin.read())))


# Recall Trail
# Pattern: count subsets of 1..n summing to S/2 (0/1 knapsack, count version), then halve.
# - S = n(n+1)/2 odd -> 0 ways. Target s = S // 2 (integer division, never /).
# - dp[i][l] = ways to make sum l using numbers i..n. Base row i = n+1: 1 if l == 0 else 0.
# - dp[i][l] = dp[i+1][l] (skip i) + dp[i+1][l-i] (take i, only if l >= i; Python's
#   negative index would silently wrap). Items are 1..n, so the loop stops at i = 1.
# - Each split {A, B} is counted twice, and you can't // 2 a value taken mod p:
#   multiply by the inverse of 2 = 2^(p-2) (Fermat, p prime).
# - Faster: a 1D dp with l looping downward, skipping n (n sits in the other set) -> no halving.
