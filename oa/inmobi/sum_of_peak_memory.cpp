/*
 * Sum of Peak Memory — InMobi OA
 *
 * Given N memory readings m[0..N-1], return the sum of max(m[i..j]) over all
 * windows 0 <= i <= j < N, modulo 10^9 + 7.
 *
 * Input : N, then N readings
 * Output: the sum mod 10^9 + 7
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll M = 1e9 + 7;

ll madd(ll a, ll b)
{
    return (a % M + b % M) % M;
}
ll mmul(ll a, ll b)
{
    return (a % M) * (b % M) % M;
}

long long sumOfPeakMemory(const vector<long long>& m)
{
    ll n = m.size(), ans = 0;
    vector<ll> L(n, -1), R(n, n);
    stack<ll> st;
    for (ll k = 0; k < n; k++)
    {
        while (!st.empty() && m[st.top()] < m[k])
        {
            st.pop();
        }
        if (!st.empty())
        {
            L[k] = st.top();
        }
        st.push(k);
    }
    st = stack<ll>();
    for (ll k = n - 1; k >= 0; k--)
    {
        while (!st.empty() && m[st.top()] <= m[k])
        {
            st.pop();
        }
        if (!st.empty())
        {
            R[k] = st.top();
        }
        st.push(k);
    }
    for (ll k = 0; k < n; k++)
    {
        ans = madd(ans, mmul(m[k], mmul(k - L[k], R[k] - k)));
    }
    return ans;
}

signed main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0;
    vector<ll> m(n);
    for (ll i = 0; i < n; i++) scanf("%lld", &m[i]);
    printf("%lld\n", sumOfPeakMemory(m));
    return 0;
}
