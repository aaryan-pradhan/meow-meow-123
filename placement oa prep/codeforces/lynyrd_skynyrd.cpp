
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m, q; cin >> n >> m >> q;
    vector<int> p(n), nx(n + 1);
    for (int &x : p)
    {
        cin >> x;
    }
    for (int i = 0; i < n; i++)
    {
        nx[p[i]] = p[(i + 1) % n];
    }
    vector<int> a(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> a[i];
    }
    vector<vector<int>> up(18, vector<int>(m + 2, m + 1));
    vector<int> last(n + 1, m + 1);
    for (int i = m; i >= 1; i--)
    {
        up[0][i] = last[nx[a[i]]];
        last[a[i]] = i;
    }
    for (int k = 1; k < 18; k++)
    {
        for (int i = 1; i <= m + 1; i++)
        {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }
    vector<int> best(m + 2, m + 1);
    for (int i = m; i >= 1; i--)
    {
        int j = i;
        for (int k = 0; k < 18; k++)
        {
            if ((n - 1) >> k & 1)
            {
                j = up[k][j];
            }
        }
        best[i] = min(best[i + 1], j);
    }
    string ans;
    while (q--)
    {
        int l, r; cin >> l >> r;
        ans += best[l] <= r ? '1' : '0';
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
