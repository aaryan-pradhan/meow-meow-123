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
    ll n;
    cin>>n;
    vector < ll > v(n + 1 ); 
    vector<ll> s(1,0);
    for(ll i=1;i<=n;i++)
    {
        cin>>v[i];
        if(v[i]!=i)
        {
            s.push_back(i);
        }


    }
   
    ll k=s.size()-1;
    bool ok=true;
    for(ll i=1;i<=k;i++)
    {
        if(v[s[i]]!=s[k-i+1])
        {
            ok=false;
        }

    }

    if(ok)
    {
        py ; 
    }
    else 
    {
        pn ;
    }





}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t;
    cin >> t ;
    while(t--)
    {
        solve() ; 
    }
}
    
  