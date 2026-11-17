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
#define pn cout << -1 << endl
#define pll pair<ll,ll>

using namespace std;
bool comp(pll a, pll b)
{
    ll s = a.fr + a.sc;
    ll t = b.fr + b.sc;
    if(s == t)
    {
        return a.fr < b.fr;
    }
    return s < t;
}
void solve() 
{
    ll n , k ; 
    cin >> n >> k;
    if(k > n*n)
    {
        pn ; 
        return ;
    }
    
    vector < pll > order ; 
    for(ll i = 0 ; i < n ; i++)
    {
        for(ll j = 0 ; j < n ; j++)
        {
            order.push_back({i, j}) ;
        }
    }
    sort(order.begin(), order.end(), comp) ;
    //debug(order) ;
    vector < vector < ll >> mat(n, vector < ll >(n, 0)) ;
    if(k%2==0)
    {
        for(ll i = 0 ; i < n ; i++)
        {
            
            if(k==0)
            {
                break ;
            }
            mat[i][i] = 1 ; 
            k-- ; 
        }
    }
    
    for(auto p : order)
    {
        if(k==0)
        {
            break ;
        }
        if(mat[p.fr][p.sc] == 0)
        {
            mat[p.fr][p.sc] = 1 ; 
            k-- ; 
        }
        


    }

    for(ll i = 0 ; i < n ; i++)
    {
        for(ll j = 0 ; j < n ; j++)
        {
            if(mat[i][j] != mat[j][i])
            {
                pn ;
                return ;
            }
        }
    }
    for(ll i = 0 ; i < n ; i++)
    {
        for(ll j = 0 ; j < n ; j++)
        {
            cout << mat[i][j] << " " ;
        }
        cout << endl ;
    }





    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  