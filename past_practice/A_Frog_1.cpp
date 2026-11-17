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
    vector < ll > a ( n + 1 , 0 ) ;
    vector < ll > dp ( n + 1 , -1 ) ; 
    for ( ll i = 1 ; i <= n ; i++ )
    {
        cin >> a[i] ; 
    }

    for ( ll i = n ; i >= 0 ; i-- )
    {
        if ( i == n)
        {
            dp[i] = 0 ;
        }
        else if ( dp[i] != -1 )
        {
            continue ; 
        }
        else 
        {
            ll ans = INF ; 
            for ( ll j = i + 1 ; j <= min ( n , i + 2 ) ; j++ )
            {
                ans = min ( ans , dp[j] + abs ( a[j] - a[i] ) ) ;
            }
            dp[i] = ans ;
        }

    }
    cout << dp[1] << endl ;
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  