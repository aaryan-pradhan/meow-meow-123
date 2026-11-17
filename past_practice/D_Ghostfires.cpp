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
    ll r , g, b;
    cin >> r >> g >> b;
    
    vector <pair <ll, char>> v = {{r, 'R'}, {g, 'G'}, {b, 'B'}};
    sort(v.rbegin(), v.rend()); 
    
    if (v[0].fr > v[1].fr + v[2].fr) 
    {
        string ans = "";
        vector <char> rem;

        for(ll i = 0; i < v[1].fr; i++) 
            rem.push_back(v[1].sc);

        for(ll i = 0; i < v[2].fr; i++) 
            rem.push_back(v[2].sc);
        
        for(size_t i = 0; i < rem.size(); i++) 
        {
            ans += v[0].sc;
            ans += rem[i];
        }

        ans += v[0].sc;
        cout << ans << endl;
        return;
    }
    
    ll t = r + g + b;
    string ans = "";
    

    vector <vector < ll >> perms = { {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0} };
    
    if (t % 2 == 0) 
    {
        for (auto p : perms) 
        {
            ll A_cnt = v[p[0]].fr, B_cnt = v[p[1]].fr, C_cnt = v[p[2]].fr;
            char A_char = v[p[0]].sc, B_char = v[p[1]].sc, C_char = v[p[2]].sc;
            
            ll x = A_cnt + B_cnt - C_cnt;
            ll y = B_cnt + C_cnt - A_cnt;
            ll z = C_cnt + A_cnt - B_cnt;
            
            if (x >= 0 && y >= 0 && z >= 0 && x % 2 == 0 && y % 2 == 0 && z % 2 == 0) 
            {
                x /= 2; y /= 2; z /= 2;
                string S = "";
                for(ll i = 0; i < x; i++) 
                {
                    S += A_char; 
                    S += B_char; 
                }
                for(ll i = 0; i < y; i++) 
                {
                    S += C_char; 
                    S += B_char; 
                }
                for(ll i = 0; i < z; i++) 
                { 
                    S += C_char; 
                    S += A_char; 
                }

                bool valid_S = true;
                for (int i = 0; i + 3 < (int)S.size(); i++) 
                {
                    if (S[i] == S[i + 3]) 
                    {
                        valid_S = false;
                        break;
                    }
                }
                
                if (!valid_S) 
                    continue;

                ans = S;
                break;
            }
        }
    } 
    else 
    {
        bool found = false;
        for(int sub = 0; sub < 3 && !found; sub++) 
        {
            if (v[sub].fr == 0) 
                continue;
            
            vector < pair<ll, char>> cur_v = v;
            cur_v[sub].fr--;
            char add = cur_v[sub].sc;
            
            for (auto p : perms) 
            {
                ll A_cnt = cur_v[p[0]].fr, B_cnt = cur_v[p[1]].fr, C_cnt = cur_v[p[2]].fr;
                char A_char = cur_v[p[0]].sc, B_char = cur_v[p[1]].sc, C_char = cur_v[p[2]].sc;
                
                ll x = A_cnt + B_cnt - C_cnt;
                ll y = B_cnt + C_cnt - A_cnt;
                ll z = C_cnt + A_cnt - B_cnt;
                
                if (x >= 0 && y >= 0 && z >= 0 && x % 2 == 0 && y % 2 == 0 && z % 2 == 0) 
                {
                    x /= 2; y /= 2; z /= 2;
                    string S = "";
                    for(ll i = 0; i < x; i++) 
                    { 
                        S += A_char; 
                        S += B_char; 
                    }
                    for(ll i = 0; i < y; i++) 
                    { 
                        S += C_char; 
                        S += B_char; 
                    }
                    for(ll i = 0; i < z; i++) 
                    { 
                        S += C_char; 
                        S += A_char; 
                    }
                    
                 
                    bool valid_S = true;
                    for (int i = 0; i + 3 < (int)S.size(); i++) 
                    {
                        if (S[i] == S[i + 3]) 
                        {
                            valid_S = false;
                            break;
                        }
                    }
                    
                    if (!valid_S) 
                        continue; 
                    
                    bool ok1 = true;

                    if (S.size() >= 1 && S.back() == add) 
                        ok1 = false;
                    if (S.size() >= 3 && S[S.size()-3] == add) 
                        ok1 = false;
                    
                    if (ok1) 
                    {
                        ans = S + add;
                        found = true;
                        break;
                    }
                    
                    bool ok2 = true;
                    if (S.size() >= 1 && S[0] == add) 
                        ok2 = false;
                    if (S.size() >= 3 && S[2] == add) 
                        ok2 = false;
                    
                    if (ok2) 
                    {
                        ans = add + S;
                        found = true;
                        break;
                    }
                }
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
 
    ll t; 
    cin >> t; 
    for(ll i = 0; i < t; i++)
    {
        solve();
    }
}