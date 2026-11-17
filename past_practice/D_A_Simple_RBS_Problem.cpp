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

ll n , k ; 
vector < vector < ll > > dp ;
ll rec(ll nl , ll kl)
{
    if( kl > nl ) 
    {
        return 0 ; 
    }
    if ( kl <= 0 || nl <= 0 ) 
    {
        return 0 ; 
    }
    if( kl == 0 && nl == 0 ) 
    {
        return 1 ; 
    }
    if(dp[nl][kl] != -1) 
    {
        return dp[nl][kl] ; 
    }
    
    ll ans = madd(rec(nl - 1, kl - 1), rec(nl - 1, kl)) ;
    
    return dp[nl][kl] = ans ;



}


// x1 + x2 + x3 ... + xk = n 
// x1 >= 1 , x2 >= 1 , x3 >= 1 , ... , xk >= 1 
// (x1 - 1) + (x2 - 1) + (x3 - 1) + ... + (xk - 1) = n - k 
// y1 + y2 + y3 + ... + yk = n - k 
// y1 >= 0 , y2 >= 0 , y3 >= 0 , ... , yk >= 0
void solve() 
{
    cin >> n >> k ; 
    dp.clear() ;
    dp.resize(n + 1, vector < ll > (k + 1, -1)) ;
    cout << rec(n, k) << endl ;
}

signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t; 
    cin >> t ; 
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ; 
    }
 

}
    
  