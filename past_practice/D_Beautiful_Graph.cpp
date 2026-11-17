#include "bits/stdc++.h"
#define ll long long 
#define endl "\n"
#define fr first
#define sc second
#define MOD 998244353
 
#define INF 1e18
#define mp make_pair
#define PI acos(-1) 
#define py cout << "YES" << endl
#define pn cout << 0 << endl
#define pll pair<ll,ll>
 
using namespace std;
vector < vector < ll > > g ;
vector < pll > edges ; 
vector < ll > vis ; 
ll flag ; 
ll n , m ; 
ll noc ; 
vector<ll> pow2(300005);
ll col1 , col2 ; 
 
void dfs( ll node , ll col)
{
    vis[node] = col ; 
    if(col == 1)
    {
        col1++ ;
    }
    else
    {
        col2++ ;
    }
    for(auto child : g[node])
    {
        if(!vis[child])
        {
            dfs(child,3-col) ;
        }
        else if(vis[child])
        {
            if(vis[node] == vis[child])
            {
                flag = 1 ; 
            }
        }
    }
 
}
 
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
    flag  = 0 ;
    
    cin >> n >> m ; 
    
    g.assign(n+1,vector < ll >()) ;
    vis.assign(n+1,0) ;
    for(ll i = 0 ; i < m ; i++)
    {
        ll u , v ; 
        cin >> u >> v ; 
        g[u].push_back(v) ;
        g[v].push_back(u) ;
    }
    ll res = 0 ; 
    ll ans = 1 ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        if(!vis[i])
        {
            
            col1 = 0 ; 
            col2 = 0 ; 
            dfs(i,1) ;
 
            
            if(flag)
            {
                pn ; 
                return ; 
            }
            else
            {
                res = madd(pow2[col1] , pow2[col2]) ;
                
                ans = mmul ( ans , res) ; 
            }
        }
    } 
    cout << ans << endl ;
 
 
 
    g.clear() ; 
    
    
 
 
 
    
    
      
    
 
 
 
 
 
 
 
 
 
 
 
 
}
signed main() 
{
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    pow2[0] = 1;
    for(ll i = 1 ; i < 300005 ; i++)
    {
        pow2[i] = mmul(pow2[i-1] , 2) ;
    }
    ll t; 
    cin >> t ;
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ; 
    }
}
