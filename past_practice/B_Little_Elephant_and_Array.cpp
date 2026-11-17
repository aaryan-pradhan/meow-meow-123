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
ll n , m , bs ; 
vector < ll > a; 
vector < ll > freq ;
ll ans ; 
struct Query
{
    ll l , r , id ; 
    bool operator < ( const Query & other) const 
    {
        ll bl = l / bs ; 
        ll bl_other = other.l / bs ;
        if(bl != bl_other)
        {
            return bl < bl_other ;
        }
        else 
        {
            return r < other.r ;
        }
    }
};
void solve() 
{
   
    cin >> n >> m ; 
    bs = sqrt(n) ;

    a.resize(n +1 ) ; 
    freq.resize(n+1) ;
    for (ll i = 1 ; i <= n ; i++)
    {
        
    }

    vector < Query > queries ( m ) ;
    for (ll i = 0 ; i < m ; i++)
    {
        cin >> queries[i].l >> queries[i].r ;
        queries[i].id = i ; 
    }
    sort(queries.begin(), queries.end()) ;
    




   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  