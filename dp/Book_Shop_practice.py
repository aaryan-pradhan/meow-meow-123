# Problem: Book Shop — Python practice
# Link: https://cses.fi/problemset/task/1158
#
# A shop sells n books. Book i costs h[i] and has s[i] pages. You can spend at
# most x in total and buy each book at most once. What is the maximum number
# of pages you can buy?
#
# Input:   n x / h_1 .. h_n / s_1 .. s_n
# Output:  one integer, the maximum number of pages
# Limits:  1 <= n <= 1000, 1 <= x <= 1e5, 1 <= h_i, s_i <= 1000
# Sample:  4 10 / 4 8 5 3 / 5 12 8 1  ->  13  (books 1 and 3: price 9, pages 13)
#
# Run:  python3 dp/Book_Shop_practice.py          -> self-check (sample + random tests)
#       python3 dp/Book_Shop_practice.py < in.txt -> reads CSES-format stdin
import random
import sys


def solve(n, x, h, s):
    # dp[i][b] is the budget left and i am on step i and i need to go from step i to the n what is the maximmum number of pages that i can buy 
    # dp[i][b] = max(dp[i+1][b - h[i]]) + s[i] , dp[i+1][b] ) 
    dp = [[-1] * (x + 1) for _ in range(2)]
    for i in range(n , -1, -1):
        for b in range(x+1):
            if i == n:
                if b >= 0:
                    dp[(i&1)][b] = 0
                    continue 

            ans = 0 
            ans = dp[(i+1)&1][b]
            if b >= h[i]:
                ans = max(ans , dp[(i+1)&1][b-h[i]] + s[i])
            dp[(i&1)][b] = ans 
        
    return dp[0][x]

            




def brute(n, x, h, s):
    """Every subset — only for checking small cases."""
    best = 0
    for mask in range(1 << n):
        cost = pages = 0
        for i in range(n):
            if mask >> i & 1:
                cost += h[i]
                pages += s[i]
        if cost <= x:
            best = max(best, pages)
    return best


def check():
    assert solve(4, 10, [4, 8, 5, 3], [5, 12, 8, 1]) == 13, "sample"
    for _ in range(300):
        n = random.randint(1, 10)
        x = random.randint(1, 40)
        h = [random.randint(1, 15) for _ in range(n)]
        s = [random.randint(1, 20) for _ in range(n)]
        got, want = solve(n, x, h, s), brute(n, x, h, s)
        assert got == want, (n, x, h, s, got, want)
    print("all tests pass")


if __name__ == "__main__":
    if sys.stdin.isatty():
        check()
    else:
        data = sys.stdin.read().split()
        n, x = int(data[0]), int(data[1])
        h = list(map(int, data[2:2 + n]))
        s = list(map(int, data[2 + n:2 + 2 * n]))
        print(solve(n, x, h, s))
