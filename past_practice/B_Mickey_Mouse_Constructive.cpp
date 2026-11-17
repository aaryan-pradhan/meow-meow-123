// orz
#include "bits/stdc++.h"
 
#define ll long long 
#define endl "\n"
#define fr first
#define sc second
#define MOD 1000000007
#define MOD1 676767677
#define INF 1e18
#define mp make_pair
#define PI acos(-1) 
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define pll pair<ll,ll>
 
using namespace std;

void solve() 
{
    ll x , y ; 
    cin >> x >> y ;
 
    ll s = abs(x - y) ;
    ll ans = 0 ;
 
    if (s == 0) 
    {
        ans = 1 ;
    } 
    else 
    {
        for (ll i = 1 ; i * i <= s ; i++) 
        {
            if (s % i == 0) 
            {
                ans++ ;
                if (i * i != s) 
                {
                    ans++ ;
                }
            }
        }
    }
 
    vector < ll > res ;
    if (x > y) 
    {
        for (ll i = 0 ; i < y ; i++) 
        {
            res.push_back(-1) ;
        }
        for (ll i = 0 ; i < x ; i++) 
        {
            res.push_back(1) ;
        }
    } 
    else 
    {
        for (ll i = 0 ; i < x ; i++) 
        {
            res.push_back(1) ;
        }
        for (ll i = 0 ; i < y ; i++) 
        {
            res.push_back(-1) ;
        }
    }
    
    cout << (ans % MOD1) << endl ;
    for(auto x : res) 
    {
        cout << x << " " ;
    }

    cout << endl ;
 
}
 
signed main() 
{
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll t; 
    cin >> t;
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ;
    }
        
}