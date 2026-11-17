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
ll k , p  ; 
ll q ; 
ld dp[1001][1001] ; 
bool vis[1001][1001] ; 

ld rec(ll d ,ll j)
{
    if ( d < 0 || j < 0 )
    {
        return 0.0 ; 
    }
    if(d==0)
    {
        if(j==0)
        {
            return 1.0 ; 
        }
        else 
        {
            return 0.0 ; 
        }
    }
    if(vis[d][j])
    {
        return dp[d][j] ; 
    }
    ld t1 = rec( d-1 , j ) ; 
    ld t2 = rec( d-1,j-1 ) ; 
    ld ans = t1 * j / k + t2 * (k - j + 1)  *1.0 / k ; 
    vis[d][j] = 1 ; 
    dp[d][j] = ans ; 
    return dp[d][j] ; 
    
}
void solve() 
{
    cin >> k >> q ; 
    cin >> p ; 
    memset(dp,0.0,sizeof(dp)) ; 
    memset(vis,0,sizeof(vis)) ; 
    cout << fixed << setprecision(7) << rec(10,k) << endl ; 



    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  