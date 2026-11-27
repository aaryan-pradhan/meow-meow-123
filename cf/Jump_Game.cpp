// orz
// 55. Jump Game · LeetCode · Medium
//
// Question:
// you start at index 0 of an integer array nums. nums[i] is the maximum jump length
// from index i: from i you can jump to any of i + 1 .. i + nums[i].
// return true if you can reach the last index, else false.
// Example 1: nums = [2,3,1,1,4]   -> true   (0 -> 1 -> 4)
// Example 2: nums = [3,2,1,0,4]   -> false  (every path gets stuck at index 3, nums[3] = 0)
// Constraints: 1 <= n <= 10^4, 0 <= nums[i] <= 10^5
//
// 1. Mathematical statement
//    graph on 0 .. n - 1 with edges i -> j for i < j <= i + nums[i].
//    is n - 1 reachable from 0?
//
// 2. Brute force
//    bfs / dfs on that graph. node i has nums[i] edges, so O(sum of nums[i]) = 10^4 * 10^5 = 10^9.
//    too slow.
//
// 3. What the brute force wastes
//    it treats every reachable index as a separate fact, but the reachable set has a shape:
//    it is always a prefix 0 .. far.
//
// 4. Key breaking point
//    if j is reachable, every index before j is reachable too: the jump that landed on j
//    came from some i < j with j <= i + nums[i], and that jump could stop on any index
//    between i and j instead (and indices <= i are handled the same way, by induction).
//    (same model as Jump Game II: a long jump plus free steps back i -> i - 1.)
//    so the reachable set is 0 .. far, and I only keep the number far.
//
// 5. Method
//    step 1 : far = 0, only index 0 is reached.
//    step 2 : for i = 0 .. n - 1:
//             if i > far, index i is not reachable, and nothing after it is either. return false.
//    step 3 : else i is reachable, so all of i + 1 .. i + nums[i] is too:
//             far = max(far , i + nums[i]).
//    step 4 : the loop got past n - 1, so n - 1 <= far. return true.
//
// 6. Why it works
//    after processing 0 .. i (all reachable), far = max of j + nums[j] over j <= i,
//    the furthest index any of them can jump to, and by the prefix fact of 4 every index
//    up to far is reachable. if i > far, no index before i jumps to i or past it,
//    so i and everything after it is unreachable.
//    time O(n), extra space O(1).
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
class Solution {
public:
    bool canJump(vector<int>& nums) {
        ll n = nums.size() ;
        // step 1 : this stores the last index of the reachable prefix 0 .. far
        ll far = 0 ;
        for(ll i = 0 ; i < n ; i++)
        {
            // step 2 : i is past the reachable prefix
            if(i > far)
            {
                return false ;
            }
            // step 3 : i is reachable, extend the prefix
            else
            {
                far = max(far , i + nums[i]) ;
            }
        }
        // step 4
        return true ;
    }
};
