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
void solve() 
{
    ll n , a , b ; 
    cin >> n >> a >> b ;
    vector < ll > p ( n + 1 ) ; 
    map < ll , ll > pos ; 
    UnionFind uf(n+2) ;
    for(ll i = 1 ; i <= n ; i++)
    {
        cin >> p[i] ;
        pos[p[i]] = i ;
    }
    for(ll i = 1 ; i <= n ; i++)
    {
        ll x = pos[p[i]] ;
        ll y = pos[a - p[i]] ;
        ll z = pos[b - p[i]] ;
        if(y)
        {
            uf.merge(x,y) ;
        }
        else
        {
            uf.merge(x,n+1) ;
        }

        if(z)
        {
            uf.merge(x,z) ;
        }
        else 
        {
            uf.merge(x,n+2) ;
        }

 
    }
    if(uf.find(n+1) == uf.find(n+2))
    {
        pn ; 
        return ;
    }
    else 
    {
        py ; 
        for(ll i = 1 ; i <= n ; i++)
        {
            if(uf.find(i) == uf.find(n+2))
            {
                cout << 0 << " " ;
            }
            else 
            {
                cout << 1 << " " ;
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
    
  