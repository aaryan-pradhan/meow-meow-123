
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
vector < vector < ll > > g ;
vector < ll > vis ;
ll noc = 0 ;
void dfs(ll node)
{
    vis[node] = noc ; 
    for(auto child : g[node])
    {
        if(!vis[child])
        {
            dfs(child) ; 
        }
    }

}
void solve() 
{
    
    ll n , m ; 
    cin >> n >> m ;
    
    g.resize(n+1) ;
    vis.assign(n+1, 0) ;
    for(ll i = 0 ; i < m ; i++)
    {
        ll u , v ; 
        cin >> u >> v ; 
        g[u].push_back(v) ;
        g[v].push_back(u) ;
    }
    noc = 0 ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        if(!vis[i])
        {
            noc++ ;
            dfs(i) ;
        }
    }
    ll res = n - noc ; 
    ll ans = 1LL << res ;
    cout << ans << endl ;









}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  