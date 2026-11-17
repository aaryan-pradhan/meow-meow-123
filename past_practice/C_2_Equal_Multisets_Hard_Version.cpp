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
bool isPrime(ll n) 
{
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) 
    {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
vector <ll> divisors(ll n) 
{
    vector <ll> ans;
    for (ll i = 1; i * i <= n; i++) 
    {
        if (n % i == 0) 
        {
            ans.push_back(i);
            if (i != n / i) 
            {
                ans.push_back(n / i);
            }
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}
vector <pll> primeFactors(ll n)
{
    vector <pll> ans;
    for (ll i = 2; i * i <= n; i++) 
    {
        if (n % i == 0) 
        {
            ll cnt = 0;
            while (n % i == 0) 
            {
                n /= i;
                cnt++;
            }
            ans.push_back({i, cnt});
        }
    }
    if (n > 1) 
    {
        ans.push_back({n, 1});
    }
    return ans;
}
ll madd(ll a, ll b) 
{
    return ((a%MOD) +(b%MOD))%MOD ; 
}
ll msub(ll a, ll b) 
{
    return ((a%MOD) - (b%MOD))%MOD ; 
}
ll mmul(ll a, ll b) 
{
    return ((a%MOD) *(b%MOD))%MOD ; 
}
ll mpow(ll a, ll b) 
{
    ll res = 1; 
    while (b > 0) 
    {
        if (b & 1) 
        {
            res = mmul(res, a);
        }
        a = mmul(a, a);
        b >>= 1;
    }
    return res;
}
ll minv(ll a) 
{
    return mpow(a, MOD - 2);
}
ll mdiv(ll a, ll b)
{
    return mmul(a, minv(b));
}
ll mcorr(ll a) 
{
    return (a%MOD + MOD) % MOD;
}
vector<ll> fact(1000001, 1);
vector<ll> fact_inv(1000001, 1);
void fill_fact()
{
    for (ll i = 2; i <= 1000000; i++) 
    {
        fact[i] = mmul(fact[i - 1], i);
        fact_inv[i] = minv(fact[i]);
    }
}
ll nCr(ll n, ll r) 
{
    if (n < r || r < 0) return 0;
    if (n == r || r == 0) return 1;
    if(r==1 || r==(n-1))
    {
        return n;
    }
    if(r==2 || r==(n-2))
    {
        return mdiv(mmul(n, n - 1),2) ; 
    }
    if(r==3 || r==(n-3))
    {
        return mdiv(mmul(n, mmul(n - 1, n - 2)),6) ; 
    }
    if(r==4 || r==(n-4))
    {
        return mdiv(mmul(n, mmul(n - 1, mmul(n - 2, n - 3))),24) ; 
    }
    return mmul(fact[n], mmul(fact_inv[r], fact_inv[n - r]));
}

void solve() 
{
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  