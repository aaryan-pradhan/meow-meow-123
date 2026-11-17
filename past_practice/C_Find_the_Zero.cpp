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
    cin >> n;
    
    ll res;
    
    
    cout << "? 1 2" << endl;
    cout.flush();
    cin >> res;

    if(res == -1) exit(0);

    if (res == 1) 
    { 
        cout << "! 1" << endl;
        cout.flush();
        return;
    }
    
    cout << "? 2 3" << endl;
    cout.flush();
    cin >> res;

    if(res == -1) exit(0);
    if (res == 1) 
    { 
        cout << "! 2" << endl; 
        cout.flush(); 
        return; 
    }
    
    cout << "? 3 1" << endl; 
    cout.flush();
    cin >> res;
    
    if(res == -1) exit(0);
    if (res == 1) 
    { 
        cout << "! 3" << endl; 
        cout.flush(); 
        return; 
    }
    
    
    for (ll i = 1; i <= n - 2; ++i) 
    {
        ll u = 3 + 2 * i - 1;
        ll v = 3 + 2 * i;
        
        cout << "? " << u << " " << v << "\n"; 
        cout.flush();
        cin >> res;

        if(res == -1) exit(0);
        
        if (res == 1) 
        { 
            cout << "! " << u << "\n"; 
            cout.flush(); 
            return; 
        }
    }
    
    
    cout << "! " << 2 * n << "\n";
    cout.flush();

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
        solve() ;
    }
}
    
  