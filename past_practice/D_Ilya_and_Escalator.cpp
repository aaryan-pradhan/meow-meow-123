#include "bits/stdc++.h"
using namespace std;
#define ll long long 
#define ld long double 

ll n , t ; 
ld p ;
bool vis[2010][2010] ;
ld dp[2010][2010] ; 
ld rec(ll i , ll nop)
{
    // this recurrences returns the number of people standing in the escalator from i to level seconds 
    if(nop == 0)
    {
        return n ; 
    }
    if( i == t)
    {
        return n - nop ; 
    }
    
    if(vis[i][nop])
    {
        return dp[i][nop] ; 
    }
    ld ans = p * rec(i+1, nop-1) + rec(i+1, nop) * (1-p) ;
    vis[i][nop] = 1 ; 
    return dp[i][nop] = ans ; 
}
void solve()
{
    cin >> n >> p >> t ; 
    memset(vis,0,sizeof(vis)) ; 
    memset(dp,0,sizeof(dp)) ; 
    cout << fixed << setprecision(6) << rec(0,n) << endl ;

}
int main() {
	solve() ; 
	return 0 ; 

}
