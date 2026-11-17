/*
Problem Statement 4 — Harness 2026 IIT Roorkee (2 DSA questions and 10 MCQs on CS fundamentals)

You are given an array a of n positive integers. Initially, a variable p is
set to 1.

For each element a_i of the array, you must choose exactly one of the following
four operations:
1. Do nothing: Leave p unchanged.
2. Multiply: Update p to p x a_i.
3. Divide: Update p to p / a_i.
4. Both: Perform both the multiplication and division operations, leaving p
   unchanged.

After processing all n elements, you obtain a final value of p.

You are given q queries. Each query contains a target integer t. For each
query, determine the number of ways to perform the operations such that the
final value of p is equal to t.

Since the answer can be large, output it modulo 10^9 + 7.

Two ways are considered different if they involve different choices of
operations for at least one array element.

Input Format
- The first line contains two integers, n and q, representing the size of the
  array and the number of queries.
- The second line contains n integers representing the array a.
- The next q lines each contain an integer t, representing the target value
  for that query.

Output Format
For each query, print the number of ways to obtain the corresponding target
value t, modulo 10^9 + 7.

Constraints
- 1 <= n <= 19
- 1 <= q <= 5
- 1 <= a_i <= 6
- 1 <= t <= 10^15

Clarification needed: The statement should specify whether division is
performed using ordinary real-number arithmetic or whether p must remain an
integer after every operation. This distinction can change the answer
significantly. Also, since operations 1 and 4
[statement truncated in source]
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
ll madd( ll a , ll b)
{
   return (a%MOD + b%MOD)%MOD ; 
}
ll mmul(ll a , ll b)
{
  return (a%MOD * b%MOD)%MOD ; 
}
ll a[20] ; 
ll dp[20][81][41][41] ; // offsets: e2 in [-40,40], e3/e5 in [-20,20]
ll n , q ; 
array < ll , 3 > b(ll x )
{
  array < ll , 3 > ans = {0,0,0} ; 
  while(x%2==0)
  {
    if(x%2==0)
    {
      x/=2 ; 
      ans[0]++ ; 
    }
  }
  while(x%3==0)
  {
    if(x%3==0)
    {
      ans[1]++ ; 
      x/=3 ; 
    }

  }
  while(x%5==0)
  {
    if(x%5==0)
    {
      ans[2]++ ; 
      x/=5 ; 
    }
  }
  if(x != 1) ans[0] = 1000 ;
  return ans ;

}
ll rec(ll i , ll e2 , ll e3 ,ll e5)
{
  // can't get back to 0 with n-i elements left (each moves e2 by <= 2, e3/e5 by <= 1)
  if(abs(e2) > 2*(n-i) || abs(e3) > n-i || abs(e5) > n-i)
  {
    return 0 ; 
  }
  if(i==n)
  {
    if(e2 == 0 && e3 == 0 && e5 == 0){
      return 1 ; 
    }
    else 
    {
      return 0; 
    }
  }
  if(dp[i][e2+40][e3+20][e5+20] != -1)
  {
    return dp[i][e2+40][e3+20][e5+20] ; 
  }
  ll res = 0 ;  
  array < ll , 3 > ans = b(a[i]) ; 
  res = madd( res ,rec( i + 1 , e2 + ans[0] , e3 + ans[1], e5 + ans[2]) ) ; 
  res = madd ( res , rec( i + 1 , e2 - ans[0] , e3 - ans[1], e5 - ans[2]) ) ; 
  res = madd( res ,mmul( 2 , rec( i + 1 , e2  , e3 , e5 )) ) ; 
  return dp[i][e2+40][e3+20][e5+20] = res ; 

}
void solve()
{
  cin >> n >> q ; 
  memset(a, 0 , sizeof(a)) ; 
  for(ll i = 0 ; i < n ; i++)
  {
    cin >> a[i] ; 
  }
  memset(dp , -1 , sizeof(dp)) ; 
  while(q--)
  {
    ll t ; 
    cin >> t ; 
    array <ll , 3 > sol = b(t) ; 
    cout << rec(0 , sol[0] , sol[1] , sol[2]) << endl ; 


  }

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
}
