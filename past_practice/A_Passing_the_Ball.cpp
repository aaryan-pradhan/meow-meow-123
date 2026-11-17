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
    
    string s;
    cin >> s;
    
    ll ans = 0;
    for(ll i = 0; i < n; i++)
    {
        if(s[i] == 'L')
        {
            ans = i + 1;
            break;
        }
    }
    
    cout << ans << endl;
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