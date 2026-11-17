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
#define ld long double 

using namespace std;
ll max(ll a , ll b)
{
    if ( a > b)
    {
        return a ; 
    }
    else
    {
        return b ; 
    }
}
ll min(ll a , ll b)
{
    if ( a > b)
    {
        return b ; 
    }
    else
    {
        return a ; 
    }
}


void solve() 
{
    ll n ; 
    cin >> n ; 
    ll a[n+1] ;
    for(ll i = 1 ; i <= n ; i++ )   cin >> a[i] ; 
    ld dp[n+100] ;  
    for ( ll i = n ; i >= 1 ; i--)
    {
        if ( i == n )
        {
            dp[i] = ( a[n] + 1 ) / 2.0  ;
        }
        else 
        {
            ll res = dp[i+1] ; 
            ll t = max(a[i] - res,0); 
            ld ans ; 
            if (t == 0 )
            {
                ans = dp[i+1] ; 
            }
            else 
            {
                ans = dp[i+1] * res  ; 
                ans += t * ( a[i] + res + 1) / 2.0  ; 
                ans /= (a[i]*1.0) ; 
            }
            dp[i] = ans ; 
        }


    }
    cout << fixed << setprecision(10) << dp[1] << endl ; 
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    t = 1 ;
    while(t--)
    {
        solve() ; 
    }
}
    
  