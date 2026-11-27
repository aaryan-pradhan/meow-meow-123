// orz
// 215. Kth Largest Element in an Array · LeetCode · Medium
//
// Question:
// given an integer array nums and an integer k, return the kth largest element in
// the array. note that it is the kth largest element in sorted order, not the kth
// distinct element. can you solve it without sorting?
// Example 1: nums = [3,2,1,5,6,4], k = 2         -> 5
// Example 2: nums = [3,2,3,1,2,4,5,5,6], k = 4   -> 4
// Constraints: 1 <= k <= n <= 10^5, -10^4 <= nums[i] <= 10^4
//
// 1. Mathematical statement
//    sort nums in decreasing order as d[0] >= d[1] >= .. >= d[n - 1]. return d[k - 1].
//
// 2. Brute force
//    k times: find the biggest value left and remove it. the k-th one removed is the answer.
//    O(n * k), n = k = 10^5 gives 10^10. dead.
//
// 3. What the brute force wastes
//    every round rescans all n values, but at any moment only the k biggest values seen
//    so far can still be the answer. everything below them is dead forever.
//
// 4. Key breaking point
//    keep exactly the k biggest values seen so far in a min-heap (priority_queue with greater).
//    the top of a min-heap is its smallest value, so the top = the k-th biggest seen so far.
//    a new value pushes in, and if the heap grows to k + 1, the top (the smallest of the k + 1)
//    can't be in the top k any more, so it is popped.
//
// 5. Method
//    step 1 : min-heap pq, empty.
//    step 2 : for every x in nums: push x. if pq has k + 1 values, pop the top.
//    step 3 : return pq.top().
//
// 6. Why it works
//    after each x, pq holds the k biggest values among those seen (a value is popped only when
//    k bigger-or-equal values are in the heap with it). after all of nums, pq holds the k biggest
//    of the whole array, and its smallest one is the k-th largest.
//    time O(n log k), extra space O(k).
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
    int findKthLargest(vector<int>& nums, int k) {
        ll n = nums.size() ;
        // step 1 : this stores the k biggest values seen so far, smallest on top
        priority_queue < ll , vector < ll > , greater < ll > > pq ;
        // step 2
        for(ll i = 0 ; i < n ; i++)
        {
            pq.push(nums[i]) ;
            if((ll)pq.size() > k)
            {
                pq.pop() ;
            }
        }
        // step 3
        return pq.top() ;
    }
};
