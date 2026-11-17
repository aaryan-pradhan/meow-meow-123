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
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n),c(n);
    for( ll i=0;i<n;i++) cin>>a[i];
    for(ll i = 0;i<n;i++) cin>>c[i];
    map<ll, ll> freq;
    for( ll i = 0;i<n;i ++)
    {
        freq[a[i]]+=c[i];
    }
    vector< pll > v;
    for( auto it : freq)
    {
        v.push_back(it);
    }

    ll sz=v.size();
    ll ans=0;
    for(ll i=0;i<sz;i++){
        ll k=v[i].fr;
        ll x = min(v[i].sc,m/k);
        ans= max(ans, x*k);
        if(i+1<sz && v[i+1].fr == k+1)
        {
            ll rem= m-x*k;
            ll y=min(v[i+1].sc,rem/(k+1));
            ll cost=x*k+y*(k+1);
            ll sw=min({x,v[i+1].sc-y,m-cost});
            ans=max(ans,cost+sw);
        }
    }
    cout<<ans<<endl;
    
   






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
    
  