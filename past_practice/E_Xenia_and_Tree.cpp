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
vector < vector < ll > > depthstore ; 
vector < vector < ll > > up ; 
void dfs(ll node, ll par, ll depth)
{

    ent[node] = timer ;
    timer++ ; 
    for( auto ch : g[node])
    {
        if(ch != par)
        {
            dfs(ch,node,depth+1) ;
        }
    }
    ext[node] = timer ;
    
}
void solve() 
{
    ll n ; 
    cin >> n ;
    g.resize(n+1) ;
    ent.resize(n+1) ;
    ext.resize(n+1) ;
    depthstore.resize(n+1) ;
    up.resize(n+1) ;
    vector < ll > root ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        ll parent ; 
        cin >> parent ;
        g[parent].push_back(i) ;
    }







   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  