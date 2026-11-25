#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Solution
{
public:
    int trap(vector<int>& height)
    {
        ll n = height.size();
        vector<ll> h(height.begin(), height.end());

        vector<ll> dp1(n, 0);
        dp1[0] = h[0];
        for (ll i = 1; i < n; i++)
        {
            dp1[i] = max(h[i], dp1[i - 1]);
        }

        vector<ll> dp2(n, 0);
        dp2[n - 1] = h[n - 1];
        for (ll i = n - 2; i >= 0; i--)
        {
            dp2[i] = max(h[i], dp2[i + 1]);
        }

        ll ans = 0;
        for (ll i = 1; i < n - 1; i++)
        {
            ll water = min(dp1[i - 1], dp2[i + 1]) - h[i];
            if (water < 0)
            {
                water = 0;
            }
            ans += water;
        }
        return ans;
    }
};
