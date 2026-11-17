import sys
tok = iter(sys.stdin.read().split())

def main():
    n = int(next(tok))

    pos = [0] * (n + 1)
    for i in range(1, n + 1):
        x = int(next(tok))
        pos[x] = i

    rounds = 1
    for i in range(2, n + 1):
        if pos[i] < pos[i - 1]: rounds += 1

    print(rounds)

main()