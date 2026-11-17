// orz
#include "bits/stdc++.h"
#define ll long long 
#define ld long double 
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
#define pll pair<ld,ld>

using namespace std;


pll add (pll a , pll b)
{
    return { (a.fr + b.fr) , (a.sc + b.sc)} ; 
}
pll mul ( pll a , ll b)
{
    return { a.fr * b , a.sc * b } ; 
}
pll div ( pll a , ll b)
{
    return { a.fr / b , a.sc / b } ; 
}
void solve() 
{
    ll n ; 
    cin >> n ; 
    ll a , b ; 
    cin >> a >> b ; 
    

    ll s[n+1] ;
    pll dp[n+1] ;

    memset(s , -1 , sizeof(s)) ;

    for( ll i = 1 ; i <=a ; i++)
    {
        ll x ; 
        cin >> x ; 
        s[x] = 0 ; 
    }
    for( ll i = 1 ; i <=b ; i++)
    {
        ll x ; 
        cin >> x ; 
        s[x] = 1 ; 
    }
    pll sum = {0,0} ; 
    for( ll i = n ; i >= 1 ; i--)
    {

        if(i==n)
        {
            dp[i] = {1,0} ; 
        }
        else if ( s[i] == 0 )
        {
            dp[i] = {0,0} ; 
        }
        else if ( s[i] == 1 )
        {
            dp[i] = {0,1} ; 
        }
        else
        {
            dp[i] = div(sum , n-i) ; 
        }
        sum = add(sum , dp[i]) ; 


    }
    ld p = dp[1].sc / ( 1 - dp[1].fr) ;
    cout << fixed << setprecision(6) << p << endl ;





    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    cin >> t ;
    
    while (t--)
    {
        solve() ; 
    }
}
    
  