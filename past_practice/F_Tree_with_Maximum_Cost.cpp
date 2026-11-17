// orz
#include <bits/stdc++.h>

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
ll n ; 
vector < ll > w ; 
vector < vector < ll >> g ; 
vector < ll > indp ; 
vector < ll > outdp ;
vector < ll > subtree_size ;

void indfs(ll node, ll par)
{
    indp[node] = 0;
    subtree_size[node] = w[node] ;
    for (auto child : g[node])
    {
        if (child != par)
        {
            indfs(child,node) ;
            subtree_size[node] += subtree_size[child] ;
            indp[node] += indp[child] + subtree_size[child] ;
        }
    }
    
}
void outdfs(ll node, ll par)
{
    if(node==1)
    {
        outdp[node] = 0 ;
    }
    else 
    {
        outdp[node] = outdp[par] + indp[par] - (indp[node] + subtree_size[node]) + (subtree_size[1] - subtree_size[node]) ;
    }
    for (auto child : g[node])
    {
        if (child != par)
        {
            outdfs(child,node) ;
        }
    }
    
}
void solve() 
{
    cin >> n ; 
    w.resize(n+1) ;
    g.resize(n+1) ;
    for (ll i = 1 ; i <= n ; i++)
    {
        cin >> w[i] ;
    }
    for(ll i = 1 ; i < n ; i++)
    {
        ll u , v ; 
        cin >> u >> v ;
        g[u].push_back(v) ;
        g[v].push_back(u) ;
    }
    indp.resize(n+1) ; 
    outdp.resize(n+1) ;
    subtree_size.resize(n+1) ;
    indfs(1,0) ;
    outdfs(1,0) ;
    ll mini = INF ;
    ll maxi = -INF ; 
    for (ll i = 1 ; i <= n ; i++)
    {
        maxi = max(maxi,indp[i] + outdp[i]) ;
        mini = min(mini,indp[i] + outdp[i]) ; 
    }
    cout << mini << " " << maxi << endl ;

    g.clear() ;
    w.clear() ;
    indp.clear() ;
    outdp.clear() ;
    subtree_size.clear() ;



    

    






   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    cin >> t;  
    while(t--)
    {
        solve() ; 
    }
    
}
    
  