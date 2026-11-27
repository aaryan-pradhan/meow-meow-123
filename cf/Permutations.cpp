// orz
// 46. Permutations · LeetCode · Medium
//
// Question:
// given an array nums of distinct integers, return all the possible permutations.
// the answer can be in any order.
// Example 1: nums = [1,2,3] -> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
// Example 2: nums = [0,1]   -> [[0,1],[1,0]]
// Example 3: nums = [1]     -> [[1]]
// Constraints: 1 <= nums.length <= 6, -10 <= nums[i] <= 10, all the integers of nums are unique.
//
// 1. Mathematical statement
//    return every sequence p of length n that uses each nums[i] exactly once.
//
// 2. Brute force
//    try all n^n sequences of indices, keep the ones with no index repeated.
//    6^6 = 46656, tiny, but most of them repeat an index.
//
// 3. What the brute force wastes
//    once an index is placed, every sequence that places it again is dead, yet the brute force
//    still builds the whole sequence before checking.
//
// 4. Key breaking point
//    fill the positions left to right and only offer the numbers not used yet.
//    used[i] = 1 if nums[i] is already in cur. then every leaf is a real permutation.
//
// 5. Method
//    step 1 : rec() : cur = the positions filled so far, used marks their indices.
//    step 2 : cur has n numbers : push it to ans, return.
//    step 3 : for every i with used[i] = 0 : used[i] = 1, push nums[i], rec(), pop, used[i] = 0.
//    step 4 : reset the globals, rec().
//
// 6. Why it works
//    position 1 gets n choices, position 2 gets the n - 1 left, and so on. every permutation is
//    exactly one path, so the leaves are all n! permutations, each once.
//    time O(n! * n), space O(n) besides the answer.
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
vector < ll > used ; // used[i] = 1 if v[i] is already in cur
vector < int > cur ;
vector < vector < int > > ans ;
void rec()
{
    // step 1 : this fills the rest of cur with the unused numbers, in every order
    // step 2 : every number is placed
    if(cur.size() == v.size())
    {
        ans.push_back(cur) ;
        return ;
    }
    // step 3 : the next position gets any unused number
    for(ll i = 0 ; i < (ll)v.size() ; i++)
    {
        if(used[i] == 1)
        {
            continue ;
        }
        used[i] = 1 ;
        cur.push_back(v[i]) ;
        rec() ;
        cur.pop_back() ;
        used[i] = 0 ;
    }
}
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        // step 4 : reset every global, LeetCode keeps them between test cases
        v = nums ;
        used.assign(nums.size() , 0) ;
        cur.clear() ;
        ans.clear() ;
        rec() ;
        return ans ;
    }
};
