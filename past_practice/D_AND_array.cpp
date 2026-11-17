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



vector < vector <ll> > S2(65, vector<ll>(65, 0));
void fill_S2() 
{
    S2[0][0] = 1;
    for(ll i = 1; i < 65; i++) 
    {
        for(ll j = 1; j <= i; j++) 
        {
            S2[i][j] = madd(mmul(j, S2[i-1][j]), S2[i-1][j-1]);
        }
    }
}


vector<ll> BM(vector < ll > s) 
{
    vector<ll> C = {1}, B = {1};
    ll L = 0, m = 1, b_val = 1;
    for(ll i = 0; i < s.size(); i++) 
    {
        ll d = 0;
        for(ll j = 0; j <= L; j++) 
        {
            d = madd(d, mmul(C[j], s[i-j]));
        }
        
        if(d == 0) 
        {
            m++;
        } 
        else 
        {
            vector<ll> T = C;
            ll c = mmul(d, minv(b_val));
            while(C.size() <= B.size() + m)
            {
                C.push_back(0);
            }
            for(ll j = 0; j < B.size(); j++) 
            {
                C[j+m] = msub(C[j+m], mmul(c, B[j]));
            }
            if(2 * L <= i) 
            {
                L = i + 1 - L;
                B = T;
                b_val = d;
                m = 1;
            } 
            else 
            {
                m++;
            }
        }
    }
    return C;
}



void solve() 
{
    ll n ; 
    cin >> n ;
 
    vector < ll > b(max(n + 1, 65LL), 0) ; 
    for(ll i = 1 ; i <= n ; i++) 
    {
        cin >> b[i] ;
    }
 

    vector < ll > seq ;
    for(ll k = 1 ; k <= 60 ; k++) 
    {
        ll s = 0 ;
        for(ll r = 1 ; r <= k ; r++) 
        {
            ll t = mmul(S2[k][r], fact[r]) ;
            t = mmul(t, b[r]);
            s = madd(s, t) ;
        }
        seq.push_back(s) ;
    }

    vector < ll > cp ; 
    cp = BM(seq) ;
    ll L = cp.size() - 1 ;

    vector < ll > Y ;
    Y.push_back(0) ; 

    for(ll x = 1 ; x <= n ; x++) 
    {
        ll val = 0 ;
        for(ll j = 0 ; j <= L ; j++) 
        {
            val = madd(mmul(val, x), cp[j]);
        }
        if(val == 0) 
        {
            Y.push_back(x) ;
        }
    }


    ll dim = Y.size() ;
    vector < vector < ll > > mat(dim, vector < ll > (dim + 1, 0)) ;
    
    for(ll k = 0 ; k < dim ; k++) 
    {
        
        for(ll j = 0 ; j < dim ; j++) 
        {
            mat[k][j] = nCr(Y[j], k) ;
        }

        if(k == 0) 
        {
            mat[k][dim] = ((1LL << 29) - 1) % MOD ;
        }
        else 
        {
            mat[k][dim] = b[k] ;
        }
    }

    for(ll i = 0 ; i < dim ; i++) 
    {
        ll pivot = i ;
        for(ll j = i ; j < dim ; j++) 
        {
            if(mat[j][i] != 0) 
            {
                pivot = j ; 
                break ;
            }
        }
        swap(mat[i], mat[pivot]) ;
        ll inv = minv(mat[i][i]) ;
        
        for(ll j = i ; j <= dim ; j++)
        {
            mat[i][j] = mmul(mat[i][j], inv) ;
        }
        for(ll j = 0 ; j < dim ; j++) 
        {
            if(i != j && mat[j][i] != 0) 
            {
                ll factor = mat[j][i] ;
                for(ll k = i ; k <= dim ; k++) 
                {
                    mat[j][k] = msub(mat[j][k], mmul(factor, mat[i][k])) ;
                }
            }
        }
    }


    vector < ll > a(n, 0) ;
    for(ll i = 0 ; i < dim ; i++) 
    {
        ll mask = mcorr(mat[i][dim]) ;
        ll count = Y[i] ;
        for(ll bit = 0 ; bit < 29 ; bit++) 
        {
            if((mask >> bit) & 1) 
            {
                for(ll idx = 0 ; idx < count ; idx++) 
                {
                    a[idx] |= (1LL << bit) ;
                }
            }
        }
    }

    for(auto x : a) 
    {
        cout << x << " " ;
    }
    cout << endl ;
}

signed main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    fill_fact();
    fill_S2();

    ll t;
    cin >> t ;
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ;
    }
}