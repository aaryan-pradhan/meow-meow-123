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

ld U(ll li , ll ri, ll k )
{
    ld pi = 0; 
    if ( k <= li )
    {
        pi = 0.0 ; 
    }
    else if ( k > ri )
    {
        pi = 1.0; 
    } 
    else 
    {
        // li to k-1 are valid 
        pi = 1.0 * ( k-1 - li + 1) / (ri - li + 1 ) ; 
    }
    return pi ; 
}
void solve() 
{
    ll n ; 
    cin >> n ; 
    vector < pll > a(n+1) ;
    ll maxi = 0 ;  
    for( ll i = 1 ; i <= n ; i++)
    {
        cin >> a[i].fr >> a[i].sc ; 
        maxi = max(maxi , a[i].sc) ; 
    }
    ld ans = 0 ; 
    for( ll k = 1 ; k <= maxi ; k++)
    {
        ld temp = 0.0 ; 
        ld pk = 1.0 ; 
        ld qk = 0.0 ; 
        ld rest = 0.0 ; 
        for( ll i = 1 ; i <= n ; i++)
        {
            ll li = a[i].fr ; 
            ll ri = a[i].sc ; 
            ld pi = U(li , ri , k) ; 
            pk *= pi ;   
        }
        temp += pk ; 
        for( ll i = 1 ; i <= n ; i++ )
        {
            ll li = a[i].fr ; 
            ll ri = a[i].sc ; 
            rest = 1.0 ; 
            for( ll j = 1 ; j <= n ; j++)
            {
                if(i==j)
                {
                    continue ;
                }
                else 
                {
                    ll lj = a[j].fr ; 
                    ll rj = a[j].sc ; 
                    rest *= U(lj , rj , k ) ; 
                }
            }
            rest *= (1 - U(li,ri,k)) ; 
            qk += rest ; 
        }
        temp += qk; 
        ans += ( 1.0 - temp) ; 
    }
    cout << fixed << setprecision(9) << ans << endl ; 

    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  