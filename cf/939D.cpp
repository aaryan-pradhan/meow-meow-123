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

// Recall Trail
// 1. Question: buy the fewest letter pairs (c1, c2), each usable any number
//    of times both ways on both strings, so the strings can be made equal.
// 2. Small cases: (ab, da) -> 2, (ax, yz) -> 2, (ab, ba) -> 1. Position i
//    gives the letter pair (s_i, t_i).
// 3. Graph on 26 letters, edges = bought spells. Done iff for every i,
//    s_i and t_i are in the same component (NOT "one component overall").
// 4. Optimal has no cycle: dropping a cycle edge keeps components the same.
//    So a component of k letters costs exactly k - 1 spells.
// 5. Union-find over the n pairs; each union that joins two groups is a
//    spell to print. O(n) on 26 letters.
