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
    cin >> n ; 
    vector <ll> a(n) ;
    vector < ll > pa(n+1,0) ; 
    for(ll i = 0 ; i < n ; i++)
    {
        cin >> a[i] ;
        pa[a[i]]++ ; 


    }
    


    vector < ll > b(n) ;
    
    for(ll i = 0 ; i < n ; i++)
    {
        cin >> b[i] ;

    }
    ll la ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        if(pa[i]==0)
        {
            la = i ; 
            break ; 

        }
    }
    pll da ;
    for(ll i = 0 ; i < n ; i++)
    {
        for(ll j = i + 1 ; j < n ; j++)
        {
            if(a[i] == a[j])
            {
                da = {i,j} ; 
                break ; 

            }
            
        }       
    }
    a[da.fr] = la ; 
    ll c = 0 ; 
    for(ll i = 0 ; i < n ; i++)
    {
        if(a[i] == b[i])
        {
            c++ ; 
        }
    }
    if(c != n-1)
    {
        swap(a[da.fr],a[da.sc]) ;
        
    }
    for(ll i = 0 ; i < n ; i++)
    {
        cout << a[i] << " " ; 
    }
    cout << endl ;


    
    
    


    



    

   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  