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
    ll k , l ;
    cin >> k >> l ;
    ll c = 0 ; 
    while(l != 1)
    {
        if(l % k != 0)
        {
            pn ; 
            return ;
        }
        l /= k ;
        c++ ;
    }
    py ; 
    cout << c-1 << endl ;




   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  