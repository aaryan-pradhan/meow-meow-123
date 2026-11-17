
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
    ll n;
    cin >> n;
    
    vector <ll> ci(n);
    vector <ll> pi(n);
    
    for(ll i = 0; i < n; i++) 
    {
        cin >> ci[i] >> pi[i];
    }
    

    vector <long double> dp(n + 1, 0.0);
    
    for(ll i = n - 1; i >= 0; i--) 
    {
        long double mult = 1.0 - (long double)pi[i] / 100.0;
        long double take = (long double)ci[i] + mult * dp[i + 1];
        
        if(take > dp[i + 1]) 
        {
            dp[i] = take;
        }
        else
        {
            dp[i] = dp[i + 1];
        }
    }
    
    cout << fixed << setprecision(10) << dp[0] << endl;
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