#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Solution
{
public:
    int jump(vector<int>& a)
    {
        ll n = a.size();
        vector<vector<array<ll, 2>>> g(n);
        for (ll u = 0; u < n; u++)
        {
            g[u].push_back({1, min(n - 1, u + a[u])});
            if (u > 0)
            {
                g[u].push_back({0, u - 1});
            }
        }
        vector<ll> dist(n, LLONG_MAX);
        deque<ll> qu;
        dist[0] = 0; qu.push_back(0);
        while (!qu.empty())
        {
            ll u = qu.front(); qu.pop_front();
            for (auto [w, v] : g[u])
            {
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    if (w == 0)
                    {
                        qu.push_front(v);
                    }
                    else
                    {
                        qu.push_back(v);
                    }
                }
            }
        }
        return dist[n - 1];
    }
};
