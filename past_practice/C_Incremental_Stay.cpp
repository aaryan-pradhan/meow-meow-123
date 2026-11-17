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



void solve() 
{
    ll n ;
    cin >> n ;
    

    vector < ll > a( 2 * n ) ;
    for( ll i = 0 ; i < 2 * n ; i++ ) 
    {
        cin >> a[i] ;
    }
    
    vector < ll > w( n + 1, 0 ) ;
    for( ll i = 1 ; i < 2 * n ; i++ ) 
    {
        ll gap = a[i] - a[i - 1] ;
        ll m = min( i, 2 * n - i ) ;
        w[m] += gap ;
    }
    
    ll se = 0 ;
    ll so = 0 ;
    
    for( ll i = 1 ; i <= n ; i++ ) 
    {
        if( i % 2 == 0 ) 
        {
            se += w[i] ;
        } 
        else 
        {
            so += w[i] ;
        }
    }
    
    ll s = 0 ;
    vector < ll > res ; 
    for( ll k = 1 ; k <= n ; k++ ) 
    {
        if( k % 2 == 0 ) 
        {
            se -= w[k] ;
        } 
        else 
        {
            so -= w[k] ;
        }
        
        s += k * w[k] ;
        ll ans = s ;
        
        if( k % 2 == 0 ) 
        {
            ans += k * se + ( k - 1 ) * so ;
        } 
        else 
        {
            ans += ( k - 1 ) * se + k * so ;
        }
        
        res.push_back(ans) ;
    }
    
    for( auto x : res ) 
    {
        cout << x << " " ;
    }
    cout << endl ;
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