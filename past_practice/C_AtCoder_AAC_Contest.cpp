// orz
#include <bits/stdc++.h>
#include<iostream>
#include<iomanip>
#define ll  unsigned long long 
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

using namespace std;

void solve() 
{
    ll nA , nB , nC ; 
    cin >> nA >> nB >> nC ;
    ll mini = min(nA,min(nB,nC)) ;
    ll ans = 0 ; 
    if(mini == nA || mini == nC)
    {
        ans = mini ; 
    }
    else 
    {
        ans = nA + nB + nC ; 
        ans /= 3 ; 

        
    }
    cout << ans << endl ;
        
    

}

signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    cin >> t ; 
    while(t--)
    {
        solve() ; 
    } 
}
    
  