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
#define ld long double 
using namespace std;

void solve() 
{
    ll n ; 
    cin >> n ; 
    string a , b ; 
    cin >> a >> b ; 
    a = "/" + a ; 
    b = "/" + b ; 
    ll sa[26] ; 
    ll sb[26] ;
    memset(sa, 0 , sizeof(sa)) ; 
    memset(sb, 0 , sizeof(sb)) ;
    ld cb = 0 ; 
    for ( ll i = 1 ; i <= n ; i++)
    {
        cb += sa[b[i]-'A'] * ( n - i + 1);
        sa[a[i]-'A'] += i ; 
    }
    ld ca = 0 ; 
    for ( ll i = 1 ; i <= n ; i++)
    {
        ca += sb[a[i]-'A'] * ( n - i + 1);
        sb[b[i]-'A'] += i ; 
    }
    ld ans = 0 ; 
    ld div = n * ( n + 1 ) * ( 2 * n + 1 ) / 6 ; 
    for ( ll i = 1 ; i <= n ; i++)
    {
        if(a[i]==b[i])
        {
            ans += i * (n-i+1) ; 
        }  
    }
    ans += (ca + cb) ; 
    ans /= div ; 
    cout << fixed << setprecision(10) << ans << endl ; 
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  