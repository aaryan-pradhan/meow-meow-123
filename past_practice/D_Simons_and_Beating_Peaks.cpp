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
vector < ll > parent ;
vector < ll > depth ;

void dfs(ll node, ll par, ll dep)
{
    depth[node] = dep;

    for (auto child : g[node])
    {
        if (child != par)
            dfs(child, node, dep + 1);
    }
}

void solve()
{
    ll n;
    cin >> n;

    vector<ll> a(n+1);

    parent.assign(n+1, -1);
    depth.assign(n+1, 0);
    g.assign(n+1, {});

    for (ll i = 1; i <= n; i++)
        cin >> a[i];

    stack<ll> s;

    for (ll i = 1; i <= n; i++)
    {
        ll last = -1;

        while (!s.empty() && a[s.top()] < a[i])
        {
            last = s.top();
            s.pop();
        }

        if (!s.empty())
            parent[i] = s.top();

        if (last != -1)
            parent[last] = i;

        s.push(i);
    }

    ll root = -1;

    for (ll i = 1; i <= n; i++)
    {
        if (parent[i] == -1)
            root = i;
        else
            g[parent[i]].push_back(i);
    }

    dfs(root, 0, 0);

    ll maxi = 0;

    for (ll i = 1; i <= n; i++)
        maxi = max(maxi, depth[i]);

    cout << n - maxi - 1 << endl;

    g.clear();
    parent.clear();
    depth.clear();

}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t;
    for (ll i = 1; i <= t; i++)
    {
        solve();
    }
}
    
  