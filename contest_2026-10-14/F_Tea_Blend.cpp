// orz
#include <bits/stdc++.h>

#define ll long long 
#define endl "\n"

using namespace std;

const ll MAX = 1e6 + 5;
ll spf[MAX];

void sieve() {
    for (ll i = 2; i < MAX; i++) {
        if (spf[i] == 0) {
            for (ll j = i; j < MAX; j += i) {
                if (spf[j] == 0) {
                    spf[j] = i;
                }
            }
        }
    }
}


vector<ll> gop(ll x) 
{
    vector<ll> op ; 
    while (x > 1) 
    {
        ll p = spf[x];
        ll  count = 0;
        while (x % p == 0) {
            count++;
            x /= p;
        }
        if (count % 2 == 1) {
            op.push_back(p);
        }
    }
    return op;
}

void solve() 
{
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) 
    {
        cin >> a[i];
    }

    
    map < vector<ll>, ll > freq;
    vector < vector < ll > > graph ; 
    graph.assign(n+1, vector < ll > () ) ;
    for (ll i = 0; i < n; i++) 
    {
        graph[i] = gop(a[i]);
        freq[graph[i]]++;
    }


    set<ll> ap ; 
    ll tp = 0 ; 
    for (ll j = 0; j < n; j++) 
    {

        for (ll p : graph[j]) 
        {
            if (ap.count(p)) 
            {
                ap.erase(p); 
            }
            else
            {
                ap.insert(p); // odd power now, add
            }
        }

        if (ap.empty()) 
        {
            tp += freq[graph[j]]; 
        }

        
    }

    cout << tp << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    ll t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}