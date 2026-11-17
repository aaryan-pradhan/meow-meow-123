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
    ll n , m ; 
    cin >> n >> m ;
    vector < vector < ll> > a(n+2, vector < ll > (m+2)) ;
    for ( ll i = 1 ; i <= n ; i++ )
    {
        for ( ll j = 1 ; j <= m ; j++ )
        {
            cin >> a[i][j] ;
        }
    }
    vector < vector < ll > > dp1(n+2 , vector < ll > (m+2)) ;
    vector < vector < ll > > dp2(n+2 , vector < ll > (m+2)) ;
    vector < vector < ll > > dp3(n+2 , vector < ll > (m+2)) ;
    vector < vector < ll > > dp4(n+2 , vector < ll > (m+2)) ; 
    for(ll i = 1 ; i <= n ; i++ )
    {
        for ( ll j = 1 ; j <= m ; j++ )
        {
            ll t1 , t2 ; 
            ll ans = max(dp1[i-1][j] , dp1[i][j-1]) ;
            dp1[i][j] = ans + a[i][j] ;
        }
        
    }
    for (ll i = n; i >= 1 ; i-- )
    {
        for ( ll j = 1 ; j <= m ; j++ )
        {
            ll t1 , t2 ; 
            ll ans = max(dp2[i+1][j] , dp2[i][j-1]) ;
            dp2[i][j] = ans + a[i][j] ;
        }
        
    }
    for ( ll i = 1 ; i <= n ; i++ )
    {
        for ( ll j = m ; j >= 1 ; j-- )
        {
            ll t1 , t2 ; 
            ll ans = 0 ;
            ans = max(dp3[i-1][j] , dp3[i][j+1]) ;
            dp3[i][j] = ans + a[i][j] ;
        }
    }
    for ( ll i = n ; i >= 1 ; i-- )
    {
        for ( ll j = m ; j >= 1 ; j-- )
        {
            ll t1 , t2 ; 
            ll ans = 0 ;
            ans = max(dp4[i+1][j] , dp4[i][j+1]) ;
            dp4[i][j] = ans + a[i][j] ;
        }
    }


    
    ll ans = 0 ; 

    for(ll i = 2 ; i < n ; i++ )
    {
        for ( ll j = 2 ; j < m ; j++ )
        {
            ll op1 = dp1[i-1][j] + dp4[i+1][j] + dp2[i][j-1] + dp3[i][j+1];
            ll op2 = dp1[i][j-1] + dp4[i][j+1] + dp2[i+1][j] + dp3[i-1][j] ;
            ans = max(ans , max(op1 , op2)) ;


        }
    }

    cout << ans << endl ; 
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  