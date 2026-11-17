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

void solve() 
{
    ll n ; 
    cin >> n ; 
    vector < ll > a(n+1) ;
    for(ll i = 1 ; i <= n ; i++)
    {
        ll x ; 
        cin >> x ;
        if(i&1)
        {
            a[i] = x ; 
        }
        else 
        {
            a[i] = -x ;         
        }
    }
    vector < ll > pre(n+2) ;
    pre[0] = 0 ;
    for(ll i = 1 ; i <= n ; i++)
    {
        pre[i] = pre[i-1] + a[i] ;
    }
    ll ans = 0 ;
    for(ll l = 1 ; l <= n ; l++)
    {
        for(ll r = l ; r <= n ; r++)
        {
            if((l&1) == (r&1))
            {
                if(l&1)
                {
                    if(pre[r] - pre[l-1] > 0)
                    {
                        ans++ ;
                    }
                }
                else 
                {
                    if(pre[r] - pre[l-1] < 0)
                    {
                        ans++ ;
                    }
                }
            }
            
        }
    }
    cout << ans << endl ;


    
       






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    cin >> t ;
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ;
    }
}
    
  