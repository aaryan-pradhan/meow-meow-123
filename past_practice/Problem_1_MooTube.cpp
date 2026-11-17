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
struct query
{
    ll k , v , idx ; 
    query()
    {
        k = v = idx = 0 ; 
    }
    query(ll a , ll b , ll c)
    {
        k = a ; 
        v = b ; 
        idx = c ; 
    }
    static bool cmp(query a , query b)
    {
        return a.k > b.k ; 
    }
};

struct edge
{
    ll w , u , v ;
    edge()
    {
        w = u = v = 0 ; 
    }
    edge(ll n1 , ll we , ll n2)
    {
        u = n1 ;
        v = n2 ;
        w = we ;

    }
    static bool cmp(edge a , edge b)
    {
        return a.w > b.w ; 
    }
};

struct UnionFind
{
    ll n ,  *par , *rank ; 
    UnionFind()
    {
        n = 0 ; 
        par = nullptr ;
        rank = nullptr ;

    }
    UnionFind( ll a)
    {
        n = a ; 
        par = new ll[n+1] ; 
        rank = new ll[n+1] ; 
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
            }
            else 
            {
                par[x] = y ; 
                rank[y] += rank[x] ; 
            }
        }


    }

}; 
deque < edge > g ; 
void solve() 
{
    ll n , r ; 
    cin >> n >> r ; 
    g.resize(n) ; 
    for(ll i = 1 ; i <=n-1 ; i++)
    {
        ll a , b , c ; 
        cin >> a >> b >> c ;
        g.push_back(edge(a , c , b)) ;
        g.push_back(edge(b , c , a)) ;

    }
    vector < query > q ; 
    for(ll i = 0 ; i < r ; i++)
    {
        ll k , v ; 
        cin >> k >> v ;
        q.push_back(query(k , v , i)) ;
    }

    sort(q.begin(), q.end(), query::cmp) ;
    sort(g.begin(), g.end(), edge::cmp) ;

    UnionFind uf(n) ;
    ll ans[r+10] ;
    for(auto x : q)
    {
        ll k = x.k ; 
        while(!g.empty() && g.front().w >= k)
        {
            edge e = g.front() ; 
            g.pop_front() ; 
            uf.merge(e.u , e.v) ;
        }
        ans[x.idx] = uf.rank[uf.find(x.v)] - 1 ;
        

    }
    for(ll i = 0 ; i < r ; i++)
    {
        cout << ans[i] << endl ;
    }

    g.clear() ; 


    
   






}
signed main() 
{

    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  