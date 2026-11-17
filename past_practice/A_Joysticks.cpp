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

ll rec(ll a1 , ll a2 )
{
    if(a1 <= 0 || a2 <= 0)
        return 0;
    

    
    if(a1 < a2)
    {
        swap(a1,a2);
    }
    return 1 + rec(a1-2,a2+1);
}
void solve() 
{
    ll a1 , a2 ; 
    cin >> a1 >> a2 ;
    cout << rec(a1 ,a2) << endl;
    
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  