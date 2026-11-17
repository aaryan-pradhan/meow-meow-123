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

ll dp[10][2000005] ;
ll rec(ll d , ll m)
{
    if(m == 0 )
    {
        dp[d][m] = 1;
        return dp[d][m];
    }
    if(dp[d][m] != -1)
        return dp[d][m];
    
    ll ans = 0 ; 

    if(d == 9)
    {
        ans = madd(ans,rec(0,m-1));
        ans = madd(ans,rec(1,m-1));

    }
    else
    {
        ans = madd(ans,rec(d+1,m-1));
    }
    return dp[d][m] = ans ;

}

void solve() 
{
    ll n , m ; 
    cin >> n >> m ;


    ll res = 0 ; 
    while(n >  0 )
    {
        ll ld = n%10 ;
        n /= 10 ;
        res = madd(res,rec(ld,m));
    }
    cout << mcorr(res) << endl;





    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    memset(dp,-1,sizeof(dp)) ;

    

 
    ll t; 
    cin >> t;
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ;
    }
        
}
    
  