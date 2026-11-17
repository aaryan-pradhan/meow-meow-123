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
ld dp[101][101][101] ; 
bool vis[101][101][101] ; 



ld rec( ll r , ll p , ll s)
{
    if ( r == 0 )
    {
        return 0.0 ; 
    }
    if (p == 0 )
    {
        return 1.0 ; 
    }
    if( s == 0 )
    {
        return 0.0 ; 
    }
    if( vis[r][p][s])
    {
        return dp[r][p][s] ; 
    }
    ld ans = 0.0 ;  
    ans = r * p * rec( r - 1 , p , s ) ; 
    ans += p * s * rec ( r , p - 1 , s) ; 
    ans += s * r * rec( r , p , s - 1 ) ; 
    ans /= 1.0 * (  r * p + p * s + s * r  ) ; 
    vis[r][p][s] = true ; 
    return dp[r][p][s] = ans ; 

}
void solve() 
{
    ll r , p , s ; 
    cin >> r >> s >> p ; 
    memset(vis,0,sizeof(vis)) ; 
    memset(dp,0.0 ,sizeof(dp)) ; 
    ld a1 = rec ( r , p , s ) ; 
    ld a2 = rec ( p , s , r ) ; 
    ld a3 = rec ( s , r , p ) ; 
    cout << fixed << setprecision(10) << a1 << " " << a3 << " " << a2 << endl ; 

    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  