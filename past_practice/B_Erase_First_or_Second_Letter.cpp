//keep it simple silly
#include <bits/stdc++.h>
#include<iostream>
#include <iomanip>
#include <map>
#define ll long long 
#define endl "\n"
#define fr first
#define sc second
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define mp make_pair
#define PI acos(-1)
#define pll pair<ll,ll>


using namespace std ;
 
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
// #define cerr cout
namespace __DEBUG_UTIL__
{
    using namespace std;
    /* Primitive Datatypes Print */
    void print(const char *x) { cerr << x; }
    void print(bool x) { cerr << (x ? "T" : "F"); }
    void print(char x) { cerr << '\'' << x << '\''; }
    void print(signed short int x) { cerr << x; }
    void print(unsigned short int x) { cerr << x; }
    void print(signed int x) { cerr << x; }
    void print(unsigned int x) { cerr << x; }
    void print(signed long int x) { cerr << x; }
    void print(unsigned long int x) { cerr << x; }
    void print(signed long long int x) { cerr << x; }
    void print(unsigned long long int x) { cerr << x; }
    void print(float x) { cerr << x; }
    void print(double x) { cerr << x; }
    void print(long double x) { cerr << x; }
    void print(string x) { cerr << '\"' << x << '\"'; }
    template <size_t N>
    void print(bitset<N> x) { cerr << x; }
    void print(vector<bool> v)
    { /* Overloaded this because stl optimizes vector<bool> by using
          _Bit_reference instead of bool to conserve space. */
        int f = 0;
        cerr << '{';
        for (auto &&i : v)
            cerr << (f++ ? "," : "") << (i ? "T" : "F");
        cerr << "}";
    }
    /* Templates Declarations to support nested datatypes */
    template <typename T>
    void print(T &&x);
    template <typename T>
    void print(vector<vector<T> > mat);
    template <typename T, size_t N, size_t M>
    void print(T (&mat)[N][M]);
    template <typename F, typename S>
    void print(pair<F, S> x);
    template <typename... T>
    void print(priority_queue<T...> pq);
    template <typename T>
    void print(stack<T> st);
    template <typename T>
    void print(queue<T> q);
    /* Template Datatypes Definitions */
    template <typename T>
    void print(T &&x)
    {
        /*  This works for every container that supports range-based loop
            i.e. vector, set, map, oset, omap, dequeue */
        int f = 0;
        cerr << '{';
        for (auto &&i : x)
            cerr << (f++ ? "," : ""), print(i);
        cerr << "}";
    }
    template <typename T>
    void print(vector<vector<T> > mat)
    {
        int f = 0;
        cerr << "\n~~~~~\n";
        for (auto &&i : mat)
        {
            cerr << setw(2) << left << f++, print(i), cerr << "\n";
        }
        cerr << "~~~~~\n";
    }
    template <typename T, size_t N, size_t M>
    void print(T (&mat)[N][M])
    {
        int f = 0;
        cerr << "\n~~~~~\n";
        for (auto &&i : mat)
        {
            cerr << setw(2) << left << f++, print(i), cerr << "\n";
        }
        cerr << "~~~~~\n";
    }
    template <typename F, typename S>
    void print(pair<F, S> x)
    {
        cerr << '(';
        print(x.first);
        cerr << ',';
        print(x.second);
        cerr << ')';
    }
    template <typename... T>
    void print(priority_queue<T...> pq)
    {
        int f = 0;
        cerr << '{';
        while (!pq.empty())
            cerr << (f++ ? "," : ""), print(pq.top()), pq.pop();
        cerr << "}";
    }
    template <typename T>
    void print(stack<T> st)
    {
        int f = 0;
        cerr << '{';
        while (!st.empty())
            cerr << (f++ ? "," : ""), print(st.top()), st.pop();
        cerr << "}";
    }
    template <typename T>
    void print(queue<T> q)
    {
        int f = 0;
        cerr << '{';
        while (!q.empty())
            cerr << (f++ ? "," : ""), print(q.front()), q.pop();
        cerr << "}";
    }
    /* Printer functions */
    void printer(const char *) {} /* Base Recursive */
    template <typename T, typename... V>
    void printer(const char *names, T &&head, V &&...tail)
    {
        /* Using && to capture both lvalues and rvalues */
        int i = 0;
        for (size_t bracket = 0; names[i] != '\0' and (names[i] != ',' or bracket != 0); i++)
            if (names[i] == '(' or names[i] == '<' or names[i] == '{')
                bracket++;
            else if (names[i] == ')' or names[i] == '>' or names[i] == '}')
                bracket--;
        cerr.write(names, i) << " = ";
        print(head);
        if (sizeof...(tail))
            cerr << " ||", printer(names + i + 1, tail...);
        else
            cerr << "]\n";
    }
    /* PrinterArr */
    void printerArr(const char *) {} /* Base Recursive */
    template <typename T, typename... V>
    void printerArr(const char *names, T arr[], size_t N, V... tail)
    {
        size_t ind = 0;
        for (; names[ind] and names[ind] != ','; ind++)
            cerr << names[ind];
        for (ind++; names[ind] and names[ind] != ','; ind++)
            ;
        cerr << " = {";
        for (size_t i = 0; i < N; i++)
            cerr << (i ? "," : ""), print(arr[i]);
        cerr << "}";
        if (sizeof...(tail))
            cerr << " ||", printerArr(names + ind + 1, tail...);
        else
            cerr << "]\n";
    }
}
#ifndef ONLINE_JUDGE
#define debug(...) std::cerr << __LINE__ << ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
#define debugArr(...) std::cerr << __LINE__ << ": [", __DEBUG_UTIL__::printerArr(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#define debugArr(...)
#endif
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
    string s ; 
    cin >> s ; 
     
    string temple ="http://www.{word}.{word}/{word}/{word}?username={word}&pwd={word}&profile={word}&role={word}&key={word}" ; 

    map <string,string> m ;


    deque < char > dq ; 
    for(auto x : temple)
    {
        dq.push_back(x) ;
    }

    string curr = "" ;
    string curr2 = "" ;
    bool f = false ;
    for(auto x : s)
    {
        if(!dq.empty() && x == dq.front())
        {
            dq.pop_front() ;
            if(f)
            {
                m[curr] = curr2 ;
                curr = "" ;
                curr2 = "" ;
                f = false ;
            }
        }
        else 
        {
            if(x == '=')
            {
                f = true ;
            }
            else if(x == '&')
            {
                m[curr] = curr2 ;
                curr = "" ;
                curr2 = "" ;
                f = false ;
            }
            else 
            {
                if(f)
                {
                    curr2 += x ; 
                }
                else 
                {
                    curr += x ; 
                }
            }
        }
    }
    m[curr] = curr2 ;
    cout << "username:" << m["username"] << endl ;
    cout << "pwd:" << m["pwd"] << endl ;

    cout << "profile:" << m["profile"] << endl ;
    cout << "role:" << m["role"] << endl ;
    cout << "key:" << m["key"] << endl ;

    




    

    



    

}


signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //fill_fact(); 

    ll t ; 
    cin >> t ; 
    while(t--)
    {
        solve() ; 
    }
}
    
  