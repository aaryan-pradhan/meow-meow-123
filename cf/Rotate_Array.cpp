// orz
// 189. Rotate Array · LeetCode · Medium
//
// Question:
// given an integer array nums, rotate it to the right by k steps (k >= 0):
// every element moves k places right, and elements falling off the end come back at the front.
// Example 1: nums = [1,2,3,4,5,6,7], k = 3   -> [5,6,7,1,2,3,4]
// Example 2: nums = [-1,-100,3,99], k = 2    -> [3,99,-1,-100]
// Constraints: 1 <= n <= 10^5, -2^31 <= nums[i] <= 2^31 - 1, 0 <= k <= 10^5
// Follow up: do it in place with O(1) extra space. -> done here.
//
// 1. Mathematical statement
//    new[(i + k) mod n] = old[i] for every i, with O(1) extra space.
//
// 2. Brute force
//    rotate by 1 step, k times: save the last element, shift everything right by one,
//    put it at the front. O(n * k) = 10^10. dead.
//    (a copy array is O(n) time but O(n) space, it misses the follow up.)
//
// 3. What the brute force wastes
//    every element walks k single steps, when it only has to land once in its final slot.
//
// 4. Key breaking point
//    rotating by n is doing nothing, so k = k mod n first.
//    cut nums into A = the first n - k elements and B = the last k. rotating right by k
//    turns A B into B A. reversing the whole array gives rev(B) rev(A): the blocks are
//    already in the right place, only their insides are backwards. so reverse each block again.
//
// 5. Method
//    step 1 : k = k mod n.
//    step 2 : reverse all of nums. now it is rev(B) rev(A), rev(B) = nums[0 .. k - 1].
//    step 3 : reverse nums[0 .. k - 1], it becomes B.
//    step 4 : reverse nums[k .. n - 1], it becomes A. now nums = B A.
//
// 6. Why it works
//    reversing a whole array maps index i to n - 1 - i, so the last block B lands at the
//    front and A at the back, each in backwards order. reversing a block twice gives it back,
//    so steps 3 and 4 fix the insides. 3 reversals, each element is swapped at most twice.
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
    void rotate(vector<int>& nums, int k) {
        ll n = nums.size() ;
        // step 1 : rotating by n does nothing
        ll r = k % n ;
        // step 2 : A B -> rev(B) rev(A)
        reverse(nums.begin() , nums.end()) ;
        // step 3 : rev(B) -> B
        reverse(nums.begin() , nums.begin() + r) ;
        // step 4 : rev(A) -> A
        reverse(nums.begin() + r , nums.end()) ;
    }
};
