// orz
// 228. Summary Ranges · LeetCode · Easy
//
// Question:
// given a sorted array of unique integers nums, return the smallest sorted list
// of ranges that covers every number of nums exactly (no range holds a number
// that is not in nums). write range [a, b] as "a->b" if a != b and as "a" if a == b.
// Example 1: nums = [0,1,2,4,5,7]     -> ["0->2","4->5","7"]
// Example 2: nums = [0,2,3,4,6,8,9]   -> ["0","2->4","6","8->9"]
// Constraints: 0 <= n <= 20, -2^31 <= nums[i] <= 2^31 - 1,
//              all values are unique, nums is sorted ascending
//
// 1. Mathematical statement
//    cut nums into maximal blocks where each value is the previous + 1.
//    output each block as its first and last value.
//
// 2. Brute force
//    for every pair (i , j) check if nums[i .. j] is consecutive, and keep only the
//    blocks that can't be grown left or right. O(n^3), tiny at n = 20, but clumsy.
//
// 3. What the brute force wastes
//    the blocks don't overlap and come in order. once a block ends at h, the next
//    one starts at h + 1, so there is nothing to search for.
//
// 4. Key breaking point
//    my t / h window: t = start of the block, push h forward while the next value
//    is nums[h] + 1. when h can't move, [t, h] is one maximal block, and the next
//    block starts at t = h + 1.
//
// 5. Method
//    step 1 : t = 0. while t < n:
//    step 2 : h = t. while h + 1 < n and nums[h + 1] == nums[h] + 1, h++.
//             (in ll: nums[h] + 1 overflows int at 2^31 - 1.)
//    step 3 : write the block: "a" if t == h, else "a->b". then t = h + 1.
//    step 4 : return the list.
//
// 6. Why it works
//    step 2 stops exactly at a gap (or the end), so [t, h] can't grow right, and it
//    can't grow left because the block before it stopped at a gap. so every block
//    is maximal and together they cover nums once, in order. maximal blocks are
//    the fewest ranges, since no range can jump over a gap.
//    time O(n), extra space O(1) besides the answer.
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
    vector<string> summaryRanges(vector<int>& nums) {
        ll n = nums.size() ;
        vector < string > ans ;
        // step 1 : t is the start of the current block
        ll t = 0 ;
        while(t < n)
        {
            // step 2 : grow h while the next value is one more
            ll h = t ;
            while(h + 1 < n && (ll)nums[h + 1] == (ll)nums[h] + 1)
            {
                h++ ;
            }
            // step 3 : write [t, h]
            if(t == h)
            {
                ans.push_back(to_string(nums[t])) ;
            }
            else
            {
                ans.push_back(to_string(nums[t]) + "->" + to_string(nums[h])) ;
            }
            t = h + 1 ;
        }
        // step 4
        return ans ;
    }
};
