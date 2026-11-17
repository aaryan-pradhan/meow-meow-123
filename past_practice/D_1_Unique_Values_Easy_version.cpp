
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

ll query(vector<ll>& s) 
{
    cout << "? " << s.size() << " ";
    for (ll v : s) 
    {
        cout << v << " ";
    }
    cout << endl;
    cout.flush();

    ll r;
    cin >> r;
    if (r == -1)
    {
        exit(0);
    }
    return r;
}


bool check(ll mid, ll ss, ll l) 
{
    vector<ll> s;
    
    for (ll i = 1; i <= mid; i++) 
    {
        s.push_back(i);
    }

    for (ll i = ss; i <= l; i++) 
    {
        s.push_back(i);
    }

    return (query(s) % 2 != s.size() % 2) ; 
    
}


ll bs(ll lo, ll hi, ll ss , ll l) 
{
    ll ans = hi; 
    while (lo <= hi) 
    {
        ll mid = lo + (hi - lo) / 2;
        
        if (check(mid, ss, l)) 
        {
            ans = mid;     
            hi = mid - 1;  
        } 
        else 
        {
            lo = mid + 1; 
        }
    }
    return ans;
}

void solve() 
{
    ll n;
    cin >> n;
    ll l = 2 * n + 1;
    
 
    ll z = bs(1, l , l + 1, l);
    ll y = bs(1, z - 1, z, l);
    ll x = bs(1, y - 1, y, l);
    
    cout << "! " << x << " " << y << " " << z << endl;
    cout.flush();
}

signed main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t;
    for (ll i = 0; i < t; i++) 
    {
        solve();
    }
}