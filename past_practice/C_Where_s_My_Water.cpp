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

void solve() 
{
    ll n,h;cin>>n>>h;
    
    deque<ll>a(n+1);
    for(ll i=1;i<=n;i++)cin>>a[i];
    
    deque<ll>p(n+1,0),s(n+2,0);
    deque<ll>v(n+1,0),sm(n+1,0);
    
    for(ll d=1;d<=n;d++)
    {
        ll mx=a[d];
        
        for(ll i=d;i>=1;i--)
        {
            if(a[i]>mx)mx=a[i];
            v[i]=h>mx?h-mx:0;
        }
        
        mx=a[d];
        for(ll i=d  ;i<=n;i++)
        {
            if(a[i]>mx)mx=a[i];
            v[i]=h>mx?h-mx:0;
        }
        
        if(!sm.empty())sm[0]=0;
        for(ll i=1;i<=n;i++)sm[i]=sm[i-1]+v[i];
        
        for(ll k=d;k<=n;k++)
        {
            if(sm[k]>p[k])p[k]=sm[k];
        }
        
        for(ll k=1;k<=d;k++)
        {
            ll x=sm[n]-sm[k-1];
            if(x>s[k])s[k]=x;
        }
    }
    
    ll ans=p[n];
    
    for(ll k=1;k<n;k++)
    {
        ll cur=p[k]+s[k+1];
        if(cur>ans)ans=cur;
    }
    
    cout<<ans<<endl;
}

signed main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t;cin>>t;
    for(ll i=1;i<=t;i++)solve();
}