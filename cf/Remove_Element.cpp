// orz
// 27. Remove Element · LeetCode · Easy
//
// Question:
// given an integer array nums and an integer val, remove every occurrence of val
// in place. the order of the remaining elements may change. return k, the number
// of elements that are not val; the first k elements of nums must be exactly
// those elements (in any order), what is after them does not matter.
// Example 1: nums = [3,2,2,3], val = 3           -> 2, nums = [2,2,_,_]
// Example 2: nums = [0,1,2,2,3,0,4,2], val = 2   -> 5, nums = [0,1,4,0,3,_,_,_] (any order)
// Constraints: 0 <= n <= 100, 0 <= nums[i] <= 50, 0 <= val <= 100
//
// 1. Mathematical statement
//    k = number of i with nums[i] != val.
//    rearrange nums so that nums[0 .. k - 1] is the multiset { nums[i] : nums[i] != val }.
//
// 2. Brute force
//    find a val, shift everything after it one place left, repeat.
//    each shift is O(n), up to n shifts, O(n^2).
//
// 3. What the brute force wastes
//    every element after a val is moved again for every val before it,
//    when it only needs to move once, straight to its final slot.
//
// 4. Key breaking point
//    treat nums[0 .. k - 1] as a stack of the kept elements, built in place.
//    read nums left to right; an element that is not val is pushed, a val is skipped.
//    the write slot k never passes the read slot i, so nothing unread is overwritten.
//
// 5. Method
//    step 1 : k = 0, the stack is empty.
//    step 2 : for i = 0 .. n - 1:
//             if nums[i] == val, skip it.
//             else push it: nums[k] = nums[i], then k++.
//    step 3 : return k.
//
// 6. Why it works
//    every non-val element is pushed exactly once, in order, and no val is pushed,
//    so nums[0 .. k - 1] is exactly the kept elements. k <= i at each write,
//    so nums[i] is read before slot i can be written.
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
    int removeElement(vector<int>& nums, int val) {
        ll n = nums.size() ;
        // step 1 : nums[0 .. k - 1] is the stack of kept elements
        ll k = 0 ;
        // step 2 : skip val, push everything else
        for(ll i = 0 ; i < n ; i++)
        {
            if(nums[i] == val)
            {
                continue ;
            }
            else
            {
                nums[k] = nums[i] ;
                k++ ;
            }
        }
        // step 3
        return k ;
    }
};
