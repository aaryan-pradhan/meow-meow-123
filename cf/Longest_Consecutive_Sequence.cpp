// orz
// 128. Longest Consecutive Sequence · LeetCode · Medium
//
// Question:
// given an unsorted array of integers nums, return the length of the longest
// run of consecutive values (x, x + 1, .., x + len - 1) that are all in nums.
// you must write an algorithm that runs in O(n) time.
// Example 1: nums = [100,4,200,1,3,2]         -> 4   (1, 2, 3, 4)
// Example 2: nums = [0,3,7,2,5,8,4,6,0,1]     -> 9   (0 .. 8)
// Example 3: nums = [1,0,1,2]                 -> 3
// Constraints: 0 <= n <= 10^5, -10^9 <= nums[i] <= 10^9
//
// 1. Mathematical statement
//    S = the set of values in nums. the largest len with x, x + 1, .., x + len - 1
//    all in S for some x (0 if S is empty).
//
// 2. Brute force
//    for every x in S, count up x + 1, x + 2, .. while they are in S. keep the best.
//    a run of length L gets walked from each of its L values: L + (L - 1) + .. = O(L^2).
//    nums = 0 .. 10^5 - 1 gives ~5 * 10^9. dead.
//    (sorting + one scan is O(n log n), but the judge asks for O(n).)
//
// 3. What the brute force wastes
//    walking up from x + 1, x + 2, .. re-walks a tail of the walk that started at x.
//    only the walk from the FIRST value of a run is needed.
//
// 4. Key breaking point
//    x is the first value of its run exactly when x - 1 is not in S.
//    walk up only from those starts. every value of S is then walked exactly once,
//    by the start of its own run. with a hash set each "is v in S" is O(1), so O(n).
//
// 5. Method
//    step 1 : s = unordered_set of nums (duplicates collapse).
//    step 2 : for every x in s (not in nums: duplicate starts would re-walk the run):
//             if x - 1 is in s, x is not a start, skip it.
//    step 3 : else len = 1, and while x + len is in s, len++. ans = max(ans , len).
//    step 4 : return ans (0 when nums is empty, the loop never runs).
//
// 6. Why it works
//    every run has exactly one start, and step 3 from that start counts the whole run.
//    each value is visited by step 2 once and by step 3 once (inside its own run),
//    so the total work is O(n) average with the hash set.
//    time O(n) average, extra space O(n).
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
    int longestConsecutive(vector<int>& nums) {
        ll n = nums.size() ;
        // step 1 : s stores every value once
        // note : unordered_set is O(1) average, an anti-hash test could slow it down
        unordered_set < ll > s ;
        for(ll i = 0 ; i < n ; i++)
        {
            s.insert(nums[i]) ;
        }
        ll ans = 0 ;
        for(auto x : s)
        {
            // step 2 : only walk from the first value of a run
            if(s.find(x - 1) != s.end())
            {
                continue ;
            }
            // step 3 : walk the run up from x
            ll len = 1 ;
            while(s.find(x + len) != s.end())
            {
                len++ ;
            }
            ans = max(ans , len) ;
        }
        // step 4
        return ans ;
    }
};
