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


vector < vector < ll >> g; 
ll n ; 
vector < vector < ll >> par , dp ;
vector < ll > val , dep ; 
ll gcd (ll a , ll b)
{
    if(b == 0) return a;
    return gcd(b,a%b);
}
void dfs(ll u, ll p , ll d)
{
    dep[u] = d;
    par[u][0] = p;
    dp[u][0] = val[u];
    for(ll i = 1 ; i < 20 ; i++)
    {
        par[u][i] = par[par[u][i-1]][i-1];
        dp[u][i] = gcd(dp[u][i-1],dp[par[u][i-1]][i-1]);
    }
    for(auto v : g[u])
    {
        if(v != p) 
            dfs(v,u,d+1);
    }

}
ll path_agg(ll u, ll v)
{
    if(dep[u] < dep[v])
        swap(u,v);
    ll ans = 0;
    ll diff = dep[u] - dep[v];
    for(ll i = 19 ; i >= 0 ; i--)
    {
        if(diff & (1LL << i))
        {
            ans = gcd(ans,dp[u][i]);
            u = par[u][i];
        }
    }
    if(u == v)
    {
        ans = gcd(ans,val[u]);
        return ans;
    }
    for(ll i = 19 ; i >= 0 ; i--)
    {
        if(par[u][i] != par[v][i])
        {
            ans = gcd(ans,dp[u][i]);
            ans = gcd(ans,dp[v][i]);
            u = par[u][i];
            v = par[v][i];
        }
    }
    ans = gcd(ans , val[u]);
    ans = gcd(ans , val[v]);
    ans = gcd(ans , val[par[u][0]]);
    return ans;
}
void solve() 
{
    
    cin >> n;
    val.clear();
    val.resize(n+1);
    for(ll i = 1 ; i <= n ; i++)
    {
        cin >> val[i];
    }
    g.clear();
    g.resize(n+1);
    par.clear();
    par.resize(n+1, vector < ll > (20));
    dp.clear();
    dp.resize(n+1, vector < ll > (20));
    dep.clear();
    dep.resize(n+1);
    for(ll i = 0 ; i < n-1 ; i++)
    {
        ll u , v ; 
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0,0);
    ll q ;
    cin >> q;
    for(ll i = 0 ; i < q ; i++)
    {
        ll x , y ; 
        cin >> x >> y;
        cout << path_agg(x,y) << endl;
    }


    
    
}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t; 
    for(ll i = 0; i < t; i++)
    {
        solve();
    }
}