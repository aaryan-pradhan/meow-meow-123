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
ld dp[1001][1001][2] ; 
bool vis[1001][1001][2] ; 

ld rec ( ll w , ll b , bool s)
{
    // probabilty that the pricess wins with w balls left and b balls left and state that represents who is the person drawing 
    if ( w < 0 || b < 0 )
    {
        return 0 ; 
    }
    if(w == 0 )
    {
        return 0 ; 
    }
    
    if ( b == 0 && s == 1)
    {
        return 1 ; 
    }
    if ( b == 0 && s == 0 )
    {
        return 0 ; 
    }
    if ( vis[w][b][s])
    {
        return dp[w][b][s] ; 
    }
    ld ans = 0 ; 
    if ( s == 1)
    {
        ans = w * 1.0 / ( w + b)  + ( b * 1.0 / ( w + b) )  * rec(w,b-1,0) ; 
    }
    else 
    {
        ans = ( 1.0 * b / ( w + b ) )  * ( 1.0 *  w / ( w + b - 1 ) * rec(w-1,b-1,1) + ( b- 1.0 )  / ( w + b - 1 ) * rec(w,b-2,1)) ; 
    }
    vis[w][b][s] = 1; 
    return dp[w][b][s] = ans ; 

}
void solve() 
{
   ll w , b ; 
   cin >> w >> b ; 
   memset(vis,0,sizeof(vis)) ; 
   memset(dp,0.0,sizeof(dp)) ; 
   cout << fixed << setprecision(10) << rec(w,b,1) << endl ; 








}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  