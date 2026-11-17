// orz
#include <bits/stdc++.h>

#define ll long long 
#define endl "\n"
#define fr first
#define sc second

#define MOD 998244353
#define INF 1e18
#define mp make_pair
#define PI acos(-1) 
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define pll pair<ll,ll>

using namespace std;
ll madd(ll a, ll b)
{
    return (a%MOD + b%MOD)%MOD ; 
}
ll msub(ll a, ll b)
{
    return (a%MOD - b%MOD + MOD)%MOD ; 
}
ll mmul(ll a , ll b)
{
    return ((a%MOD)*(b%MOD)%MOD);
}
void solve() 
{
    ll n;
    cin>>n;
    vector<ll> v(n);
    for(ll i=0;i<n;i++) cin>>v[i];
    vector<ll> pw(n+1);
    pw[0]=1;
    for(ll i=1;i<=n;i++) pw[i]=mmul(pw[i-1],2);
    ll ans=0;
    for(ll i=0;i<n;i++)
    {
       ans=madd(ans,mmul(v[i],pw[i]));
       for(ll j=i+1;j<n;j++)
       {
            if(v[i]>v[j])
            {
                //cout<<mmul(pw[i],pw[n-1-j])<<endl;
                ans=madd(ans,mmul(v[i]-v[j],mmul(pw[i],pw[n-1-j])));
            }
       }



    
    }
    cout<<ans<<endl;
    
    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t;
    cin>>t;
    while(t--)  solve();
}
    
  