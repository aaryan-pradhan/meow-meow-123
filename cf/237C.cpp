#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve()
{
    ll a, b, k; cin >> a >> b >> k;
    vector<ll> p(b + 1, 1), pre(b + 1);
    p[0] = p[1] = 0;
    for (ll i = 2; i * i <= b; i++)
    {
        if (p[i])
        {
            for (ll j = i * i; j <= b; j += i)
            {
                p[j] = 0;
            }
        }
    }
    for (ll i = 1; i <= b; i++)
    {
        pre[i] = pre[i - 1] + p[i];
    }
    auto check = [&](ll l)
    {
        for (ll x = a; x + l - 1 <= b; x++)
        {
            if (pre[x + l - 1] - pre[x - 1] < k)
            {
                return false;
            }
        }
        return true;
    };
    ll lo = 1, hi = b - a + 1, ans = -1;
    while (lo <= hi)
    {
        ll mid = (lo + hi) / 2;
        if (check(mid))
        {
            ans = mid; hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
