/*
Problem Statement 3 — Harness 2026 IIT Roorkee (2 DSA questions and 10 MCQs on CS fundamentals)

You are given an array a of n distinct positive integers and an integer q,
representing the number of queries.

Each query consists of an integer x. For each query, perform a left circular
shift of the array by x positions and determine the position of the maximum
element in the resulting array.

// 1 2 5 4 3 ; q = 5 
// 3 
// 2 5 4 3 1 
// 5 4 3 1 2 
// 4 3 1 2 5 
// 5

A left circular shift moves the first x elements to the end of the array while
preserving their relative order.

Since the array contains distinct elements, its maximum element occurs at
exactly one position.

Input Format
- The first line contains two integers, n and q, representing the size of the
  array and the number of queries, respectively.
- The second line contains n distinct positive integers representing the
  array a.
- The next q lines each contain an integer x, representing the number of
  positions to shift the array to the left.

Output Format
For each query, print the 1-based position of the maximum element after
performing the specified left circular shift.

Constraints
- 1 <= n, q <= 10^5
- 1 <= a_i <= 10^9
- All elements of a are distinct.
- 0 <= x <= 10^9

Note: Since the shift is circular, shifting by x positions is equivalent to
shifting by (x mod n) positions.
*/

#include <bits/stdc++.h>

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
    ll n , q ; 
    cin >> n >> q; 
    ll maxi , midx ; 
    maxi = -INF ; 
    midx = -1 ; 
    vector < ll > a(n+1 , 0) ; 
    for(ll i = 1 ; i <= n ; i++)
    {
      cin >> a[i] ; 
      if(a[i] > maxi)
      {
        maxi = max(maxi, a[i]);  
        midx = i ; 
      }
    }
    ll k = midx ; 
    vector < ll > ans ; 
    while(q--)
    {
      ll x ; 
      cin >> x ; 
    
      // after one x circular shift is identical to x%n circular shift 
      x = x % n ; 
      // if max is at k then after x circular shift the postion is k - x if k > x 
      if(k > x )
      {
        ans.push_back( k - x ) ; 
      }
      else
      {
        // if x is more than k then it goes all the way to the beginning and then it moves ahead 
        // first shift to 1 that takes 
        ll takes = k -1 ; 
        // noe 
        ll left = x - takes ; 
        ll idx = n ; 
        left-- ; 
        ans.push_back(idx - left) ; 

      

      }
      k = midx ; 

      
    }
    for(auto &x : ans)
    {
      cout << x << endl ; 
    }

}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
}
