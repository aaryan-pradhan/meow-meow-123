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
    
    ll n, m, k;
    cin >> n >> m >> k;
    
    char c0 = '0';
    char c1 = '1';
    
    if(m > n)
    {
        swap(n, m);
        swap(c0, c1);
    }
    
    if(k < n - m || k > n)
    {
        cout << -1 << endl;
        return;
    }
    
    vector<char> v;
    
    for(ll i = 0; i < k; i++)
    {
        v.push_back(c0);
    } 
    
    ll rem0 = n - k;
    for(ll i = 0; i < rem0; i++)
    {
        v.push_back(c1);
        v.push_back(c0);
    }
    
    ll rem1 = m - rem0;
    for(ll i = 0; i < rem1; i++)
    {
        v.push_back(c1);
    }
    
    for(char c : v)
    {
        cout << c;
    }
    cout << endl;

}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t; 
    for(ll i = 0; i < t; i++)
    {
        solve();
    }
}