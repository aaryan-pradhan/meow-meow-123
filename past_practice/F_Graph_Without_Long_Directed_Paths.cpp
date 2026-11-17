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
vector < pll > edges ; 
vector < ll > vis ; 
ll flag = 0 ; 
ll n , m ; 
void dfs( ll node , ll col )
{
    vis[node] = col ; 
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
                return ;  
            }
        }
    }

}
void solve() 
{
    
    cin >> n >> m ; 
    g.resize(n+1) ;
    vis.assign(n+1,0) ;
    for(ll i = 0 ; i < m ; i++)
    {
        ll u , v ; 
        cin >> u >> v ; 
        g[u].push_back(v) ;
        g[v].push_back(u) ;
        edges.push_back(mp(u,v)) ;
    }
    dfs(1, 1 ) ; 
    if(flag)
    {
        pn ; 
        return ;
    }
    else 
    {
        py ; 
        for(auto edge : edges)
        {
            if(vis[edge.fr] == 1 && vis[edge.sc] == 2)
            {
                cout << 1 ;
            }
            else if(vis[edge.fr] == 2 && vis[edge.sc] == 1)
            {
                cout << 0 ;
            }
        }
        cout << endl ;
    }










}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  