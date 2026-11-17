import sys
tok = iter(sys.stdin.read().split())

def main():
    out = []
    t = int(next(tok))
    for _ in range(t):                      # while (t--)
        n = int(next(tok))
        a = [0] * n                         # vector<int> a(n)
        evens, odds = [], []
        for i in range(n):
            a[i] = int(next(tok))
            if a[i] % 2 == 0: evens.append(a[i])    # push_back -> append
            else: odds.append(a[i])
        evens.sort()                        # sort(evens.begin(), evens.end())
        odds.sort()

        ei, oi = 0, 0
        for i in range(n):
            if a[i] % 2 == 0:
                a[i] = evens[ei] 
                ei += 1   
            else:
                a[i] = odds[oi]
                oi += 1
        print(*a) 

    
        


main()