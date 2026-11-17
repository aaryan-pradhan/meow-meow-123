
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
ll n, k , v ; 
vector < vector < ll > > g ;
vector < ll > depth ;
vector < ll > parent ;
vector < ll > subtree_size ;
vector < ll > num_child ; 
vector < pll > dtl ; 
// for every vertex store the distance to the furthurst and second furthest leaf of the vertex in the subtree
ll flag ;
void dfs(ll node, ll par , ll dep)
{
    parent[node] = par ;
    depth[node] = dep ;
    subtree_size[node] = 1 ; 
    num_child[node] = 0 ; 
    for (auto child : g[node])
    {
        if (child != par)
        {
            dfs(child,node,dep+1) ;
            subtree_size[node] += subtree_size[child] ;
            num_child[node]++ ; 
        }
    }
    
  
}
void solve() 
{
    cin >> n >> k >> v ; 
    g.resize(n+1) ;
    for (ll i = 0 ; i < n-1 ; i++)
    {
        ll u , v ; 
        cin >> u >> v ;
        g[u].push_back(v) ;
        g[v].push_back(u) ;
    }
    flag = false ; 
    depth.assign(n+1,0) ;
    parent.assign(n+1,0) ;
    subtree_size.assign(n+1,0) ;
    num_child.assign(n+1,0) ;
    dtl.assign(n+1,{0,0}) ;
    dfs(v,0,0) ; 
    




    
    
    
    
    
    
    
    
    g.clear() ; 

}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    cin >> t ;
    for (ll i = 1; i <= t; i++)
    {
        solve() ;
    } 
}
    
  