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

// Recall Trail
// 1. Question: for every i, the cheapest walk from 1 to i, where a step
//    U -> V costs |U - V|, except the shortcut U -> a_U costs 1.
// 2. Simplify: a walk U -> V that never turns back costs the same as
//    stepping one intersection at a time through every node in between.
// 3. So the n^2 walking edges shrink to i -> i + 1 and i -> i - 1 (both
//    directions!), cost 1 each. Add the shortcuts i -> a_i, cost 1.
//    About 3n edges.
// 4. Every edge costs 1, so a walk's energy = its number of edges, so the
//    fewest edges from 1 (plain BFS from the single source 1) = min energy.
// 5. Trap: "always take the shortcut" is false (a_1 = 5, target 2: shortcut
//    costs 4, walking costs 1). BFS picks the edges, not you.
// 6. O(n) for n = 2 * 10^5.
