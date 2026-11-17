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
ll madd(ll a , ll b)
{
    return (a%MOD + b%MOD) %MOD ; 
}
ll msub(ll a , ll b)
{
    return (a%MOD - b%MOD) %MOD ; 
}
ll mmul(ll a , ll b)
{
    return (a%MOD * b%MOD) %MOD ; 
}
ll mpow(ll a , ll b)
{
    ll res = 1 ; 
    while(b)
    {
        if(b&1) res = mmul(res,a) ;
        a = mmul(a,a) ;
        b >>= 1 ;
    }
    return res ;
}
ll mdiv(ll a , ll b)
{
    return mmul(a,mpow(b,MOD-2)) ; 
}
ll mcorr(ll a)
{
    return (a%MOD + MOD) %MOD ; 
}
ll n ; 
ll m ; 
ll a[100100] ; 
ll dp[100100] ; 
ll s1[100100] ; 
ll s2[100100] ; 
ll rec( ll i)
{
    // this returns the prob s1 > s2 
    if(i >= n)
    {
        return 0 ; 
    }
    if(dp[i]!=-1)
    {
        return dp[i] ; 
    }
    ll w , e , ans ;
    ll a = s1[i];
    ll b = s2[i] ; 
    if(!a && !b)
    {
        w = mdiv(m-1,2*m) ; 
        e = mdiv(1,m) ; 
    }
    else if(b && !a)
    {
        w = mdiv(m-b, m) ; 
        e = mdiv(1,m) ; 
    }
    else if(a && !b)
    {
        w = mdiv(a-1, m) ; 
        e = mdiv(1,m) ; 
    }
    else 
    {
        if(a>b)
        {
            w = 1 ;
            e = 0 ; 
        }
        else if(a<b)
        {
            w = e= 0 ;  
        }
        else 
        {
            w = 0 ; 
            e = 1 ; 
        }
        
    }
    ans = mcorr(madd(w , mmul(e,rec(i+1)))) ; 
    return dp[i] = ans ; 
}

void solve() 
{
    cin >> n >> m ; 
    for(ll i = 0 ; i < n ; i++) cin >> s1[i] ; 
    for(ll i = 0 ; i < n ; i++) cin >> s2[i] ; 

    memset(dp,-1,sizeof(dp)) ; 
    cout << rec(0) << endl ; 

    
    


    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  