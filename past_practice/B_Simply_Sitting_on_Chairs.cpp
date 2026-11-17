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
    
    
    vector < ll > p(n + 1) ;
    for(ll i = 1 ; i <= n ; i++ ) 
    {
        cin >> p[i] ;
    }
    

    vector < ll > d(n + 67, 0) ;
    
    for(ll i = 1 ; i <= n ; i++ ) 
    {
        if(p[i] <= i) 
        {
            d[i + 1]++ ;
            d[n + 2]-- ;
        } 
        else 
        {
            d[i + 1]++ ;
            d[p[i] + 1]-- ;
        }
    }
    
    ll ans = 0 ;
    ll cur = 0 ;

    for(ll i = 1 ; i <= n + 1 ; i++ ) 
    {
        cur += d[i] ;
        ans = max(ans, cur) ;
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