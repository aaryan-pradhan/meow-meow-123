// orz
#include"bits/stdc++.h"
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
ll n ; 
ll dp[1000010][7] ;  
ll rec ( ll i , ll s ) 
{
    // this returns the number of ways of attach sequences to from level i to the end if the past things is the state s that should not have TT or S if it is not that then you can put both, there are 8 combos for the past characters null- 0  , T - 1  , S - 2  , ST - 3  , TS - 4  ,  ( cann ot move here ) SS - 5  , TT - 6  these are the 8 combos that are there in the based on that we are going to make the changes to the state 
    if( i == 1000010 ) 
    {
        return 1 ; 
    }
    if (dp[i][s] != -1)
    {
        return dp[i][s] ; 
    }
    ll ans = 0 ; 
    if ( s == 0 )
    {
        ans = ans % MOD + rec( i + 1 , 2 ) % MOD ;
        ans = ans % MOD + rec( i + 1 , 1 ) % MOD ;
    }
    else if ( s == 1 ) 
    {
        ans = ans % MOD + rec( i + 1 , 4 ) % MOD ;
        ans = ans % MOD + rec( i + 1 , 6 ) % MOD ;
    }    
    else if ( s == 2 ) 
    {
        ans = ans % MOD + rec( i + 1 , 3 ) % MOD ;
    }  
    else if ( s == 3 ) 
    {
        ans = ans % MOD + rec( i + 1 , 4 ) % MOD ;
        ans = ans % MOD + rec( i + 1 , 6 ) % MOD ;
    }     
    else if ( s == 4 ) 
    {
        ans = ans % MOD + rec( i + 1 , 3 ) % MOD ;
    }   
    else if ( s == 6 ) 
    {
        ans = ans % MOD + rec( i + 1 , 4 ) % MOD ;
    } 
    return dp[i][s] = ans; 
    

}
void solve() 
{
    cin >> n ; 
    cout << rec ( 1000010 - n , 0 ) % MOD << endl ;

    
    
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll t ; 
    cin >> t ; 


    memset(dp , -1, sizeof(dp)) ; 

    //cout << ans << endl ; 

    while(t--)
    {
        solve() ; 
    }
}
    
  