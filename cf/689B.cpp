#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve()
{
    ll n; cin >> n;
    vector<vector<ll>> g(n + 1);
    for (ll i = 1; i <= n; i++)
    {
        ll a; cin >> a;
        g[i].push_back(a);
        if (i > 1)
        {
            g[i].push_back(i - 1);
        }
        if (i < n)
        {
            g[i].push_back(i + 1);
        }
    }
    vector<ll> vis(n + 1), dist(n + 1, -1);
    queue<ll> qu;
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
    for (ll i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
