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
#define pn cout << "NO" << endl
#define pll pair<ll,ll>
using namespace std;
// Problem Statement
/*
  
*/
// Small Observations
/*

*/
// Claims on algo 
/*  
    
*/
void solve() 
{
    string s ; 
    cin >> s ; 
    char prev = s[0] ; 
    ll c = 1 ; 
    ll maxc = 1 ; 
    ll n = s.length() ; 
    for( ll i = 1 ; i < n ; i++)
    {
        if(s[i]==prev)
        {
            c++ ; 
            maxc = max(maxc , c) ; 
        }
        else
        {
            c = 1 ; 
        }
        prev = s[i] ; 
    }
    cout << maxc << endl ; 
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