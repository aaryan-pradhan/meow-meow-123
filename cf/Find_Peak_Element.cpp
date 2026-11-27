// orz
// 162. Find Peak Element · LeetCode · Medium
//
// Question:
// a peak element is an element that is strictly greater than its neighbours.
// given a 0-indexed integer array nums, find a peak element and return its index.
// if there are several peaks, return the index of any of them. imagine
// nums[-1] = nums[n] = -infinity, so an element at the border only has to beat
// its one real neighbour. you must write an O(log n) algorithm.
// Example 1: nums = [1,2,3,1]         -> 2   (3 is a peak)
// Example 2: nums = [1,2,1,3,5,6,4]   -> 1 or 5   (2 is a peak, 6 is a peak)
// Constraints: 1 <= n <= 1000, -2^31 <= nums[i] <= 2^31 - 1,
//              nums[i] != nums[i + 1] for every valid i.
//
// 1. Mathematical statement
//    with nums[-1] = nums[n] = -infinity, find any i with nums[i - 1] < nums[i] > nums[i + 1].
//
// 2. Brute force
//    test every i against its two neighbours. O(n), the judge asks for O(log n).
//
// 3. What the brute force wastes
//    one comparison nums[i] vs nums[i + 1] already tells which side surely has a peak,
//    and it throws that away.
//
// 4. Key breaking point
//    call check(i) true if i is the last index or nums[i] > nums[i + 1] ("the road goes down after i").
//    check is NOT false .. true over the whole array (it can switch many times), but my template
//    still works with one fact: check(n - 1) is true. when the template stops it returns an index
//    ans with check(ans) true and check(ans - 1) false (or ans = 0). that ans is a peak:
//    check(ans - 1) false -> nums[ans - 1] < nums[ans] (neighbours differ),
//    check(ans) true      -> nums[ans] > nums[ans + 1] or ans is the last index.
//
// 5. Method
//    step 1 : check(i) returns true if i = n - 1 or nums[i] > nums[i + 1].
//    step 2 : lo = 0, hi = n - 1, ans = n - 1.
//    step 3 : the binary search template: check(mid) true -> ans = mid, hi = mid - 1,
//             false -> lo = mid + 1.
//    step 4 : return ans.
//
// 6. Why it works
//    why the template lands on a switch false -> true:
//    hi only changes together with ans (hi = ans - 1), and lo only changes to mid + 1 right after
//    check(mid) was false. ans is set at least once, because if it never were, hi stays n - 1, so lo
//    would have to pass n - 1, which needs check(n - 1) false. impossible.
//    so at the end lo = hi + 1 = ans, and lo is either 0 or (an index with check false) + 1.
//    so check(ans) is true and check(ans - 1) is false (or ans = 0, where nums[-1] = -infinity).
//    by the key breaking point (4.) that is a peak. time O(log n), extra space O(1).
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
bool check(ll i , vector<int>& nums)
{
    // this returns true if the road goes down after i (or i is the last index)
    ll n = nums.size() ;
    if(i == n - 1)
    {
        return true ;
    }
    if(nums[i] > nums[i + 1])
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
    int findPeakElement(vector<int>& nums) {
        ll n = nums.size() ;
        // step 2 : check(n - 1) is always true
        ll lo = 0 , hi = n - 1 , ans = n - 1 ;
        // step 3
        while(lo <= hi)
        {
            ll mid = lo + (hi - lo) / 2 ;
            if(check(mid , nums))
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
