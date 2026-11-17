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

vector < vector <ll> > graph; 
vector <ll> col; 
ll c0, c1;
bool bp; 

void dfs(ll u, ll c) 
{
    col[u] = c;
    if(c == 0) 
    {
        c0++;
    }
    else 
    {
        c1++;
    }
    
    for(ll v : graph[u])
    {
        if(col[v] == -1)
        {
            dfs(v, 1 - c);
        }
        else if(col[v] == col[u])
        {
            bp = false;
        }
    }
}

void solve() 
{
    ll n, m;
    cin >> n >> m;
    
    graph.assign(n + 1, vector<ll>());
    col.assign(n + 1, -1);
    
    for(ll i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    ll ans = 0;
    
    for(ll i = 1; i <= n; i++)
    {
        if(col[i] == -1)
        {
    
            c0 = 0; 
            c1 = 0;
            bp = true; 
    
            dfs(i, 0);
            
            if(bp)
            {
                ans += max(c0, c1);
            }
        }
    }
    
    cout << ans << endl;
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