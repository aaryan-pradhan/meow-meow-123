// orz
// 39. Combination Sum · LeetCode · Medium
//
// Question:
// given an array of distinct integers candidates and a target integer target, return a list
// of all unique combinations of candidates where the chosen numbers sum to target.
// the same number may be chosen an unlimited number of times. two combinations are unique
// if the count of at least one number differs. the answer can be in any order.
// the tests make sure there are fewer than 150 unique combinations.
// Example 1: candidates = [2,3,6,7], target = 7 -> [[2,2,3],[7]]
// Example 2: candidates = [2,3,5], target = 8   -> [[2,2,2,2],[2,3,3],[3,5]]
// Example 3: candidates = [2], target = 1       -> []
// Constraints: 1 <= candidates.length <= 30, 2 <= candidates[i] <= 40, all candidates distinct,
//              1 <= target <= 40.
//
// 1. Mathematical statement
//    return every vector of counts c[0 .. n - 1] >= 0 with sum of c[i] * candidates[i] = target,
//    written out as the list of chosen numbers.
//
// 2. Brute force
//    every count c[i] is between 0 and target / candidates[i], so try every count for every
//    candidate: up to 21^30 tuples. dead.
//
// 3. What the brute force wastes
//    it keeps going after the sum already passed target, and it tries every count for a later
//    candidate even when the earlier ones already went over.
//
// 4. Key breaking point
//    this is my unbounded knapsack rec (unordered, items outside, take stays on the row):
//    rec(i , left) = combinations of candidates i .. n - 1 that make left.
//    take candidates[i] and STAY at i (it can be taken again), or skip it for good and go to i + 1.
//    walking the candidates in a fixed order means each combination comes out once, never as [2,3] and [3,2].
//    stop a take when candidates[i] > left, so the sum never passes target.
//
// 5. Method
//    step 1 : rec(i , left) : cur = numbers chosen so far, left = target - sum(cur).
//    step 2 : left = 0 : cur is a combination, push it to ans, return.
//    step 3 : i = n : no candidates left and left > 0, return.
//    step 4 : take : if candidates[i] <= left, push it, rec(i , left - candidates[i]), pop it.
//    step 5 : nottake : rec(i + 1 , left).
//    step 6 : reset the globals, rec(0 , target).
//
// 6. Why it works
//    a combination = how many times each candidate is taken. the rec decides candidate 0 first
//    (take it again and again, then skip), then candidate 1, and so on, so every count vector is
//    exactly one path. the take guard only cuts paths whose sum is already above target.
//    time O(number of rec calls), tiny here. depth <= target / 2 + n (a take lowers left by >= 2,
//    a skip moves i up by 1), space O(target + n) besides the answer.
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
vector < int > v ;
vector < int > cur ;
vector < vector < int > > ans ;
void rec(ll i , ll left)
{
    // step 1 : this collects every way to make left with v[i .. n - 1], each one usable many times
    // step 2 : the sum is exactly target
    if(left == 0)
    {
        ans.push_back(cur) ;
        return ;
    }
    // step 3 : no candidates left
    if(i == (ll)v.size())
    {
        return ;
    }
    // step 4 : take v[i] and stay at i
    if(v[i] <= left)
    {
        cur.push_back(v[i]) ;
        rec(i , left - v[i]) ;
        cur.pop_back() ;
    }
    // step 5 : never take v[i] again
    rec(i + 1 , left) ;
}
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // step 6 : reset every global, LeetCode keeps them between test cases
        v = candidates ;
        cur.clear() ;
        ans.clear() ;
        rec(0 , target) ;
        return ans ;
    }
};
