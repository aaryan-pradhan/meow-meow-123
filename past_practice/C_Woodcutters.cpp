// or
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
#define pll pair<ll,bool>

using namespace std;

ll n ; 
vector < ll >  x ; 
vector < ll > h ; 
vector < vector < ll >> dp ;
ll rec(ll i , ll ch)
{

    if(i == n )
    {
        dp[i][ch] = 1;
        return dp[i][ch];
    }

    if(dp[i][ch] != -1)
        return dp[i][ch];
    ll ans=0;
    if(ch==0)
    {
        ll space=(x[i+1]-x[i]);
        if(space>h[i])
        {
            ans=1+rec(i+1,2);
        }
        space=(x[i]-x[i-1]);
        if(space>h[i])
        {
            ans=max(ans,1+rec(i+1,1));
        }
        ans=max(ans,rec(i+1,0));
    }
    else if(ch==1)
    {
        ll space=(x[i+1]-x[i]);
        if(space>h[i])
        {
            ans=1+rec(i+1,2);
        }
        space=(x[i]-x[i-1]);
        if(space>h[i])
        {
            ans=max(ans,1+rec(i+1,1));
        }
        ans=max(ans,rec(i+1,0));
    }
    else if(ch==2) 
    {
        ll space=(x[i+1]-x[i]);
        if(space>h[i])
        {
            ans=1+rec(i+1,2);
        }
        space=(x[i]-(x[i-1]+h[i-1]));
        if(space>h[i])
        {
            ans=max(ans,1+rec(i+1,1));
        }
        ans=max(ans,rec(i+1,0));
    }
    
    return dp[i][ch]=ans;

    
}
void solve() 
{
    cin >> n ; 
    x.assign(n+1,0) ; 
    h.assign(n+1,0) ;
    dp.assign(n+1,vector<ll>(3,-1)) ;


    x[0] = -INF ; 
    for(ll i = 1 ; i <= n ; i++)
        cin >> x[i] >> h[i];

    cout << max(max(rec(1,0),rec(1,1)),rec(1,2)) << endl;

    

    
   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}