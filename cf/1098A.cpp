#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<vector<ll>> g;
vector<ll> h, s;

void dfs1(ll u, ll p)
{
    h[u] = h[p] + 1;
    for (ll v : g[u])
    {
        if (v != p)
        {
            dfs1(v, u);
        }
    }
}

void dfs2(ll u, ll p)
{
    if (h[u] % 2 == 0)
    {
        ll mn = LLONG_MAX;
        for (ll v : g[u])
        {
            if (v != p)
            {
                mn = min(mn, s[v]);
            }
        }
        if (mn == LLONG_MAX)
        {
            s[u] = s[p];
        }
        else
        {
            s[u] = mn;
        }
    }
    for (ll v : g[u])
    {
        if (v != p)
        {
            dfs2(v, u);
        }
    }
}

void solve()
{
    ll n; cin >> n;
    g.assign(n + 1, {}); h.assign(n + 1, 0); s.assign(n + 1, 0);
    vector<ll> par(n + 1);
    for (ll i = 2; i <= n; i++)
    {
        cin >> par[i];
        g[par[i]].push_back(i);
    }
    for (ll i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    dfs1(1, 0);
    dfs2(1, 0);
    ll ans = s[1];
    for (ll i = 2; i <= n; i++)
    {
        if (s[i] < s[par[i]])
        {
            cout << -1 << "\n";
            return;
        }
        ans += s[i] - s[par[i]];
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}

// Recall Trail
// 1. Known s_v and s_p give a_v = s_v - s_p, which must be >= 0.
// 2. Erased (even-depth) v: for each child c, a_v + a_c = s_c - s_p is
//    fixed. Raising a_v by 1 lowers every child by 1, so the total changes
//    by 1 - (#children) <= 0. Push a_v as high as allowed.
// 3. a_c >= 0 for all children caps it: a_v = min over children of
//    (s_c - s_p), i.e. s_v = min child s. No children: a_v = 0, s_v = s_p.
// 4. Answer -1 if any a_v < 0 (some s_v < s_p).
// 5. dfs1 gets depth, dfs2 fills s at even depth, a loop sums
//    a_i = s_i - s_par. O(n). Sum up to 1e5 * 1e9, long long.
