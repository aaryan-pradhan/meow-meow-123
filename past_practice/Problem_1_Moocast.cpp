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

vector < pll > pts ; 
struct UnionFind
{
    ll n , setsz , *par , *rank ; 
    UnionFind()
    {
        n = setsz = 0 ; 
        par = nullptr ;
        rank = nullptr ;

    }
    UnionFind( ll a)
    {
        n = setsz = a ; 
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
            setsz-- ; 
        }


    }

    

}; 
bool check(ll x)
{
    ll n = pts.size() ;

    UnionFind uf(n) ;
    for(ll i = 0 ; i < n ; i++)
    {
        for(ll j = i+1 ; j < n ; j++)
        {
            ll dist = (pts[i].fr - pts[j].fr) * (pts[i].fr - pts[j].fr) + (pts[i].sc - pts[j].sc) * (pts[i].sc - pts[j].sc) ;
            if(dist <= x)
            {
                uf.merge(i+1,j+1) ;
            }
        }
    }
    return uf.setsz == 1 ;


}
void solve() 
{
    ll n ; 
    cin >> n ; 

    if(n == 1)
    {
        cout << 0 << endl ;
        return ;
    }

    pts.resize(n) ;

    for(ll i = 0 ; i < n ; i++)
    {
        cin >> pts[i].fr >> pts[i].sc ;
    }
    ll maxi = 0 ; 
    ll mini = INF ;
    for(ll i = 0 ; i < n ; i++)
    {
        for(ll j = i+1 ; j < n ; j++)
        {
            ll dist = (pts[i].fr - pts[j].fr) * (pts[i].fr - pts[j].fr) + (pts[i].sc - pts[j].sc) * (pts[i].sc - pts[j].sc) ;
            maxi = max(maxi,dist) ;
            mini = min(mini,dist) ;
        }
    }
    ll lo = mini , hi = maxi ;
    ll ans = maxi ; 
    while(lo <= hi)
    {
        ll mid = lo + (hi - lo) / 2 ;
        if(check(mid))
        {
            ans = mid ; 
            hi = mid - 1 ;
        }
        else 
        {
            lo = mid + 1 ;
        }
    }
    cout << ans << endl ;



    
   






}
signed main() 
{
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  