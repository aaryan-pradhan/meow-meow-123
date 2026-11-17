/*
 * Safe Deployment Order — Houlihan Lokey OA (oahelper, 15 Oct)
 *
 * Input : n m, then m lines "u v"
 * Output: the order, space-separated on one line, or "DEADLOCK" if no valid order exists.
 */
#include <bits/stdc++.h>
using namespace std;

/*
 * n            : number of microservices, labelled 0 .. n-1
 * dependencies : list of (u, v) pairs meaning u must be deployed before v
 *
 * Return the lexicographically smallest valid deployment order, or an empty
 * vector if the dependencies contain a cycle.
 */
vector<int> deploymentOrder(int n, const vector<pair<int,int> >& d) {
    vector < vector < int > > g(n) ; 
    vector < int > ind(n) , ans ; 
    for(auto [u , v] : d)
    {
        g[u].push_back(v) ; 
        ind[v]++ ; 
    }
    priority_queue < int , vector < int >  , greater < int > > pq ; 
    for(int i = 0 ; i < n ; i++)
    {
        if(ind[i] == 0 )
        {
            pq.push(i) ;
        }
    }
    while(!pq.empty())
    {
        int n = pq.top() ; 
        pq.pop() ; 
    
        for(auto ch : g[n])
        {
            if(ind[ch] == 0)
            {
                pq.push(ch) ; 
                ind[ch]-- ; 
            }
        }     
    }
    if ( ans.size() < n
    {
        return {} ; 
    }
    return ans ; 
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    vector<pair<int,int> > dependencies;
    dependencies.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        dependencies.push_back(make_pair(u, v));
    }

    vector<int> order = deploymentOrder(n, dependencies);
    if (order.empty()) {
        printf("DEADLOCK\n");
    } else {
        string out;
        char buf[16];
        for (size_t i = 0; i < order.size(); ++i) {
            if (i) out.push_back(' ');
            int len = snprintf(buf, sizeof(buf), "%d", order[i]);
            out.append(buf, len);
        }
        out.push_back('\n');
        fwrite(out.data(), 1, out.size(), stdout);
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

void solve()
{
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto &v : a)
    {
        for (int &x : v)
        {
            cin >> x;
        }
    }
    int c = n / 2, k = n > 9 ? 2 : 1, x = a[c][c];
    vector<int> b;
    for (int i = c - k; i <= c + k; i++)
    {
        for (int j = c - k; j <= c + k; j++)
        {
            b.push_back(i == c && j == c ? 0 : a[i][j] + x);
        }
    }
    sort(all(b), greater<int>());
    int m = b.size() / 2;
    for (int i = 0; i <= m; i++)
    {
        int l = b[m - i], r = b[m + i];
        cout << l;
        for (int j = 1; j < i; j++)
        {
            cout << " " << (j % 2 ? l - r : l + r);
        }
        if (i)
        {
            cout << " " << r;
        }
        cout << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}