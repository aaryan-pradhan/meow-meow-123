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
#define ld long double 
using namespace std;

void solve() 
{
    ll n ; 
    cin >> n ; 
    vector < ll > a(n,0) ; 

    for(ll i = 0 ; i < n ; i++)
    {
        cin >> a[i] ;
    }
    vector < ll > d(5050, 0); 
    ll maxi = 0 ; 
    for( ll i = 0 ; i < n ; i++)
    {
        for ( ll j = i + 1 ; j < n ; j++)
        {
            d[abs(a[i]-a[j])]++ ; 
            maxi = max(abs(a[i]-a[j]), maxi) ; 
        }
    }
    vector < ld > p(maxi + 1 , 0) ;  
    ld de = n * 1.0 * ( n - 1.0 ) / 2.0 ; 
    for ( ll k = 0 ; k < maxi + 1 ; k++)
    {
        p[k] = 1.0 * d[k] / de ; 
    }

    vector < ld > ps( 2 * maxi + 1 ,0.0) ; 
    for ( ll i = 1 ; i <=  maxi ; i++)
    {
        for ( ll j = 1 ; j <= maxi ; j++)
        {
            ps[i+j] += p[i] * p[j] ; 
        }
    } 
    vector < ld > pre(2 * maxi + 2 , 0.0) ; 
    pre[0] = 0.0 ; 
    pre[1] = 0.0 ; 
    pre[2] = ps[1] ; 
    for(ll k = 3 ; k < 2 * maxi + 2 ; k++)
    {
        pre[k] = pre[k-1] + ps[k-1] ; 
    }
    ld ans = 0.0 ; 
    for(ll i = 1 ; i <= maxi ; i++)
    {
        ans += pre[i] * p[i] ; 
    }
    cout << fixed << setprecision(10) << ans << endl ; 

    





    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  