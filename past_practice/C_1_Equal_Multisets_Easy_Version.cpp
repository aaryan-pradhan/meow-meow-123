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
    ll n , k ; 
    cin >> n >> k ;
 
    vector < ll > a(n) ; 
    for(ll i = 0 ; i < n ; i++) 
    {
        cin >> a[i] ;
    }
 
    vector < ll > b(n) ;
    for(ll i = 0 ; i < n ; i++) 
    {
        cin >> b[i] ;
    }
 
    vector < bool > f(n, false) ;
    vector < ll > avail(n + 2, 0) ;
    vector < ll > res ;

    for(ll m = 0 ; m < k ; m++) 
    {
        bool ok1 = true ;
        for(ll j = m ; j < n ; j += k) 
        {
            if(a[j] != a[m]) 
            {
                ok1 = false ;
            }
        }
        
        if(ok1 == true) 
        {
            avail[a[m]]++ ; 
            for(ll j = m ; j < n ; j += k) 
            {
                f[j] = true ;
            }
        }
    }
 

    for(ll i = 0 ; i < n ; i++) 
    {
        if(f[i] == false) 
        {
            if(b[i] != -1 && b[i] != a[i]) 
            {
                pn ;
                return ;
            }
        }
    }
 

    for(ll m = 0 ; m < k ; m++) 
    {
        if(f[m] == true) 
        {
            ll req = -1 ;
        
            for(ll j = m ; j < n ; j += k) 
            {
                if(b[j] != -1) 
                {
                    if(req == -1) 
                    {
                        req = b[j] ;
                    }
                    else if(req != b[j]) 
                    {
                        pn ;
                        return ;
                    }
                }
            }
            
            if(req != -1) 
            {
                res.push_back(req) ;
            }
        }
    }
 
    
    for ( auto x : res ) 
    {
        if(avail[x] > 0) 
        {
            avail[x]-- ;
        }
        else 
        {
            pn ;
            return ;
        }
    }
 
    py ;
 
}
 
signed main() 
{
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll t; 
    cin >> t;
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ;
    }
        
}