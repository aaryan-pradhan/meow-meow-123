#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve()
{
    ll n, m; cin >> n >> m;
    vector<vector<ll>> rail(n + 1, vector<ll>(n + 1));
    for (ll i = 0; i < m; i++)
    {
        ll u, v; cin >> u >> v;
        rail[u][v] = rail[v][u] = 1;
    }
    vector<vector<ll>> tg(n + 1), rg(n + 1);
    for (ll u = 1; u <= n; u++)
    {
        for (ll v = 1; v <= n; v++)
        {
            if (u == v)
            {
                continue;
            }
            if (rail[u][v])
            {
                tg[u].push_back(v);
            }
            else
            {
                rg[u].push_back(v);
            }
        }
    }
    auto bfs = [&](vector<vector<ll>> &g)
    {
        vector<ll> vis(n + 1), dist(n + 1, -1);
        queue<ll> qu                      ;
        qu.push(1); vis[1] = 1; dist[1] = 0;
        while (!qu.empty())
        {
            ll u = qu.front(); qu.pop();
            for (ll v : g[u])
            {
                if (!vis[v])
                {
                    vis[v] = 1; dist[v] = dist[u] + 1;
                    qu.push(v);
                }
            }
        }
        return dist[n];
    };
    ll t = bfs(tg), b = bfs(rg);
    if (t == -1 || b == -1)
    {
        cout << -1 << "\n";
        return;
    }
    cout << max(t, b) << "\n";
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}

// Recall Trail
// 1. Question: minimize max(train arrival, bus arrival) at n, never in the
//    same town (except n) at the same time.
// 2. Simplify: drop the meeting rule -> each vehicle alone is a BFS
//    (unit edges), answer max of the two.
// 3. Fact: every pair has exactly one of railway / road. So the pair (1, n)
//    is one of them: one vehicle reaches n at time 1.
// 4. Proof the rule never breaks: the fast one is at n from time 1 on, and n
//    is allowed. (Two BFS paths in general CAN meet: U-V rail, K-V road.)
// 5. Answer = BFS on both graphs, max of the two; -1 if either can't reach n.
// 6. Road graph is the complement, up to n^2 edges: O(n^2) for n = 400.
