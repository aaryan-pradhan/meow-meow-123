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

// Recall Trail
// 1. Question: build two paths through all n cities, a...b and c...d, no
//    road a-b or c-d, at most k distinct roads total; else -1.
// 2. Fact: distinct = 2n - 2 - shared, so maximize shared roads.
// 3. n = 4 is impossible: the a...b path's middle is {c, d}, forcing c-d.
// 4. Construction: a c x1..xm d b and c a x1..xm b d (m = n - 4). Shared:
//    a-c, b-d and the m - 1 middle roads -> n + 1 distinct roads.
// 5. Proof n + 1 is the minimum: in path 1, a and b are endpoints (1 road
//    each); in path 2 they are inside (2 roads each). With only n roads the
//    single extra road must touch both, i.e. be a-b: forbidden.
// 6. Answer -1 if n == 4 or k < n + 1, else print the two paths. O(n).
