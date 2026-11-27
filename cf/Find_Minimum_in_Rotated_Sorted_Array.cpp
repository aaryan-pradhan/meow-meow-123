// orz
// 153. Find Minimum in Rotated Sorted Array · LeetCode · Medium
//
// Question:
// an array of length n sorted in ascending order is rotated between 1 and n times.
// rotating [a0, a1, .., a(n-1)] once gives [a(n-1), a0, a1, .., a(n-2)].
// for example [0,1,2,4,5,6,7] can become [4,5,6,7,0,1,2] (rotated 4 times) or stay
// [0,1,2,4,5,6,7] (rotated 7 times). given the rotated array nums of unique
// elements, return its minimum element. you must write an O(log n) algorithm.
// Example 1: nums = [3,4,5,1,2]        -> 1
// Example 2: nums = [4,5,6,7,0,1,2]    -> 0
// Example 3: nums = [11,13,15,17]      -> 11
// Constraints: 1 <= n <= 5000, -5000 <= nums[i] <= 5000, all values unique,
//              nums is sorted and rotated between 1 and n times.
//
// 1. Mathematical statement
//    nums = (piece A)(piece B), both pieces ascending, every value of A bigger than every
//    value of B (A may be empty). return min over i of nums[i], which is the first element of B.
//
// 2. Brute force
//    scan all n values for the smallest. O(n), the judge asks for O(log n).
//
// 3. What the brute force wastes
//    the array is two sorted pieces, and one comparison tells which piece mid is in.
//
// 4. Key breaking point
//    compare with the last element nums[n - 1], which always lives in piece B.
//    every value of B is <= nums[n - 1] (B is ascending and ends there),
//    every value of A is > nums[n - 1] (A is bigger than all of B).
//    so check(i) = "nums[i] <= nums[n - 1]" reads false on A, true on B: false .. false true .. true.
//    the minimum is the first index where check is true. my binary search template.
//
// 5. Method
//    step 1 : check(i) returns true if nums[i] <= nums[n - 1], i.e. i is in piece B.
//    step 2 : lo = 0, hi = n - 1, ans = n - 1 (check(n - 1) is always true).
//    step 3 : the binary search template for the first index where check is true.
//    step 4 : return nums[ans].
//
// 6. Why it works
//    the first index of piece B is the start of the original sorted array, so it holds the minimum.
//    if the array was rotated n times, A is empty, check is true everywhere and ans = 0.
//    time O(log n), extra space O(1).
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
class Solution {
public:
    int findMin(vector<int>& nums) {
        ll n = nums.size() ;
        // step 2
        ll lo = 0 , hi = n - 1 , ans = n - 1 ;
        // step 3 : first index of piece B
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
        return nums[ans] ;
    }
};
