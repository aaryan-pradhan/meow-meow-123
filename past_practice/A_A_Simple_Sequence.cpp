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

vector < vector < ll > > g ;

void solve() 
{
    ll n ; 
    cin >> n ;
    
    // Resizing our global graph variable cleanly, even though we 
    // strictly only need the difference array for this logic!
    g.assign(n + 5, vector < ll > ()) ; 
    
    deque < ll > p(n + 1) ;
    for(ll i = 1 ; i <= n ; i++ ) 
    {
        cin >> p[i] ;
    }
    
    // Difference array to manage range updates efficiently
    deque < ll > diff(n + 5, 0) ;
    
    for(ll i = 1 ; i <= n ; i++ ) 
    {
        if(p[i] <= i) 
        {
            // Range [i + 1, n + 1] gets +1
            diff[i + 1]++ ;
            diff[n + 2]-- ;
        } 
        else 
        {
            // Range [i + 1, p[i]] gets +1
            diff[i + 1]++ ;
            diff[p[i] + 1]-- ;
        }
    }
    
    ll ans = 0 ;
    ll curr = 0 ;
    
    // Calculate prefix sums to evaluate all possible ending boundaries K
    for(ll i = 1 ; i <= n + 1 ; i++ ) 
    {
        curr += diff[i] ;
        ans = max(ans, curr) ;
    }
    
    cout << ans << endl ;
}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t ;
    for(ll i = 0 ; i < t ; i++ ) 
    {
        solve() ;
    }
}