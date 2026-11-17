#include "bits/stdc++.h"

#define ll unsigned long long
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

ll gcd(ll a, ll b) 
{
    if (b == 0) 
        return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) 
{
    return (a / gcd(a, b)) * b;
}
void solve() 
{
    ll a, b, c, m;
    cin >> a >> b >> c >> m;
    
    ll lab = lcm(a, b);
    ll lac = lcm(a, c);
    ll lbc = lcm(b, c);
    ll labc = lcm(lab, c);
    

    ll nabc = m / labc;
    

    ll nab = (m / lab) - nabc;
    ll nac = (m / lac) - nabc;
    ll nbc = (m / lbc) - nabc;
    ll na = (m / a) - nab - nac - nabc;
    ll nb = (m / b) - nab - nbc - nabc;
    ll nc = (m / c) - nac - nbc - nabc;
    

    ll ansa = na * 6 + (nab + nac) * 3 + nabc * 2;
    ll ansb = nb * 6 + (nab + nbc) * 3 + nabc * 2;
    ll ansc = nc * 6 + (nac + nbc) * 3 + nabc * 2;
    
    cout << ansa << " " << ansb << " " << ansc << endl;
}

signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    cin >> t ;
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ; 
    }
}