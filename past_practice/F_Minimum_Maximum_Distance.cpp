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
vector < vector < ll > > g ;

vector < ll > depth ; 
ll n , k ; 
vector < ll > r ; 

void dfs( ll node , ll par, ll dep)
{
    depth[node] = dep ;

    for(auto child : g[node])
    {
        if(child != par)
        {
            dfs(child, node, dep + 1) ;
        }
    }
}
void solve() 
{
    ll n , k ; 
    cin >> n >> k ; 
    ll m = n-1 ; 

    g.assign(n+1,vector < ll >()) ;
    depth.assign(n+1,0) ;
    r.assign(k,0) ;

    for(ll i = 0 ; i < k ; i++)
    {
        cin >> r[i]; 
    }
    for(ll i = 0 ; i < m ; i++)
    {
        ll u , v ; 
        cin >> u >> v ; 
        g[u].push_back(v) ;
        g[v].push_back(u) ;
    }
    ll root = r[0] ;
    dfs(root,0,0) ;
    for(auto x : r)
    {
        if(depth[x] > depth[root])
        {
            root = x ;
        }
    }
    depth.assign(n+1,0) ;
    dfs(root,0,0) ;
    for(auto x : r)
    {
        if(depth[x] > depth[root])
        {
            root = x ;
        }
    }
    cout << (depth[root]+1)/2 << endl ;
    



    g.clear() ; 
    


   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ;
    cin >> t ;
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ;
    }
}
    
  