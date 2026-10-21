/*
Problem 2 - Train and Execute Algorithms
Source: Harness 2026 OA, IIT Roorkee

You are given an n x m matrix executionDays, where executionDays[i][j]
represents a day on which the i-th algorithm can be executed.

You are also given an array trainingTime of length n, where trainingTime[i]
denotes the number of days required to train the i-th algorithm before it
can be executed.

Each day, you can perform at most one of the following actions:
1. Train an algorithm: Spend one day training an algorithm. Training an
   algorithm requires trainingTime[i] days in total.
2. Execute an algorithm: Execute an algorithm that has already completed its
   training, provided that the execution can take place on that day.
3. Do nothing: Leave the day unused.

An algorithm can be executed only after its training is complete, and it must
be executed on one of the days specified for it in executionDays.

Your task is to determine the minimum number of days required to train and
execute all n algorithms. If it is impossible to execute all algorithms while
satisfying the given constraints, print -1.

Input Format
- The first line contains two integers, n and m, representing the number of
  algorithms and the number of possible execution days listed for each
  algorithm.
- The next n lines contcaain m integers each, representing the matrix
  executionDays.
- The next line contains n integers representing the array trainingTime.

Output Format
Print a single integer representing the minimum number of days required to
train and execute all algorithms, or -1 if it is impossible.

Constraints
1 <= executionDays[i][j] <= 10^9
1 <= n, m <= 10^5
1 <= n * m <= 10^5
1 <= trainingTime[i] <= 10^9
Note: all executionDays[i][j] are distinct.
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

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
}
