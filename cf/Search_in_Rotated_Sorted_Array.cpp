// orz
// 33. Search in Rotated Sorted Array · LeetCode · Medium
//
// Question:
// there is an integer array nums sorted in ascending order with distinct values.
// before being passed to you, nums is possibly left rotated at an unknown index k
// (1 <= k < n), so it becomes [nums[k], .., nums[n-1], nums[0], .., nums[k-1]].
// for example [0,1,2,4,5,6,7] rotated at k = 3 becomes [4,5,6,7,0,1,2].
// given nums after the possible rotation and an integer target, return the index
// of target in nums, or -1 if it is not in nums. you must write an O(log n) algorithm.
// Example 1: nums = [4,5,6,7,0,1,2], target = 0 -> 4
// Example 2: nums = [4,5,6,7,0,1,2], target = 3 -> -1
// Example 3: nums = [1], target = 0             -> -1
// Constraints: 1 <= n <= 5000, -10^4 <= nums[i], target <= 10^4, all values unique,
//              nums is an ascending array that is possibly rotated.
//
// 1. Mathematical statement
//    nums = (piece A)(piece B), both ascending, every value of A bigger than every value
//    of B (A may be empty). find the i with nums[i] = target, or say there is none.
//
// 2. Brute force
//    scan all n values. O(n), the judge asks for O(log n).
//
// 3. What the brute force wastes
//    each piece is sorted, and a sorted piece can be searched in O(log n).
//    the only thing in the way is not knowing where the pieces split.
//
// 4. Key breaking point
//    split the problem into two of my standard binary searches:
//    (a) find where piece B starts: that is exactly Find Minimum in Rotated Sorted Array,
//        the first index with nums[i] <= nums[n - 1].
//    (b) target > nums[n - 1] can only be in A (B is all <= nums[n - 1]), otherwise only in B.
//        that piece is sorted: Search Insert Position on it, the first index with nums[i] >= target.
//
// 5. Method
//    step 1 : checkpivot(i) returns true if nums[i] <= nums[n - 1] (i is in piece B).
//             binary search template, ans = n - 1 at the start -> p = first index of B.
//    step 2 : choose the piece. target > nums[n - 1] -> [0 , p - 1] (piece A, may be empty),
//             else -> [p , n - 1] (piece B).
//    step 3 : check(i) returns true if nums[i] >= target. binary search template on the
//             chosen piece, ans = -1 at the start (-1 = no index in the piece is >= target).
//    step 4 : if ans != -1 and nums[ans] = target return ans, else return -1.
//
// 6. Why it works
//    step 1 is the Find Minimum argument: A is all > nums[n - 1], B is all <= nums[n - 1],
//    so checkpivot is false .. false true .. true.
//    step 2 never throws target away: a value > nums[n - 1] can't be in B, a value <= nums[n - 1]
//    can't be in A. inside one sorted piece check is false .. true, and target, if present,
//    is the first value >= target. time O(log n) (two binary searches), extra space O(1).
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
// step 1
bool checkpivot(ll i , vector<int>& nums)
{
    // this returns true if index i is in piece B (nums[i] <= the last element)
    ll n = nums.size() ;
    if(nums[i] <= nums[n - 1])
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
// step 3
bool check(ll i , vector<int>& nums , ll target)
{
    // this returns true if nums[i] >= target
    if(nums[i] >= target)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
class Solution {
public:
    int search(vector<int>& nums, int target) {
        ll n = nums.size() ;
        // step 1 : p = first index of piece B
        ll lo = 0 , hi = n - 1 , ans = n - 1 ;
        while(lo <= hi)
        {
            ll mid = lo + (hi - lo) / 2 ;
            if(checkpivot(mid , nums))
            {
                ans = mid ;
                hi = mid - 1 ;
            }
            else
            {
                lo = mid + 1 ;
            }
        }
        ll p = ans ;
        // step 2 : choose the piece target can be in
        if(target > nums[n - 1])
        {
            lo = 0 ;
            hi = p - 1 ;
        }
        else
        {
            lo = p ;
            hi = n - 1 ;
        }
        // step 3 : first index in the piece with nums[i] >= target
        ans = -1 ;
        while(lo <= hi)
        {
            ll mid = lo + (hi - lo) / 2 ;
            if(check(mid , nums , target))
            {
                ans = mid ;
                hi = mid - 1 ;
            }
            else
            {
                lo = mid + 1 ;
            }
        }
        // step 4
        if(ans != -1 && nums[ans] == target)
        {
            return ans ;
        }
        else
        {
            return -1 ;
        }
    }
};
