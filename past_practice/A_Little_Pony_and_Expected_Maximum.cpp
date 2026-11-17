// orz
#include "bits/stdc++.h"
#define ld long double 
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

ld pow( ld a , ll b)
{
    ld res = 1.0 ; 
    while ( b > 0 )
    {
        if ( b & 1 )
        {
            res *= a ; 
        }
        a *= a ; 
        b >>=1 ; 

    }
    return res ; 


}
void solve() 
{
  ll m , n ; 
  cin >> m >> n ;
  ld ans = 1 ;  
  for(ld i = 1 ; i <= m-1; i++)
  {
    ans += ( 1 - pow((i/m),n)) ; 
    
  }
  cout << fixed << setprecision(6) << ans << endl ; 
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  