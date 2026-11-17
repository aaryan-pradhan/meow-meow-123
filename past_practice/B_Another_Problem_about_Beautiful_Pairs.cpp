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

void solve() 
{
    ll n ; 
    cin >> n ;
    vector < ll > a ( n + 1 ) ;
    vector < ll > lit ; 
    for ( ll i = 1 ; i <= n ; i++ )
    {
        cin >> a[i] ;
        lit.push_back(a[i]) ;



    }
    sort(lit.begin(), lit.end()) ;

    vector < vector < ll > > indg ( n + 1 ) ;
    for ( ll i = 1 ; i <= n ; i++ )
    {
        if(a[i] <= n)
        {
            indg[a[i]].push_back(i) ;
        }
    }
    ll ans = 0 ; 
    
    for(auto num : lit)
    {
        ll x = num ;
        for( auto num2 : lit)
        {
            ll y = num2 ;
            
            ll m = x * y ;
            for(auto i : indg[x])
            {
                ll j = i + m ; 
                if(j <= n && a[j] == y)
                {
                    ans++;
                }
            }
        }
    }
    cout << ans << endl ;

   






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
    
  