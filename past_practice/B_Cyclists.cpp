// orz
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
    ll n, k, p, m;
    cin >> n >> k >> p >> m;
    
    deque <pair<ll, bool> > dq;
    for(ll i = 0; i < n; i++) 
    {
        ll a;
        cin >> a;
        if( i == p-1 ) 
        {
            dq.push_back({a, true}); 
        } 
        else 
        {
            dq.push_back({a, false});
        }
    }
    
    ll ans = 0;
    
    while(true) 
    {
        ll limit = min((ll)dq.size(), k);
        bool fnd = false;
        ll tidx = -1;
        
        for(ll i = 0; i < limit; i++) 
        {
            if(dq[i].second) 
            {
                fnd = true;
                tidx = i;
                break;
            }
        }
        
        if(fnd) 
        {

            ll cost = dq[tidx].first;
            if(m >= cost) 
            {
                m -= cost;
                ans++;
                auto c = dq[tidx];
                dq.erase(dq.begin() + tidx);
                dq.push_back(c);
            } 
            else 
            {
                break; 
            }
        } 
        else 
        {
            
            ll mn = INF;
            ll midx = -1;
            for(ll i = 0; i < limit; i++) 
            {
                if(dq[i].first < mn) 
                {
                    mn = dq[i].first;
                    midx = i;
                }
            }
            
            if(m >= mn) 
            {
                m -= mn;
                auto c = dq[midx];
                dq.erase(dq.begin() + midx);
                dq.push_back(c);
            } 
            else 
            {
                break; 
            }
        }
    }
    
    cout << ans << endl;
}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t ; 
    cin >> t ; 
    for(ll i = 0 ; i < t ; i++)
    {
        solve() ;
    }
}