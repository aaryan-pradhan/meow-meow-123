// orz
// 169. Majority Element · LeetCode · Easy
//
// Question:
// given an array nums of size n, return the majority element: the element that
// appears more than n / 2 times (rounded down). the majority element always exists.
// Example 1: nums = [3,2,3]           -> 3
// Example 2: nums = [2,2,1,1,1,2,2]   -> 2
// Constraints: 1 <= n <= 5 * 10^4, -10^9 <= nums[i] <= 10^9
// Follow up: O(n) time and O(1) space. -> done here (Boyer-Moore voting).
//
// 1. Mathematical statement
//    find the value m with count(m) > n / 2. it is unique: two such values
//    would need more than n elements together.
//
// 2. Brute force
//    for every i, count how many j have nums[j] == nums[i]. stop when the count > n / 2.
//    O(n^2) = 2.5 * 10^9. too slow.
//    (a map of counts is O(n log n) and O(n) space, it misses the follow up.)
//
// 3. What the brute force wastes
//    it counts every value exactly, but I only need to know which value wins
//    a "more than half" vote, not by how much.
//
// 4. Key breaking point
//    cancel pairs of DIFFERENT values. throw away two different elements: m still has
//    more than half of what is left, because at most one of the two was m.
//    keep cancelling, and whatever survives must be m.
//    the cancelling is done in one pass with a candidate cand and a counter cnt
//    = how many uncancelled copies of cand are waiting.
//
// 5. Method
//    step 1 : cand = anything, cnt = 0 (nothing is waiting).
//    step 2 : for every x in nums:
//             if cnt == 0, nothing is waiting, so x becomes the new cand.
//    step 3 : if x == cand, it waits with the others: cnt++.
//             else x cancels one waiting copy of cand: cnt--.
//    step 4 : return cand.
//
// 6. Why it works
//    at the end, cnt copies of cand are still waiting, and every other element is in a
//    cancelled pair of two different values. each pair holds at most one m.
//    if cand != m, every copy of m is in a pair, so count(m) <= number of pairs <= n / 2,
//    a contradiction. so cand = m.
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
    int majorityElement(vector<int>& nums) {
        ll n = nums.size() ;
        // step 1
        ll cand = 0 ; // this stores the value whose copies are waiting
        ll cnt = 0 ;  // this stores how many copies of cand are not cancelled yet
        for(ll i = 0 ; i < n ; i++)
        {
            ll x = nums[i] ;
            // step 2 : nothing waiting, x is the new candidate
            if(cnt == 0)
            {
                cand = x ;
            }
            // step 3 : same value waits, different value cancels one copy
            if(x == cand)
            {
                cnt++ ;
            }
            else
            {
                cnt-- ;
            }
        }
        // step 4
        return cand ;
    }
};
