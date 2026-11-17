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
