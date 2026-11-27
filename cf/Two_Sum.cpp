// orz
// 1. Two Sum · LeetCode · Easy
//
// Question:
// given an array of integers nums and an integer target, return the indices of
// the two numbers that add up to target. there is exactly one solution, and the
// same element may not be used twice. return the answer in any order.
// Example 1: nums = [2,7,11,15], target = 9   -> [0,1]
// Example 2: nums = [3,2,4], target = 6       -> [1,2]
// Example 3: nums = [3,3], target = 6         -> [0,1]
// Constraints: 2 <= n <= 10^4, -10^9 <= nums[i] <= 10^9, -10^9 <= target <= 10^9,
//              only one valid answer exists
// Follow up: an algorithm less than O(n^2) time. -> done here.
//
// 1. Mathematical statement
//    find i != j with nums[i] + nums[j] = target.
//
// 2. Brute force
//    try every pair i < j. O(n^2) = 10^8 / 2. passes, but the follow up asks for less.
//
// 3. What the brute force wastes
//    for a fixed i the partner is forced: it must be rem = target - nums[i].
//    the inner loop scans all of j just to answer "where is rem?".
//
// 4. Key breaking point
//    "where is value rem?" is a lookup. a map value -> index answers it in O(log n).
//    then the pair search is one loop.
//
// 5. Method
//    step 1 : pos[v] = (last index of v) + 1. +1 so that 0 means "v is not there".
//             keeping the LAST index matters for [3,3]: pos[3] = 2, so i = 0 finds index 1.
//    step 2 : for every i, rem = target - nums[i] (in ll, it can reach 2 * 10^9).
//             if rem is in pos and pos[rem] != i + 1 (not i itself), return {i , pos[rem] - 1}.
//    step 3 : the statement promises an answer, so step 2 always returns.
//
// 6. Why it works
//    take the answer pair i < j. if nums[i] != nums[j], pos[nums[j]] points at
//    some index holding nums[j], which is not i, so i finds a valid partner.
//    if nums[i] == nums[j], pos holds the last copy, which is >= j > i, so again not i.
//    time O(n log n), extra space O(n).
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
    vector<int> twoSum(vector<int>& nums, int target) {
        ll n = nums.size() ;
        // step 1 : pos stores, for every value, its last index + 1
        map < ll , ll > pos ;
        for(ll i = 0 ; i < n ; i++)
        {
            pos[nums[i]] = i + 1 ;
        }
        // step 2 : the partner of i must be rem
        for(ll i = 0 ; i < n ; i++)
        {
            ll rem = (ll)target - nums[i] ;
            if(pos.find(rem) != pos.end() && pos[rem] != i + 1)
            {
                return {(int)i , (int)(pos[rem] - 1)} ;
            }
            else
            {
                continue ;
            }
        }
        // step 3 : never reached, an answer always exists
        return {} ;
    }
};
