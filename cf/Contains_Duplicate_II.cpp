// orz
// 219. Contains Duplicate II · LeetCode · Easy
//
// Question:
// given an integer array nums and an integer k, return true if there are two
// distinct indices i and j with nums[i] == nums[j] and abs(i - j) <= k.
// Example 1: nums = [1,2,3,1], k = 3       -> true
// Example 2: nums = [1,0,1,1], k = 1       -> true
// Example 3: nums = [1,2,3,1,2,3], k = 2   -> false
// Constraints: 1 <= n <= 10^5, -10^9 <= nums[i] <= 10^9, 0 <= k <= 10^5
//
// 1. Mathematical statement
//    is there i < j with nums[i] == nums[j] and j - i <= k?
//
// 2. Brute force
//    for every j, look back at i = j - 1 .. j - k for an equal value.
//    O(n * k) = 10^5 * 10^5 = 10^10. dead.
//
// 3. What the brute force wastes
//    for a fixed j, among all earlier i with nums[i] == nums[j], the closest one
//    gives the smallest j - i. if the closest one is too far, all of them are.
//    so only ONE earlier index per value matters: the last one.
//
// 4. Key breaking point
//    last[v] = the last index where v was seen. then each j is one lookup:
//    is j - last[nums[j]] <= k?
//
// 5. Method
//    step 1 : walk j = 0 .. n - 1. if nums[j] was seen and j - last[nums[j]] <= k,
//             return true.
//    step 2 : last[nums[j]] = j (j is now the closest copy for everything after it).
//    step 3 : no pair found, return false.
//
// 6. Why it works
//    if a good pair i < j exists, at time j last[nums[j]] is the largest i' < j with
//    the same value, so i' >= i and j - i' <= j - i <= k. step 1 catches it.
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
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        ll n = nums.size() ;
        // this stores, for every value, the last index where it was seen
        map < ll , ll > last ;
        for(ll j = 0 ; j < n ; j++)
        {
            // step 1 : the closest earlier copy of nums[j]
            if(last.find(nums[j]) != last.end() && j - last[nums[j]] <= k)
            {
                return true ;
            }
            // step 2
            last[nums[j]] = j ;
        }
        // step 3
        return false ;
    }
};
