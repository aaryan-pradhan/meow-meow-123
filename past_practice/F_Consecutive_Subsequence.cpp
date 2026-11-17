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

map < ll , ll > m ;

void solve() 
{
    
    ll n ; 
    cin >> n ; 
    vector < ll > dp(n , -1) ;
    vector < ll > a(n) ;
    vector < ll > dp2(n , -1) ; 

    

    for(ll i = 0 ; i < n ; i++)
        cin >> a[i];



 

    for(ll i = 0 ; i < n ; i++)
    {
        m[a[i]] = i ;
        if(i == 0)
        {
            dp[i] = 1;
            dp2[i] = 0 ; 
            continue;
        }
        if(dp[i] != -1)
            continue;
        ll ans ; 
        if(m.find(a[i]-1) == m.end())
        {
            ans = 1 ; 
            dp2[i] = i ; 
        }
        else
        {
            ans = 1 + dp[m[a[i]-1]];
            dp2[i] = m[a[i]-1] ;
        }
        dp[i] = ans;

    }

    ll ele = *max_element(dp.begin() , dp.end()) ;
    auto it = find(dp.begin() , dp.end() , ele) ;
    ll idx = it - dp.begin() ;


    vector < ll > res ;
    while(ele--)
    {
        res.push_back(idx)  ; 
        idx = dp2[idx] ;
    }
    reverse(res.begin() , res.end()) ;
    cout << res.size() << endl;
    for(auto x : res)
        cout << x+1 << " " ;
    cout << endl ; 
    
    


    
    

    

    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  