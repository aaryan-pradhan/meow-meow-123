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
ll dp[31][3] ; 
ll rec ( ll i , ll s)
{
    // this returns the p value from i to 31 if the past state is state 
    if ( i == 31)
    {
        return 1 ; 
    }
    if ( dp[i][s]!=-1)
    {
        return dp[i][s] ; 
    }
    ll ans = 0 ;
    if ( s == 0)
    {
        ans  = ans % MOD + rec(i + 1 , 1) % MOD ; 
        ans = ans % MOD + rec(i + 1 , 0) % MOD ; 
    }
    else if ( s == 1 )
    {
        ans = ans % MOD + rec( i + 1 , -1 ) % MOD ; 
    }
    else if ( s == -1)
    {
        ans  = ans % MOD + rec(i + 1 , 1) % MOD ; 
        ans = ans % MOD + rec(i + 1 , 0) % MOD ; 
    }
    return dp[i][s] = ans ; 
}
void solve() 
{
    ll K ; 
    cin >> K ; 
    deque < ll > ans ; 

    while( K != 0 )
    {
        ll no = 1 , n = 0 ; 
        while ( no <= K)
        {
            no = no << 1 ; 
            n++ ; 
        }
        //debug(no/2) ;
        K -= no/2 ; 
        ans.push_back(n-1) ; 
    }   

    ll top = ans.front() ; 
    ll q = top ; 
    ans.pop_front() ; 
    ll res = 1 ; 

    while(!ans.empty())
    {
        ll space = top - ans.front() -1 ;
    
        res = res * rec(31 - space,1)  ; 
        top = ans.front() ; 
        ans.pop_front() ; 
        

    }
    ll p = res ; 

    while ( p % 3 == 0 )
    {
        p/= 3 ;
        q-- ; 
    }
    cout << ( p + q ) % MOD  << endl ; 


    



}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll t ; 
    cin >> t ; 
    memset(dp,-1,sizeof(dp)) ; 
    while ( t--)
    {
        solve() ; 
    } 
}
    
  