# Beautiful Permutation (CSES 1070)
# input: n  ->  print a permutation of 1..n with no adjacent pair differing by exactly 1, or NO SOLUTION
import sys

tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))
    if n == 2 or n == 3:
        print("NO SOLUTION")
        return
    ans = []
    for i in range(2 , n+1, 2):
        ans.append(i)
    for i in range(1, n+1, 2):
        ans.append(i)
    print(*ans)

main()
    
    