// orz
// 88. Merge Sorted Array · LeetCode · Easy
//
// Question:
// nums1 and nums2 are sorted in non-decreasing order. nums1 has length m + n:
// its first m elements are real, the last n are 0 and only hold space.
// nums2 has n elements. merge nums2 into nums1 so that nums1 is sorted.
// return nothing, the answer is nums1 itself.
// Example 1: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3 -> [1,2,2,3,5,6]
// Example 2: nums1 = [1], m = 1, nums2 = [], n = 0             -> [1]
// Example 3: nums1 = [0], m = 0, nums2 = [1], n = 1            -> [1]
// Constraints: nums1.length = m + n, nums2.length = n, 0 <= m, n <= 200,
//              1 <= m + n <= 200, -10^9 <= nums1[i], nums2[j] <= 10^9
// Follow up: an algorithm that runs in O(m + n) time. -> done here.
//
// 1. Mathematical statement
//    a = nums1[0 .. m - 1], b = nums2[0 .. n - 1], both sorted.
//    write the sorted order of the multiset a + b into nums1[0 .. m + n - 1],
//    with no second array.
//
// 2. Brute force
//    copy nums2 into nums1[m .. m + n - 1] and sort nums1.
//    O((m + n) log(m + n)). fast enough here, but it throws away that both parts are already sorted.
//
// 3. What the brute force wastes
//    the sort compares elements whose order is already known inside a and inside b.
//    the only unknown is how a and b interleave.
//
// 4. Key breaking point
//    the merge of two sorted lists: compare the two heads, take the right one.
//    from the front it breaks, because writing into nums1[0 ..] overwrites a elements
//    that are not read yet. from the BACK it is safe: the free slots sit at the end
//    of nums1, so fill nums1 from the last slot with the larger of the two tails.
//
// 5. Method
//    step 1 : i = m - 1 (last unread element of a), j = n - 1 (last unread element of b),
//             k = m + n - 1 (the slot to fill next).
//    step 2 : while b still has elements (j >= 0):
//             if a still has elements and nums1[i] > nums2[j], put nums1[i] in slot k, i--.
//             else put nums2[j] in slot k, j--.
//             then k--.
//    step 3 : when b is empty, nums1[0 .. i] are the smallest elements of a and already
//             sit in their place, so stop.
//
// 6. Why it works
//    slot k gets the largest element not placed yet, so slots fill from the back in sorted order.
//    no unread element of a is ever overwritten: k = i + j + 1 and j >= 0, so k > i.
//    time O(m + n), extra space O(1).
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
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // step 1 : three pointers from the back
        ll i = m - 1 ;     // last unread element of nums1
        ll j = n - 1 ;     // last unread element of nums2
        ll k = m + n - 1 ; // the slot to fill next
        // step 2 : the larger tail goes into slot k
        while(j >= 0)
        {
            if(i >= 0 && nums1[i] > nums2[j])
            {
                nums1[k] = nums1[i] ;
                i-- ;
            }
            else
            {
                nums1[k] = nums2[j] ;
                j-- ;
            }
            k-- ;
        }
        // step 3 : nums1[0 .. i] is already in place
    }
};
