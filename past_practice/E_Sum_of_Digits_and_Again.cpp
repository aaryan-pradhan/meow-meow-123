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

vector < vector < ll >> g ; 
ll n , q ; 
ll parent[300005][20] ;
ll depth[300005] ;


void dfs(ll node , ll par , ll dep)
{
    parent[node][0] = par ;
    depth[node] = dep ; 
    for(ll i = 1 ; i < 20 ; i++)
    {
        parent[node][i] = parent[parent[node][i-1]][i-1] ;
    }
    for(auto child : g[node])
    {
        if(child != par)
        {
            dfs(child, node, dep + 1) ;
        }
    }

}
ll lca(ll u , ll v)
{
    if(depth[u] < depth[v])
    {
        swap(u,v) ;
    }
    ll diff = depth[u] - depth[v] ;
    for(ll i = 0 ; i < 20 ; i++)
    {
        if((diff) & (1 << i))
        {
            u = parent[u][i] ;
        }
    }
    if(u == v)
    {
        return u ;
    }
    for(ll i = 19 ; i >= 0 ; i--)
    {
        if(parent[u][i] != parent[v][i])
        {
            u = parent[u][i] ;
            v = parent[v][i] ;
        }
    }
    return parent[u][0] ;
}
void solve() 
{
    cin >> n ; 
    g.assign(n+1,vector < ll >()) ;
    for(ll i = 0 ; i <= n ; i++)
    {
        depth[i] = 0 ;
        for(ll j = 0 ; j < 20 ; j++)
        {
            parent[i][j] = 0 ;
        }
    }

    for(ll i = 0 ; i < n-1 ; i++)
    {
        ll u , v ; 
        cin >> u >> v ; 
        g[u].push_back(v) ;
        g[v].push_back(u) ;
    }
    
    cin >> q ; 
    

    dfs(1,0,0) ;



    while(q--)
    {
        ll x , y , z ; 
        cin >> x >> y >> z ; 
        ll l1 = lca(x,y) ;
        ll l2 = lca(y,z) ;
        ll l3 = lca(z,x) ;
        ll res = l1 ^ l2 ^ l3 ; 

  
        cout << res << endl ;
    }
    g.clear()  ; 





    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t; 
    
    while(t--)
    {
        solve() ; 
    }
}
    
  