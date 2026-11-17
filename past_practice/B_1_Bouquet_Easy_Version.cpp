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
    
   ll n, m;
   cin >> n >> m;
   map <ll ,ll> freq;
   for( ll i = 0;i<n; i++ )
   {
        ll a;
        cin >> a;
        freq[a]++;
   }

   vector< pll > v;
   for (auto i: freq)
   {
        v.push_back(i);


    
   }
    ll k= v.size();
    ll ans  = 0;
    for (ll i = 0;i < k;i++)
    {
        ll x = v[i].fr;
        ll cx = v[i].sc;
        ll tx = min(cx,m/x);

        ans = max(ans,tx*tx);
        if(i+1< k && v[i+1].fr == x+1)
        {
            ll y = v[i+1].fr;
            ll cy = v[i+1].sc;

            ll ty= min(cy,(m-tx*tx)/y);
            ll sum=tx*x+ty*y;
            ll rem= m-sum;
            
            ll add = min({tx,cy-ty, rem});
            ans = max(ans, sum + add);
        }
    }
    cout << ans << endl  ;









}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t; 
    while(t--)
    {
        solve(); 
    }
}
    
  