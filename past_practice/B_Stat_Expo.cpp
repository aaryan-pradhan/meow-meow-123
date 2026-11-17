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
ll rec ( ll level , ll diff )
{
    if ( diff < 0 )
    {
        return 0 ; 
    }
    if ( level == 12 )
    {
        return diff == 0 ; 
    }
    ll ans = 0 ;
    ll put_a = rec(level + 1 , diff + 1) ;
    ll put_b = rec(level + 1 , diff - 2) ;
    ans = put_a + put_b ;
    return ans ;
}
ll gcd( ll a , ll b )
{
    if ( b == 0 )
    {
        return a ;
    }
    return gcd(b , a%b) ;
}
void solve() 
{
    ll ans = rec(0 , 0) ;
    ll f[13] ; 
    f[0] = 1 ;
    for ( ll i = 1 ; i <= 12 ; i++ )
    {
        f[i] = f[i-1] * i ;
    }
    ll num = ans * f[8] * f[4] ;
    ll den = f[12] ;
    ll g = gcd(num , den) ;
    num /= g ;
    den /= g ;
    cout << num + den << endl ;

    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  