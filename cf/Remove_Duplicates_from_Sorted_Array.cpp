// orz
// 26. Remove Duplicates from Sorted Array · LeetCode · Easy
//
// Question:
// nums is sorted in non-decreasing order. remove the duplicates in place so that
// each unique element appears only once, keeping their relative order.
// return k, the number of unique elements; the first k elements of nums must be
// the unique elements in order, what is after them does not matter.
// Example 1: nums = [1,1,2]                -> 2, nums = [1,2,_]
// Example 2: nums = [0,0,1,1,1,2,2,3,3,4]  -> 5, nums = [0,1,2,3,4,_,_,_,_,_]
// Constraints: 1 <= n <= 3 * 10^4, -100 <= nums[i] <= 100, nums is sorted non-decreasing
//
// 1. Mathematical statement
//    k = number of distinct values in nums.
//    make nums[0 .. k - 1] the distinct values in increasing order.
//
// 2. Brute force
//    find a value equal to the one before it, shift everything after it one place left, repeat.
//    up to n shifts of O(n) each, O(n^2) = 9 * 10^8. too slow.
//
// 3. What the brute force wastes
//    every element is shifted again for every duplicate before it,
//    when it only needs to move once, straight to its final slot.
//
// 4. Key breaking point
//    treat nums[0 .. k - 1] as a stack of the answer, built in place (my stack template).
//    the array is sorted, so all copies of a value are next to each other:
//    x is a new value exactly when the stack is empty or its top nums[k - 1] != x.
//    so only the top has to be checked, never the whole stack.
//
// 5. Method
//    step 1 : k = 0, the stack is empty.
//    step 2 : for i = 0 .. n - 1, x = nums[i]:
//             if the stack is empty or nums[k - 1] != x, push x: nums[k] = x, then k++.
//             else x is a copy of the top, skip it.
//    step 3 : return k.
//
// 6. Why it works
//    sorted means equal values form one block, so the first element of every block
//    is pushed and every later copy sees itself on top and is skipped.
//    k <= i at each write, so nums[i] is read before slot i can be written.
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
    int removeDuplicates(vector<int>& nums) {
        ll n = nums.size() ;
        // step 1 : nums[0 .. k - 1] is the stack, nums[k - 1] is the top
        ll k = 0 ;
        // step 2 : push x only when it differs from the top
        for(ll i = 0 ; i < n ; i++)
        {
            ll x = nums[i] ;
            if(k == 0 || nums[k - 1] != x)
            {
                nums[k] = x ;
                k++ ;
            }
            else
            {
                continue ;
            }
        }
        // step 3
        return k ;
    }
};
