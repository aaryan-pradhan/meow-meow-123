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
ll h , r , g ; 


ll madd(ll a, ll b) 
{
    return ((a%MOD) +(b%MOD))%MOD ; 
}
ll msub(ll a, ll b) 
{
    return ((a%MOD) - (b%MOD))%MOD ; 
}
ll mmul(ll a, ll b) 
{
    return ((a%MOD) *(b%MOD))%MOD ; 
}
ll mpow(ll a, ll b) 
{
    ll res = 1; 
    while (b > 0) 
    {
        if (b & 1) 
        {
            res = mmul(res, a);
        }
        a = mmul(a, a);
        b >>= 1;
    }
    return res;
}
ll minv(ll a) 
{
    return mpow(a, MOD - 2);
}
ll mdiv(ll a, ll b)
{
    return mmul(a, minv(b));
}
ll mcorr(ll a) 
{
    return (a%MOD + MOD) % MOD;
}

void solve() 
{
 
    cin >> r >> g ;
    ll lo = 0 , hi = 4 * 1e5 + 100 ; 
    ll ans = -1 ; 
    while( lo <= hi ) 
    {
        ll mid = lo + ( hi - lo ) / 2 ;
        ll sum = ( mid * ( mid + 1 ) ) / 2 ;
        if( sum <= r + g ) 
        {
            ans = mid ;
            lo = mid + 1 ; 
        }
        else
        {
            hi = mid - 1 ; 
        }
    }
    h = ans ; 
 
    
    vector < vector < ll > > dp ; 
    dp.resize( 2 ) ; 
    dp[0].resize( r + 1 , 0 ) ; 
    dp[1].resize( r + 1 , 0 ) ; 
 
    ll nxt = ( h + 1 ) % 2 ; 
    for ( ll rleft = 0 ; rleft <= r ; rleft++ ) 
    {
        ll u = h * ( h + 1 ) / 2 ; 
        ll ru = r - rleft ; 
        ll gu = u - ru ; 
        ll gleft = g - gu ; 
        
        if ( rleft >= 0 && gleft >= 0 ) 
        {
            dp[nxt][rleft] = 1 ; 
        }
        else 
        {
            dp[nxt][rleft] = 0 ; 
        }
    }
 

    for ( ll i = h ; i >= 1 ; i-- ) 
    {
        ll cur = i % 2 ; 
        nxt = ( i + 1 ) % 2 ; 
        
        for ( ll rleft = 0 ; rleft <= r ; rleft++ ) 
        {
            dp[cur][rleft] = 0 ; 
            
            ll u = i * ( i - 1 ) / 2 ; 
            ll ru = r - rleft ; 
            ll gu = u - ru ; 
            ll gleft = g - gu ; 
            
            if ( rleft < 0 || gleft < 0 ) 
            {
                continue ; 
            }
            
            ll opt1 = 0 ; 
            if ( rleft >= i ) 
            {
                opt1 = dp[nxt][rleft - i] ;
            }
            ll opt2 = dp[nxt][rleft] ;     
            
            dp[cur][rleft] = madd( opt1 , opt2 ) ; 
        }
    }
 
    cout << mcorr( dp[1 % 2][r] ) << endl ; 
 
}

signed main() 
{
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}