import sys
tok = iter(sys.stdin.read().split())

def main():
    n, m = int(next(tok)), int(next(tok))     # cin >> n >> m

    x, pos = [0] * (n + 1), [0] * (n + 1)
    for i in range(1, n + 1):
        x[i] = int(next(tok))
        pos[x[i]] = i


    def isBad(k):                      
        if pos[k] < pos[k - 1]: 
            return 1
        return 0

    breaks = 1
    for k in range(2, n + 1): breaks += isBad(k)

    out = []
    for q in range(m):
        a, b = int(next(tok)), int(next(tok))
        u, v = x[a], x[b]

        node = set()               
        for w in (u, v):
            if w >= 2: node.add(w)
            if w + 1 <= n: node.add(w + 1)

        for k in node: breaks -= isBad(k)

        pos[u], pos[v] = pos[v], pos[u]     # swap(pos[u], pos[v])
        x[a], x[b] = x[b], x[a]

        for k in node: breaks += isBad(k)

        out.append(breaks)
    print(*out , sep='\n')
main()