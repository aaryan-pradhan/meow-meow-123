
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
    deque<ll> a(n);
    for(ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<ll> freq(n+1000, 0);
    for (ll i = 0; i < n; i++) 
    {
        freq[a[i]]++;
    }
    ll critical = 0 ;
    ll mex = 0 ; 

    for (ll i = 0 ; i < n+1000 ; )
    {
        if(freq[i] >= 2)
        {
            i++;
        }
        else if(freq[i] == 1 && critical == 0 )
        {
            critical = 1 ; 
            i++; 
        }
        else if(freq[i] == 1 && critical == 1)
        {
            mex = i ; 
            break;
        }
        else if(freq[i] == 0)
        {
            mex = i ;
            break;
        }

    }
    cout << mex << endl;
 
 
 
 
 
 
 
 
}
signed main() {
 
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