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
    ll n,k;
    cin>>n>>k;
    vector<vector<ll>> dp(n+1,vector<ll> (2,0));
    for(ll i=0;i<=n;i++)
    {
        if(i==0)
        {
            dp[i][0]=1;
            dp[i][1]=1;
            continue;
        }
        ll ans=0;
        for(ll j=1;j<=i;j++)
        {
            if(j+k<=i)
            {
                ans=madd(ans,dp[j-1][1]);
            }
            else{
                ans=madd(ans,dp[j-1][0]);
            }
        }
        dp[i][0]=ans;
        dp[i][1]=madd(ans,ans);
    }
    cout<<dp[n][0]<<endl;
   






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
        solve();
    }
}
    
  