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
#define py cout << "Yes" << endl
#define pn cout << "No" << endl
#define pll pair<ll,ll>

using namespace std;



void solve() 
{
    ll n;
    cin >> n;
    
    vector <string> s(n);
    for(ll i = 0; i < n; i++) 
    {
        cin >> s[i];
    }
    
    for(ll i = 0; i < n; i++) 
    {
        if(s[i][i] == '0') 
        {
            pn;
            return;
        }
        for(ll j = i + 1; j < n; j++) 
        {
            if(s[i][j] == '1' && s[j][i] == '1') 
            {
                pn;
                return;
            }
        }
    }
    
    vector <pll> edges;
    
    for(ll i = 0; i < n; i++) 
    {
        for(ll j = 0; j < n; j++) 
        {
            if(i != j && s[i][j] == '1') 
            {
                bool d = true;
                for(ll k = 0; k < n; k++) 
                {
                    if(k != i && k != j && s[i][k] == '1' && s[k][j] == '1') 
                    {
                        d = false;
                        break;
                    }
                }
                if(d) 
                {
                    edges.push_back({i + 1, j + 1});
                }
            }
        }
    }
    
    if(edges.size() != n - 1) 
    {
        pn;
        return;
    }
    

    vector <vector < ll >> g(n+1);
    vector <vector < ll >> dg(n+1) ; 
    vector <bool> vis(n + 1, false);
    
    for(auto e : edges) 
    {
        g[e.fr].push_back(e.sc);
        g[e.sc].push_back(e.fr);
        dg[e.fr].push_back(e.sc) ;
    }
    
    queue<ll> q;
    q.push(1);
    vis[1] = true;
    ll comp_size = 0;
    
    while(!q.empty()) 
    {
        ll u = q.front();
        q.pop();
        comp_size++;
        
        for(ll v : g[u]) 
        {
            if(!vis[v]) 
            {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    
    if(comp_size != n) 
    {
        pn;
        return;
    }
    

    for(ll i = 1; i <= n; i++) 
    {
        vis.assign(n + 1, false);
        
        queue<ll> dirq ; 
        dirq.push(i);
        vis[i] = true;
        
        while(!dirq.empty()) 
        {
            ll u = dirq.front();
            dirq.pop();

            for(ll v : dg[u]) 
            {
                if(!vis[v]) 
                {
                    vis[v] = true;
                    dirq.push(v);
                }
            }
        }
        
        for(ll j = 1; j <= n; j++) 
        {
            if(vis[j] && s[i - 1][j - 1] == '0') 
            {
                pn;
                return;
            }
            if(!vis[j] && s[i - 1][j - 1] == '1') 
            {
                pn;
                return;
            }
        }
    }
    
    py;
    for(auto e : edges) 
    {
        cout << e.fr << " " << e.sc << endl;
    }
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