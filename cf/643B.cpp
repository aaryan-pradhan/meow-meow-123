#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve()
{
    ll n, k; cin >> n >> k;
    ll a, b, c, d; cin >> a >> b >> c >> d;
    if (n == 4 || k < n + 1)
    {
        cout << -1 << "\n";
        return;
    }
    deque<ll> mid;
    for (ll i = 1; i <= n; i++)
    {
        if (i != a && i != b && i != c && i != d)
        {
            mid.push_back(i);
        }
    }
    deque<ll> p = mid, q = mid;
    p.push_front(c); p.push_front(a); p.push_back(d); p.push_back(b);
    q.push_front(a); q.push_front(c); q.push_back(b); q.push_back(d);
    for (ll x : p)
    {
        cout << x << " ";
    }
    cout << "\n";
    for (ll x : q)
    {
        cout << x << " ";
    }
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
