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
    ll X , d ; 
    cin >> X >> d;
    
    ll ans = 1 ; 
    vector < ll > res ; 

    for(ll i = 0 ; i < 60; i++)
    {
        ll biti = X >> i & 1 ; 
        if(biti)
        {   
            for(ll j = 0 ; j < i ; j++)
            {
                res.push_back(ans) ;
            }
            ans += d ;
        }
    }
    for(ll i = 0 ; i < __builtin_popcountll(X) ; i++)
    {
        res.push_back(ans) ;
        ans += d ;
    }
    cout << res.size() << endl ;
    for(ll i = 0 ; i < res.size() ; i++)
    {
        cout << res[i] << " " ; 
    }
    cout << endl ;
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  