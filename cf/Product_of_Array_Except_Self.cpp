// orz
// 238. Product of Array Except Self · LeetCode · Medium
//
// Question:
// given an integer array nums, return an array answer where answer[i] is the
// product of all the elements of nums except nums[i]. the product of any prefix
// or suffix of nums fits in a 32-bit integer. you must write an O(n) algorithm
// without using division.
// Example 1: nums = [1,2,3,4]       -> [24,12,8,6]
// Example 2: nums = [-1,1,0,-3,3]   -> [0,0,9,0,0]
// Constraints: 2 <= n <= 10^5, -30 <= nums[i] <= 30
// Follow up: O(1) extra space (the output array does not count). -> done here.
//
// 1. Mathematical statement
//    answer[i] = product of nums[j] over all j != i.
//
// 2. Brute force
//    for every i, multiply every nums[j] with j != i.
//    O(n^2), n = 10^5 gives 10^10. dead.
//
// 3. What the brute force wastes
//    answer[i] and answer[i + 1] share almost every factor, and each one
//    multiplies them all again from scratch.
//
// 4. Key breaking point
//    "every j except i" = "every j left of i" and "every j right of i".
//    answer[i] = L[i] * R[i], where L[i] = nums[0] * .. * nums[i - 1] and
//    R[i] = nums[i + 1] * .. * nums[n - 1]. these are prefix / suffix sums, with * instead of +.
//    (the total / nums[i] trick is banned, and it breaks on a 0 anyway.)
//
// 5. Method
//    step 1 : walk left to right with a running product left = L[i] (left = 1 at i = 0).
//             write answer[i] = left first, then left *= nums[i].
//             first write, then multiply, because nums[i] must not be in its own product.
//    step 2 : walk right to left with a running product right = R[i] (right = 1 at i = n - 1).
//             answer[i] *= right first, then right *= nums[i]. same order, same reason.
//    step 3 : return answer.
//
// 6. Why it works
//    after step 1 answer[i] = L[i], after step 2 answer[i] = L[i] * R[i] = product of all j != i.
//    left and right are a prefix and a suffix product, so they fit (given).
//    time O(n), extra space O(1): only left and right.
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
    vector<int> productExceptSelf(vector<int>& nums) {
        ll n = nums.size() ;
        vector < int > answer(n , 1) ;
        // step 1 : answer[i] = product of everything left of i
        ll left = 1 ;
        for(ll i = 0 ; i < n ; i++)
        {
            answer[i] = left ;
            left *= nums[i] ;
        }
        // step 2 : multiply in the product of everything right of i
        ll right = 1 ;
        for(ll i = n - 1 ; i >= 0 ; i--)
        {
            answer[i] *= right ;
            right *= nums[i] ;
        }
        // step 3
        return answer ;
    }
};
