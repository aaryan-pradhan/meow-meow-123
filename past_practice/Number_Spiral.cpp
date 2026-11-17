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
  
*
// Small Observations
/*


    



    
    
    
    
*/
// Claims on algo 
/*  
    
*/
struct full
{
    ll id ; 
    ll H , d , h ; 
}; 
bool comp( full A , full B) 
// returns true if A should come before B
{
    __int128_t numA = ( __int128_t) A.d  * A.h ; 
    __int128_t numB = ( __int128_t) B.d  * B.h ;
    __int128_t denA = (A.H - A.h) ;
    __int128_t denB = (B.H - B.h) ; 
    __int128_t lhs = (__int128_t)numA * denB;
    __int128_t rhs = (__int128_t)numB * denA;
    if( lhs != rhs)
    {
        return lhs > rhs ; 
    }
    else 
    {
        return A.id < B.id ; 
    }
}
void solve() 
{
    ll n ; 
    cin >> n ; 
    vector < full > tr(n) ; 
    for( ll i = 0 ; i  < n ; i++)
    {
        tr[i].id = i + 1 ;
        cin >> tr[i].H >> tr[i].d >> tr[i].h  ;
    }
    sort(tr.begin() , tr.end() , comp) ; 
    for( ll i = 0 ; i < n ; i++)
    {
        cout << tr[i].id << " " ; 
    }
    cout << endl ;

    

}
signed main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t ; 
    cin >> t; 
    while(t--)  
        solve() ; 
} 
// Golden Rules
/*
    Solutions are simple.
    Proofs are simple. 
    Implementations are simple.
*/