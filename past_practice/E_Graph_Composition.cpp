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

struct UnionFind
{
    ll n , setsz , *par , *rank , maxsz ; 
    UnionFind()
    {
        n = setsz = 0 ; 
        par = nullptr ;
        rank = nullptr ;
        maxsz = 0 ; 
    }
    UnionFind( ll a)
    {
        n = setsz = a ; 
        par = new ll[n+1] ; 
        rank = new ll[n+1] ; 
        maxsz = 1 ; 
        for( ll i = 1 ; i <= n ; i++)
        {
            par[i] = i ; 
            rank[i] = 1 ; 
        }
    }
    ll find( ll x )
    {
        if( x != par[x])
        {
            return par[x] = find(par[x]) ;
        }
        else 
        {
            return x ; 
        }
    }
    void merge( ll a , ll b)
    {
        ll x = find(a) ; 
        ll y = find(b) ; 
        if (x == y) return ; 
        if( x != y )
        {
            if(rank[x] >= rank[y])
            {
                par[y] = x ; 
                rank[x] += rank[y] ;
                maxsz = max(maxsz , rank[x]) ; 
            }
            else 
            {
                par[x] = y ; 
                rank[y] += rank[x] ; 
                maxsz = max(maxsz , rank[y]) ; 

            }
            setsz-- ; 
        }


    }
    ll maxu()
    {
        return maxsz ; 
    }


}; 
ll n , mf , mg ; 
void solve() 
{
    cin >> n >> mf >> mg ;

    UnionFind f(n) ;
    vector < pll > edges ;

    for (ll i = 0 ; i < mf ; i++)
    {
        ll u , v ; 
        cin >> u >> v ;
        edges.push_back({u,v}) ;
    }
    UnionFind g(n) ;
    for (ll i = 0 ; i < mg ; i++)
    {
        ll u , v ; 
        cin >> u >> v ;
        g.merge(u,v) ;
    }
    ll ans = 0 ; 
    for (auto edge : edges)
    {
        ll u = edge.fr ; 
        ll v = edge.sc ; 
        if( g.find(u) != g.find(v))
        {
            ans++ ;    
        }
        else
        {
            f.merge(u,v) ;
        }
    }
    cout << ans + (f.setsz - g.setsz) << endl ;

    
    
   






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
    
  