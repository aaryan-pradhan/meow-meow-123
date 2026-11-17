#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<ll> par, sz;

ll find(ll x)
{
    if (par[x] == x)
    {
        return x;
    }
    return par[x] = find(par[x]);
}

void merge(ll x, ll y)
{
    x = find(x); y = find(y);
    if (x == y)
    {
        return;
    }
    if (sz[x] < sz[y])
    {
        swap(x, y);
    }
    par[y] = x;
    sz[x] += sz[y];
}

void solve()
{
    ll n; cin >> n;
    string s, t; cin >> s >> t;
    par.assign(26, 0); sz.assign(26, 1);
    for (ll i = 0; i < 26; i++)
    {
        par[i] = i;
    }
    vector<pair<char, char>> ans;
    for (ll i = 0; i < n; i++)
    {
        ll x = s[i] - 'a', y = t[i] - 'a';
        if (find(x) != find(y))
        {
            merge(x, y);
            ans.push_back({s[i], t[i]});
        }
    }
    cout << ans.size() << "\n";
    for (auto [a, b] : ans)
    {
        cout << a << " " << b << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
