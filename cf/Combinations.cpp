// orz
// 77. Combinations · LeetCode · Medium
//
// Question:
// given two integers n and k, return all possible combinations of k numbers chosen
// from the range [1, n]. the answer can be in any order.
// Example 1: n = 4, k = 2 -> [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
// Example 2: n = 1, k = 1 -> [[1]]
// Constraints: 1 <= n <= 20, 1 <= k <= n.
//
// 1. Mathematical statement
//    return every set S with S a subset of {1 .. n} and |S| = k, each written in increasing order.
//
// 2. Brute force
//    go over all 2^n masks, keep the ones with exactly k bits set.
//    2^20 = 10^6 masks * 20 bits. it passes, but most masks have the wrong size.
//
// 3. What the brute force wastes
//    it keeps building a subset after it already has k numbers, and it builds every
//    mask in full only to throw it away at the end.
//
// 4. Key breaking point
//    this is my Apple Division rec: for each number, take it or skip it.
//    stop as soon as cur has k numbers, so no subset ever grows past k.
//
// 5. Method
//    step 1 : rec(x) : cur holds the numbers taken from 1 .. x - 1, in increasing order.
//    step 2 : cur has k numbers : push it to ans, return.
//    step 3 : x > n : no numbers left and cur is too short, return.
//    step 4 : take x : push x, rec(x + 1), pop x. then nottake : rec(x + 1).
//             take first, so the answer comes out in the order of the example.
//    step 5 : reset the globals, rec(1).
//
// 6. Why it works
//    every number gets a take / skip decision until k are taken, so every k-subset is one
//    path of the recursion, and different paths give different subsets.
//    time O(C(n , k) * k + nodes of the recursion) <= O(2^n), space O(n) for cur besides the answer.
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
ll upto ; // the biggest number I may take (n)
ll need ; // how many numbers to take (k)
vector < int > cur ;
vector < vector < int > > ans ;
void rec(ll x)
{
    // step 1 : this decides for x .. upto whether each number goes into cur
    // step 2 : cur is full
    if((ll)cur.size() == need)
    {
        ans.push_back(cur) ;
        return ;
    }
    // step 3 : no numbers left
    if(x > upto)
    {
        return ;
    }
    // step 4 : take x, then skip x
    cur.push_back(x) ;
    rec(x + 1) ;
    cur.pop_back() ;
    rec(x + 1) ;
}
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        // step 5 : reset every global, LeetCode keeps them between test cases
        upto = n ;
        need = k ;
        cur.clear() ;
        ans.clear() ;
        rec(1) ;
        return ans ;
    }
};
