// orz
// 34. Find First and Last Position of Element in Sorted Array · LeetCode · Medium
//
// Question:
// given an array of integers nums sorted in non-decreasing order, find the starting
// and ending position of a given target value. if target is not found in the array,
// return [-1, -1]. you must write an algorithm with O(log n) runtime complexity.
// Example 1: nums = [5,7,7,8,8,10], target = 8 -> [3,4]
// Example 2: nums = [5,7,7,8,8,10], target = 6 -> [-1,-1]
// Example 3: nums = [], target = 0             -> [-1,-1]
// Constraints: 0 <= n <= 10^5, -10^9 <= nums[i], target <= 10^9, nums is non-decreasing.
//
// 1. Mathematical statement
//    first = min i with nums[i] = target, last = max i with nums[i] = target.
//    return [first, last], or [-1, -1] if no i has nums[i] = target.
//
// 2. Brute force
//    scan left to right, remember the first and the last index equal to target.
//    O(n), the judge asks for O(log n).
//
// 3. What the brute force wastes
//    nums is sorted, so all copies of target sit in one block, and both ends of
//    a block in a sorted array can be found by halving.
//
// 4. Key breaking point
//    both ends are "first index where check is true" questions:
//    first = the first i with nums[i] >= target,
//    last  = (the first i with nums[i] >= target + 1) - 1, i.e. one before the first value bigger than target.
//    (target + 1 is fine: values are integers, and it is done in ll so 10^9 + 1 can't overflow.)
//    one helper, firstatleast(x), with my binary search template, called twice.
//
// 5. Method
//    step 1 : check(i , x) returns true if nums[i] >= x. false .. false true .. true because nums is sorted.
//    step 2 : firstatleast(x) = the binary search template, lo = 0, hi = n - 1, ans = n
//             (n means every value is < x).
//    step 3 : first = firstatleast(target). if first = n or nums[first] != target, target is
//             missing: return [-1, -1]. (n = 0 lands here too.)
//    step 4 : last = firstatleast(target + 1) - 1.
//    step 5 : return [first, last].
//
// 6. Why it works
//    in a sorted array the values equal to target are exactly the indices in
//    [first i with value >= target , first i with value > target). value > target is the same as
//    value >= target + 1 for integers. time O(log n) (two binary searches), extra space O(1).
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
bool check(ll i , vector<int>& nums , ll x)
{
    // this returns true if nums[i] >= x
    if(nums[i] >= x)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
// step 2
ll firstatleast(vector<int>& nums , ll x)
{
    // this returns the first index i with nums[i] >= x, n if there is none
    ll n = nums.size() ;
    ll lo = 0 , hi = n - 1 , ans = n ;
    while(lo <= hi)
    {
        ll mid = lo + (hi - lo) / 2 ;
        if(check(mid , nums , x))
        {
            ans = mid ;
            hi = mid - 1 ;
        }
        else
        {
            lo = mid + 1 ;
        }
    }
    return ans ;
}
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        ll n = nums.size() ;
        // step 3
        ll first = firstatleast(nums , target) ;
        if(first == n || nums[first] != target)
        {
            return {-1 , -1} ;
        }
        // step 4
        ll last = firstatleast(nums , (ll)target + 1) - 1 ;
        // step 5
        return {(int)first , (int)last} ;
    }
};
