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
    ll a , b ; 
    cin >> a >> b ; 
    ld ans = 0.0 ; 
    if( b == 0 )
    {
        ans = 1 ; 
    }
    else if ( a <= 4 * b)
    {
        ans = 0.5 + a / (16.0 * b) ; 
    }
    else if ( a > 4 * b)
    {
        ans = 1 - 1.0 * b / a ; 
    }
    
    cout << fixed << setprecision(6) << ans << endl ; 


    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    cin >> t ; 
    while(t--)
    {
        solve() ; 
    }
}
    
  