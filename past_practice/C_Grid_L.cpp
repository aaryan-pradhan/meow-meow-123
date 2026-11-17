// orz
#include "bits/stdc++.h"
#include <math.h>   

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
ll n , m ; 
ll grid[100][100] ;
ll dp[100][100] ;
ll gcd(ll a , ll b)
{
    if(b == 0) return a ;
    return gcd(b , a%b) ;
}
ll madd(ll a , ll b)
{
    return (a%MOD + b%MOD)%MOD ;
}

int depth = 0; 

ll rec(ll i , ll p)
{
    // 1. Print ENTRY into the state with dynamic indentation
    string pad(depth * 4, ' '); 
    cout << pad << "-> Entering rec(i = " << i << ", p = " << p << ")\n";

    if(i == n)
    {
        if(p == 1) {
            cout << pad << "<- Base Case Hit: Returning 1\n";
            return 1 ;
        }
        else {
            cout << pad << "<- Base Case Hit: Returning 0\n";
            return 0 ;
        }
    }
    
    // 2. Print when you hit a PRE-CALCULATED state
    if(dp[i][p] != -1) {
        cout << pad << "<- Memo Hit! Returning " << dp[i][p] << " for (i = " << i << ", p = " << p << ")\n";
        return dp[i][p] ;
    }
    
    ll ans = 0 ; 
    for(ll j = 0 ; j < m ; j++)
    {
        depth++; // 3. GO DEEPER before calling recursion
        ans = madd(ans , rec(i+1 , gcd(p , grid[i][j]))) ;
        depth--; // 4. COME BACK UP after recursion finishes
    }

    // 5. Print the FINAL EVALUATED state before saving it
    cout << pad << "<- Evaluated rec(i = " << i << ", p = " << p << ") = " << ans << "\n";
    return dp[i][p] = ans ;
}
void solve() 
{
    cin >> n >> m ;
    memset(grid , 0 , sizeof(grid)) ;
    ll maxi = 0 ; 
    for(ll i = 0 ; i < n ; i++)
    {
        for(ll j = 0 ; j < m ; j++)
        {
            cin >> grid[i][j] ;
            maxi = max(maxi , grid[i][j]) ;
        }
    }
    
    
    
    cout << rec(0,1) << endl ; 


}

signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t ;
    for(ll i = 0 ; i < t ; i++ )
    {
        solve() ;
    }
}
    
  