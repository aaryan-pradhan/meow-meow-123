

// orz
#include <bits/stdc++.h>

#define ll long long
#define endl "\n"
#define fr first
#define sc second
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define mp make_pair
#define PI acos(-1)
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define pll pair<ll,ll>

using namespace std;

ll fun(vector<ll>& a, ll idx)
{
    return (a[idx] + a[idx+2] - a[idx+4]);
}

void solve()
{
    ll n;
    cin >> n;
    vector<ll> a(n);

    for(ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    map<ll,ll> freq;
    vector<ll> b(n-4);

    for(ll i = 0; i < n-4; i++)
    {
        b[i] = fun(a,i);
        freq[b[i]]++;
    }

    ll ans = 0;

    for(auto x : freq)
    {
        ll no = x.sc;
        ans += no * (no-1) / 2;
    }

    for(ll i = 0; i < n-4; i++)
    {
        if(i+2 < n-4 && b[i] == b[i+2])
        {
            ans--;
        }

        if(i+4 < n-4 && b[i] == b[i+4])
        {
            ans--;
        }
    }

    cout << ans << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;

    while(t--)
    {
        solve();
    }
}
