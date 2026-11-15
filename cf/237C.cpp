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

// Recall Trail
// 1. Sieve up to b, then prefix count pre[i] = primes in [1, i], so any
//    window [x, x + l - 1] has pre[x + l - 1] - pre[x - 1] primes in O(1).
// 2. check(l) slides x over a..b - l + 1: O(b - a).
// 3. Monotone: any (l + 1)-window contains the l-window at the same x, so
//    check over l is 0 0 0 1 1 1. Binary search the first 1 in [1, b - a + 1].
// 4. -1 exactly when even the full range [a, b] has fewer than k primes
//    (b - a + 1 < k is only one such case: 1 4 3 has length 4 but 2 primes).
//    No 1 in the 0-1 array, so ans stays -1.
// 5. Total O(b log log b + (b - a) log(b - a)), about 2e7 for b = 1e6.
