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
ll timer ; 
vector < ll > ent ; 
vector < ll > ext ; 
vector < vector < ll > > store ; 
vector < vector < ll > > up ; 
vector < ll > depth ;
ll m , n ; 
void dfs(ll node, ll par, ll dep)
{

    ent[node] = timer ;
    
    depth[node] = dep ;
    store[dep].push_back(timer) ; 
    
    timer++ ; 
    
    up[node][0] = par ; // this is 2 raise to 0 
    for (ll i = 1 ; i < 20 ; i++)
    {
        ll h = up[node][i-1] ; // this is 2 raise to i - 1 parent
        up[node][i] = up[h][i-1] ;
    }
    // we have explored upper part 
    for( auto ch : g[node])
    {
        if(ch != par)
        {
            dfs(ch,node,dep+1) ;
        }
    }
    // we have to explore lower part
    ext[node] = timer ;
    
}


void solve() 
{

    cin >> n ; 
    g.resize(n+1) ;
    ent.resize(n+1) ;
    ext.resize(n+1) ;
    store.resize(n+1) ;
    up.assign(n+1, vector < ll > (20,0)) ;
    depth.resize(n+1) ;
    vector < ll > root ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        ll parent ; 
        cin >> parent ;
        g[parent].push_back(i) ;
    }
    timer = 0 ; 
    dfs(0,0,0) ;


    cin >> m ; 

    while(m--)
    {
        ll v , p ; 
        cin >> v >> p ;
        ll now = v ; 
        for (ll i = 19 ; i >= 0 ; i--)
        {
            if((p>>i) & 1)
            {
                now = up[now][i] ;
            }
            
        }
        if(now == 0)
        {
            cout << 0 << " " ;
        }
        else 
        {
            ll d = depth[v] ;
            ll l = ent[now] ;
            ll r = ext[now] ;
            auto it1 = lower_bound(store[d].begin(), store[d].end(), l) ;
            auto it2 = upper_bound(store[d].begin(), store[d].end(), r) ;
            cout << it2 - it1 - 1<< " " ;
        }
        

    }
    cout << endl ;
    





   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  