import sys
tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))

    x = [int(next(tok)) for _ in range(n)]

    x.sort()

    distinct = 1 if n > 0 else 0
    for i in range(1, n):
        if x[i] != x[i - 1]: distinct += 1

    print(distinct)

main()