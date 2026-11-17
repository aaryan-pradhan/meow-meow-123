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


const ll MAXN = 1000005;
ll  z[MAXN];
ll mr[MAXN];

ll n, q;
string s;
vector<ll> dp; 

void solve() 
{
    
    cin >> n >> q;
    cin >> s;
    
    while (q--) 
    {
        ll l, r;
        cin >> l >> r;
        l--; r--; 
        ll m = r - l + 1;
        
        dp.assign(m, 0); 
        
        z[0] = 0;
        ll L_z = 0, R_z = 0;
        for (ll i = 1; i < m; i++) 
        {
            z[i] = 0;
            if (i <= R_z) z[i] = min(R_z - i + 1, z[i - L_z]);
            
            while (i + z[i] < m && s[l + z[i]] == s[l + i + z[i]]) 
            {
                z[i]++;
            }
            
            if (i + z[i] - 1 > R_z) 
            {
                L_z = i;
                R_z = i + z[i] - 1;
            }
        }
        

        for (ll i = 0; i <= m + 1; i++) 
        {
            mr[i] = 0;
        }
        
        mr[1] = m + 5; 
        ll mve = 1;
        ll res = 0;
        

        for (ll j = 0; j < m; j++) 
        {
            
            while (mve > 1 && mr[mve] <= j) 
            {
                mve--;
            }
            
            dp[j] = mve; 
            res += dp[j];
            

            int i = j + 1;
            if (i < m && z[i] > 0) 
            {
                int v = dp[j] + 1; 
                
                if (i + z[i] > mr[v]) 
                {
                    mr[v] = i + z[i];
                }
                
                if (v > mve) 
                {
                    mve = v;
                }
            }
        }
        
        cout << res << endl;
    }

}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll t; 
    cin >> t; 
    for(ll i = 0; i < t; i++)
    {
        solve();
    }
}