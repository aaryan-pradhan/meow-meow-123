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
#define int long long

const int M = 1e9 + 7;

int madd(int a, int b)
{
    return (a % M + b % M) % M;
}
int mmul(int a, int b)
{
    return (a % M) * (b % M) % M;
}

long long sumOfPeakMemory(const vector<long long>& m)
{
    int n = m.size(), ans = 0;
    vector<int> L(n, -1), R(n, n);
    stack<int> st;
    for (int k = 0; k < n; k++)
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
    st = stack<int>();
    for (int k = n - 1; k >= 0; k--)
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
    for (int k = 0; k < n; k++)
    {
        ans = madd(ans, mmul(m[k], mmul(k - L[k], R[k] - k)));
    }
    return ans;
}

#undef int
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    vector<long long> m(n);
    for (int i = 0; i < n; i++) scanf("%lld", &m[i]);
    printf("%lld\n", sumOfPeakMemory(m));
    return 0;
}
