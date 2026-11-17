/*
Problem 1 - Repeated String Cover
Source: Harness 2026 OA, IIT Roorkee (2 DSA + 10 CS-fundamentals MCQs)

You are given an integer n and a string data consisting only of lowercase
English letters ('a'-'z').

Construct a string s of length exactly n such that, when s is concatenated
with itself repeatedly the minimum number of times necessary to obtain a
string whose length is at least |data|, the resulting string contains at
least as many occurrences of each character as data does.

If multiple strings satisfy these conditions, output the lexicographically
smallest valid string s.

Input Format
- The first line contains an integer n, the required length of the string.
- The second line contains the string data.

Output Format
Print the lexicographically smallest valid string of length exactly n.
Otherwise print "-1".

Constraints
1 <= n <= 10^5
1 <= |data| <= 10^5
data contains only lowercase English letters ('a'-'z').
*/

#include <bits/stdc++.h>

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
ll ceil(ll a , ll b)
{
    if(a%b)
    {
        return a / b + 1 ; 
    }
    else 
    {
        return a / b ; 
    }
}
void solve()
{
    ll n ; 
    cin >> n ; 
    string d ; 
    cin >> d ; 
    ll ds = d.length() ; 
    vector < char > data ; 
    vector < ll > fd(26,0) ; 
    for(ll i = 0 ; i < ds ; i++)
    {
        fd[d[i]-'a']++ ; 
        data.push_back(d[i]) ; 
    }
    string ans ; 
    if ( n > ds)
    {
        ll left = n - ds ; 
        for(ll i = 0 ; i < left ; i++)
        {
            ans += 'a' ; 
        }
        sort(data.rbegin() , data.rend()) ; 
        while(!data.empty())
        {
            ans += data.back() ; 
            data.pop_back() ;
        }
    }
    else
    {
        ll x = ceil(ds , n) ; 
        ll tn = 0 ; 
        vector < ll > need(26,0) ; 
        for(ll i = 0 ; i < 26 ; i++)
        {
            need[i] = ceil(fd[i] , x) ; 
            tn += need[i] ; 
        }
        if ( tn > n)
        {
            ans = "-1" ; 
        }
        else 
        {
            ll left = n - tn ; 
            ll i = 0 ; 
            for(; i < left ; i++)
            {
                ans += 'a' ; 
            }
            for(ll i = 0 ; i < 26 ; i++)
            {
                while(need[i]!=0)
                {
                    ans += 'a' + i ; 
                    need[i]-- ; 
                }
            }

        }
        

    }
    cout << ans << endl ; 

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
}
