// orz
#include "bits/stdc++.h"
#define ll long long 
#define endl "\n"
#define fr first
#define sc second


#define INF 1e18
#define mp make_pair
#define PI acos(-1) 
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define pll pair<ll,ll>

using namespace std;

const ll MOD = 998244353 ; 


inline ll mcorr(ll a) 
{
    a %= MOD;
    return a < 0 ? a + MOD : a;
}

inline ll madd(ll a, ll b) 
{
    ll res = a + b;
    return res >= MOD ? res - MOD : res;
}

inline ll msub(ll a, ll b) 
{
    ll res = a - b;
    return res < 0 ? res + MOD : res;
}

inline ll mmul(ll a, ll b) 
{
    return (a * b) % MOD;
}

inline ll mpow(ll a, ll b) 
{
    ll res = 1;
    while (b > 0) 
    {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

inline ll minv(ll a) 
{
    return mpow(a, MOD - 2);
}

inline ll mdiv(ll a, ll b)
{
    return mmul(a, minv(b));
}

inline ll nCr(ll n, ll r) 
{
    if (r < 0 || r > n) return 0;
    
    ll num = 1;
    ll den = 1;
    
    for (ll i = 0; i < r; i++) 
    {
        num = mmul(num, (n - i) % MOD);
        den = mmul(den, i + 1);
    }
    
    return mdiv(num, den);
}



void solve() 
{
    ll n , k ; 
    cin >> n >> k ;
    vector < ll > a(n) ; 
    ll s = 0 ; 
    for ( ll i = 0 ; i < n ; i++ )
    {
        cin >> a[i] ; 
        if(i)
        {
            s += a[i] ;
        }
    }
    ll rem = a[0] - s ;
    if( rem < k )
    {
        cout << 0 << endl ;
        return ; 
    }
    // I have k boxes to fill and rem balls to fill in those boxes and I must fill atleast 1 ball in each box
    ll ans = nCr(rem -  1 , k-1) ; 
    // for the rest I have to fill k boxes will a[i] balls and they are mutually indep
    for( ll i = 1 ; i < n ; i++ )
    {
        ans = mmul(ans , nCr(a[i] + k - 1 , k-1)) ; 
    }
    cout << mcorr(ans) << endl ;


    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    
 
    solve() ; 
}
    
  