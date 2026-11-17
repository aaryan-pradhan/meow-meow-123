#include <bits/stdc++.h>
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
#define pn cout << "NO SOLUTION" << endl
#define pll pair<ll,ll>
using namespace std;
// Problem Statement
/*
  
*/
// Small Observations
/*
    I want to fill by array such that there is no difference of 1 


*/
// Claims on algo 
/*  
    
*/
void solve() 
{
    ll n ; 
    cin >> n ; 
    if(n==1)
    {
        cout << n << endl ; 
        return ; 
    }
    if ( n <=3)
    {
        pn ; return ; 
    }
    for( ll i = 2 ; i <= n ; i+=2)
    {
        cout << i << " " ; 
    }
    for( ll i = 1 ; i <= n ; i+=2)
    {
        cout << i << " " ; 
    }
    
    cout << endl ; 


}
signed main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t ; 
    t = 1 ; 
    while(t--)  
        solve() ; 
} 
// Golden Rules
/*
    Solutions are simple.
    Proofs are simple. 
    Implementations are simple.
*/