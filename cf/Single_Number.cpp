// orz
// 136. Single Number · LeetCode · Easy
//
// Question:
// given a non-empty array of integers nums, every element appears twice except
// for one. find that single one. you must implement a solution with linear
// runtime complexity and use only constant extra space.
// Example 1: nums = [2,2,1]       -> 1
// Example 2: nums = [4,1,2,1,2]   -> 4
// Example 3: nums = [1]           -> 1
// Constraints: 1 <= n <= 3 * 10^4, -3 * 10^4 <= nums[i] <= 3 * 10^4,
//              every element appears twice except one element which appears once.
//
// 1. Mathematical statement
//    the multiset nums = {u} plus two copies of each of some values. return u.
//
// 2. Brute force
//    for every i count how many j have nums[j] = nums[i], return the one with count 1.
//    O(n^2) = 9 * 10^8. too slow. (a count map is O(n) but O(n) extra space, the judge wants O(1).)
//
// 3. What the brute force wastes
//    it computes full counts, but only "odd or even" matters: u is the one value with an odd count.
//
// 4. Key breaking point
//    xor, ^, keeps exactly that odd / even information, in small steps:
//    (a) a ^ b looks at each bit place on its own: the result bit is 1 when the two bits differ,
//        0 when they are the same. so per bit place it is "add, and keep only odd / even" (1 + 1 = 0).
//    (b) x ^ x = 0, because every bit equals itself.
//    (c) x ^ 0 = x, because each bit of x differs from 0 exactly when it is 1.
//    (d) order and grouping don't matter: a ^ b = b ^ a and (a ^ b) ^ c = a ^ (b ^ c),
//        because per bit place it is just counting ones and keeping odd / even.
//    so xor of all of nums can be regrouped as u ^ (v1 ^ v1) ^ (v2 ^ v2) ^ .. = u ^ 0 ^ 0 .. = u.
//
// 5. Method
//    step 1 : acc = 0.
//    step 2 : for every x in nums, acc = acc ^ x.
//    step 3 : return acc.
//
// 6. Why it works
//    by (d) the order of the array doesn't matter, by (b) the two copies of every pair cancel,
//    by (c) what is left is u. negative numbers are fine: xor only looks at bits.
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
    int singleNumber(vector<int>& nums) {
        ll n = nums.size() ;
        // step 1
        ll acc = 0 ;
        // step 2 : pairs cancel, the single one stays
        for(ll i = 0 ; i < n ; i++)
        {
            acc = acc ^ nums[i] ;
        }
        // step 3
        return acc ;
    }
};
