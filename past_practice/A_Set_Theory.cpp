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
bool valid[1000005] ;
void solve() 
{
    ll n ; 
    cin >> n ; 
    vector < ll > a(n) ;
    for(ll i = 0 ; i < n ; i++)
    {
        cin >> a[i] ;
    }
    memset(valid,1,sizeof(valid)) ;

    set < ll > diff ; 
    for(ll i = 0 ; i < n ; i++)
    {
        for(ll j = i + 1 ; j < n ; j++)
        {
            diff.insert(abs(a[i] - a[j])) ;
        }  
    }
    ll curr = 1 ; 
    
    vector < ll > b ; 
    for(ll i = 0 ; i < n ; i++)
    {
        b.push_back(curr) ; 

        for ( auto d : diff)
        {
            if(curr + d <= 1000000 && valid[curr + d])
            {
                valid[curr + d] = false ;
            }
        }
        curr++ ; 
        while(curr <= 1000000 )
        {
            if(valid[curr])
            {
                break ;
            }
            curr++ ;
        }


        
    }
    py ; 
    for(ll i = 0 ; i < n ; i++)
    {
        cout << b[i] << " " ; 
    }
    cout << endl ;
    

    
   






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
    
  