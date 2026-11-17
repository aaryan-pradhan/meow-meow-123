// orz
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

ll gcd(ll a, ll b) 
{
    while (b) 
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

void solve() 
{
    ll n ; 
    cin >> n ;

    vector < ll > a(n) ;
    for(ll i = 0 ; i < n ; i++ ) 
    {
        cin >> a[i] ;
    }
    

    vector < ll > b(n) ;
    for(ll i = 0 ; i < n ; i++ ) 
    {
        cin >> b[i] ;
    }

    vector < ll > g(n - 1) ;
    for(ll i = 0 ; i < n - 1 ; i++ ) 
    {
        g[i] = gcd(a[i], a[i + 1]) ;
    }

    ll ans = 0  ;
    

    if(g[0] < a[0]) 
    {
        ans++ ;
    }
    

    if(g[n - 2] < a[n - 1]) 
    {
        ans++ ;
    }
    

    for(ll i = 1 ; i < n - 1 ; i++ ) 
    {
        ll p = g[i - 1] ;
        ll c = g[i] ;
        

        ll cur = (p * c) / gcd(p, c) ;
        
        if(cur < a[i]) 
        {
            ans++ ;
        }
    }
    
    cout << ans << endl ;
}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t ;
    for(ll i = 0 ; i < t ; i++ ) 
    {
        solve() ;
    }
}