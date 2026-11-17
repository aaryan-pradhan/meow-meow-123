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
 
 
 
using namespace std ;
 
#define py cout << "YES" << endl
#define pn cout << "NO" << endl

 
 
ll gcd(ll a, ll b) 
{
    while (b != 0) 
    {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 

 
void solve() 
{
    ll n ; 
    cin >> n ;

    vector<ll> a ; 
    for (ll i = 1; i <= n; i += 2) 
    {
        for (ll j = i; j <= n; j *= 2) 
        {
            a.push_back(j);
        }
    }
    for (auto num : a) {
        cout << num << " ";
    }
    cout << endl ; 
    
    
    
 
    
    
}
signed main() 
{
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    long long T;
    cin >> T;
    for (ll i = 1; i <= T; i++)
    {
        solve();
    }
}
 