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
    ll n , m ; 
    cin >> n >> m ;
    vector < ll > chosen ( m + 1 , 0 ) ;
    vector < ll > ans ( n , 0 ) ; 
    for ( ll i = 0 ; i < n ; i++ )
    {
        ll l ; 
        cin >> l ; 
        vector < ll > a ( l ) ;
        ll flag = 0 ; 
        for ( ll j = 0 ; j < l ; j++ )
        {
            cin >> a[j] ; 
            if ( chosen[a[j]] == 0  && flag == 0 )
            {
                chosen[a[j]] = 1 ;
                ans[i] = a[j] ;
                flag = 1 ; 
            }
            
        }
    }
    for ( ll i = 0 ; i < n ; i++ )
    {
        cout << ans[i] << endl ; 
    }
    cout << endl ;

    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  