#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve()
{
    ll n, m; cin >> n >> m;
    vector<string> a(n);
    for (string &s : a)
    {
        cin >> s;
    }
    ll si = 0, sj = 0, ti = 0, tj = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (a[i][j] == 'S')
            {
                si = i; sj = j;
            }
            if (a[i][j] == 'T')
            {
                ti = i; tj = j;
            }
        }
    }
    vector<ll> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
    auto enc = [&](ll i, ll j, ll d)
    {
        return (i * m + j) * 4 + d;
    };
    auto dec = [&](ll u)
    {
        return array<ll, 3>{u / 4 / m, u / 4 % m, u % 4};
    };
    auto nei = [&](ll u)
    {
        auto [i, j, d] = dec(u);
        vector<pair<ll, ll>> r;
        for (ll e = 0; e < 4; e++)
        {
            ll x = i + dx[e], y = j + dy[e];
            if (x >= 0 && x < n && y >= 0 && y < m && a[x][y] != '*')
            {
                r.push_back({e != d, enc(x, y, e)});
            }
        }
        return r;
    };
    vector<ll> dist(n * m * 4, LLONG_MAX);
    deque<ll> qu;
    for (ll d = 0; d < 4; d++)
    {
        dist[enc(si, sj, d)] = 0;
        qu.push_back(enc(si, sj, d));
    }
    while (!qu.empty())
    {
        ll u = qu.front(); qu.pop_front();
        for (auto [w, v] : nei(u))
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                if (w == 0)
                {
                    qu.push_front(v);
                }
                else
                {
                    qu.push_back(v);
                }
            }
        }
    }
    ll ans = LLONG_MAX;
    for (ll d = 0; d < 4; d++)
    {
        ans = min(ans, dist[enc(ti, tj, d)]);
    }
    cout << (ans <= 2 ? "YES" : "NO") << "\n";
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
