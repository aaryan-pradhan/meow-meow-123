// orz
#include "bits/stdc++.h"
#define ll long long 
#define ld long double 
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
bool check(ld mid , vector < ll > &a , ll n)
{
    vector < ld > b(n) ;
    for(ll i = 0 ; i < n ; i++) b[i] = a[i] - mid ;
    vector < vector < ld > > dp(2  , vector < ld > (2 , 0.0 )) ; 
    for( ll i = n ; i >= 0 ; i--)
    {
        for(ll prev = 0 ; prev < 2 ; prev++)
        {
            if( i == n)
            {
                dp[i&1][prev] = 0.0 ;
                continue ;
            }
            ld ans = -1e18 ;
            if(prev == 0 )
            {
                ans = max(ans , b[i] + dp[(i + 1)&1][1]) ;
            }
            else 
            {
                ans = max(ans , dp[(i + 1)&1][0]) ;
                ans = max(ans , b[i] + dp[(i + 1)&1][1]) ;
            }
            dp[i&1][prev] = ans ;
        }  
        
    }
    ld res = max(dp[0][0] , dp[0][1]) ;
    return res < 0.0 ;
}
bool check2(ll mid , vector < ll > &a , ll n)
{
    vector < ll > b(n) ;
    for(ll i = 0 ; i < n ; i++) b[i] = a[i] - mid >= 0 ? 1 : -1 ;
    vector < vector < ll > > dp(2  , vector < ll > (2 , 0 )) ;
    for( ll i = n ; i >= 0 ; i--)
    {
        for(ll prev = 0 ; prev < 2 ; prev++)
        {
            if( i == n)
            {
                dp[i&1][prev] = 0 ;
                continue ;
            }
            ll ans = -1e18 ;
            if(prev == 0 )
            {
                ans = max(ans , b[i] + dp[(i + 1)&1][1]) ;
            }
            else 
            {
                ans = max(ans , dp[(i + 1)&1][0]) ;
                ans = max(ans , b[i] + dp[(i + 1)&1][1]) ;
            }
            dp[i&1][prev] = ans ;
        }  
        
    }
    ll res = max(dp[0][0] , dp[0][1]) ;
    return res <= 0 ;
}
   
void solve() 
{
    
   ll n ; 
   cin >> n ; 
   vector < ll > a(n) ; 
   for(ll i = 0 ; i < n ; i++) cin >> a[i] ;
   ld l = 0 , r = 1e9 ;
   for( ll iter = 0 ; iter < 50 ; iter++)
   {
        ld mid = (l + r) / 2.0 ;
        if(check(mid , a , n)) r = mid ;
        else l = mid ;

   }
   ld ans = (l + r) / 2.0 ;
   cout << fixed << setprecision(3) << ans << endl ;
   ll lo = 0 , hi = 1e9 + 100 , ans2 = -1 ; 
   while( lo <= hi)
   {
        ll mid = lo + (hi - lo) / 2 ;
        if(check2(mid , a , n))
        {
            ans2 = mid ;
            hi = mid - 1 ;
        }
        else 
        {
            lo = mid + 1 ;
        }
   }
   cout << ans2 - 1 << endl ;










}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  