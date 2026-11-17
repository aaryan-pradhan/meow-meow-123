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
   ll m = 2 * n ; 
   vector < ll > a ( m + 1 ) ;
   deque < vector < ll > > b ( n + 1, vector < ll > (2,0) ) ; 
   for( ll i = 1 ; i <= m ; i++ )
   {
       cin >> a[i] ;
       if(b[a[i]][0] == 0)
       {
           b[a[i]][0] = i ;
       }
       else 
       {
           b[a[i]][1] = i ;
       }



   }
   
   ll ans = 0 ; 
   vector < ll > prev(2,1) ; 
   vector < ll > cur(2,0) ;
   b.pop_front() ;
   while( !b.empty() )
   {
       vector < ll > curr = b.front() ; 
       ans += abs(curr[1] - prev[1]) + abs(curr[0] - prev[0]);
       prev = curr ;
       b.pop_front() ;
   }
   cout << ans << endl ;
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  