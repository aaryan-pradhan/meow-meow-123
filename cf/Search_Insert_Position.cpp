// orz
// 35. Search Insert Position · LeetCode · Easy
//
// Question:
// given a sorted array of distinct integers nums and a target value, return the
// index of target if it is in nums. if it is not, return the index where it would
// be inserted to keep nums sorted. you must write an O(log n) algorithm.
// Example 1: nums = [1,3,5,6], target = 5 -> 2
// Example 2: nums = [1,3,5,6], target = 2 -> 1
// Example 3: nums = [1,3,5,6], target = 7 -> 4
// Constraints: 1 <= n <= 10^4, -10^4 <= nums[i], target <= 10^4,
//              nums has distinct values sorted in ascending order.
//
// 1. Mathematical statement
//    find the smallest index i in [0, n] with nums[i] >= target,
//    where nums[n] counts as +infinity (so i = n means "after everything").
//
// 2. Brute force
//    walk i = 0 .. n - 1 and stop at the first nums[i] >= target.
//    O(n), and the judge asks for O(log n).
//
// 3. What the brute force wastes
//    it ignores that nums is sorted. one look at nums[mid] already answers
//    the question for a whole half of the array.
//
// 4. Key breaking point
//    check(i) = "nums[i] >= target" reads false false .. false true true .. true
//    along the array, because nums is sorted. the answer is the first index where
//    check is true: my binary search template, lo / hi / ans.
//
// 5. Method
//    step 1 : check(i) returns true if nums[i] >= target.
//    step 2 : lo = 0, hi = n - 1, ans = n. ans = n covers "target is bigger than everything".
//    step 3 : mid = lo + (hi - lo) / 2.
//             check(mid) true  -> mid is a candidate, ans = mid, look left: hi = mid - 1.
//             check(mid) false -> the first true is right of mid: lo = mid + 1.
//    step 4 : return ans.
//
// 6. Why it works
//    everything left of the first true index is < target and everything from it on
//    is >= target, so it is exactly where target sits (if present) or where it goes.
//    each round halves [lo, hi]. time O(log n), extra space O(1).
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
    int searchInsert(vector<int>& nums, int target) {
        ll n = nums.size() ;
        // step 2
        ll lo = 0 , hi = n - 1 , ans = n ;
        // step 3 : first index where check is true
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
        return ans ;
    }
};
