// orz
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

void solve() 
{
    ll n ; 
    cin >> n ; 
    string s ; 
    cin >> s ; 
    s = 'S' + s ; 
    vector < bool > a(n+1, false) ; 
    deque < ll > m ; 
    ll cnt = 0 ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        if(s[i]=='1')
        {
            m.push_front(i) ; 
        }
        else if(s[i] == '2')
        {
            if(!m.empty())
            {   
                a[m.front()] = true ; 
                m.pop_front() ; 
                cnt++ ; 
            }
            else
            {
                a[i] = true ; 
                cnt++ ; 
            }
        }
        else if(s[i] == '3')
        {
            a[i] = true ; 
            cnt++ ; 
        }
    }
    cout << n - cnt << endl ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        if(a[i] == false)
        {
            cout << i << " " ; 
        }
    }
    cout << endl ; 
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ;
    cin >> t ;
    while(t--)
    {
        solve() ; 
    }
}
    
  