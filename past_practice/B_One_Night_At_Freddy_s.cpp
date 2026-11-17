#include "bits/stdc++.h"

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

void solve()
{
    ll n, m, L;
    cin >> n >> m >> L;

    deque<ll> f(n);
    for(ll i = 0; i < n; i++) 
        cin >> f[i];

    deque<ll> d(m, 0);

    ll prev = 0;

    for(ll i = 0; i <= n; i++)
    {
        ll cur=(i == n?L:f[i]);
        ll gap = cur - prev;
        prev = cur;
        ll rem = n - i;
        ll k = min(m, rem + 1);
        sort(d.begin(), d.end());
        if(gap > 0)
        {
            deque<ll> top(k);
            for(ll j = 0; j < k; j++)
                top[j] = d[m - k + j];

            for(ll j = 0; j < k - 1; j++)
            {
                ll diff = top[j + 1] - top[j];
                ll cost = diff * (j + 1);
                if(gap >= cost)
                {
                    gap -= cost;
                    for(ll x = 0; x <= j; x++)
                        top[x] = top[j + 1];
                }
                else
                {
                    ll add = gap / (j + 1);
                    ll rem2 = gap % (j + 1);
                    for(ll x = 0; x <= j; x++)
                        top[x] += add;
                    for(ll x = j - rem2 + 1; x <= j; x++)
                        top[x]++;
                    gap = 0;
                    break;
                }
            }
            if(gap > 0)
            {
                ll add = gap / k;
                ll rem2 = gap % k;
                for(ll x = 0; x < k; x++)
                    top[x] += add;
                for(ll x = k - rem2; x < k; x++)
                    top[x]++;
            }
            for(ll j = 0; j < k; j++)
                d[m - k + j] = top[j];
        }
        if(i < n)
        {
            auto it = max_element(d.begin(), d.end());
            *it = 0;
        }
    }

    cout << *max_element(d.begin(), d.end()) << endl;
}
signed main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t ; 
    cin >> t ;
    while(t--)  
        solve() ; 
} 
