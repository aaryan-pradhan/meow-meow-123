// orz
// 167. Two Sum II - Input Array Is Sorted · LeetCode · Medium
//
// Question:
// numbers is a 1-indexed array sorted in non-decreasing order. find two numbers
// that add up to target, at positions index1 < index2, and return [index1, index2]
// (1-indexed). there is exactly one solution, and the same element can not be used
// twice. use only constant extra space.
// Example 1: numbers = [2,7,11,15], target = 9 -> [1,2]
// Example 2: numbers = [2,3,4], target = 6     -> [1,3]
// Example 3: numbers = [-1,0], target = -1     -> [1,2]
// Constraints: 2 <= n <= 3 * 10^4, -1000 <= numbers[i] <= 1000, numbers is sorted
//              non-decreasing, -1000 <= target <= 1000, exactly one solution
//
// 1. Mathematical statement
//    find a < b (0-indexed) with numbers[a] + numbers[b] == target. return [a + 1, b + 1].
//
// 2. Brute force
//    try every pair a < b. O(n^2), n = 3 * 10^4 gives about 4.5 * 10^8 pairs. too slow,
//    and the map version of two sum costs O(n) space, which is banned.
//
// 3. What the brute force wastes
//    the array is sorted and it never uses that. if numbers[l] + numbers[r] is too
//    small, then numbers[l] plus anything left of r is also too small.
//
// 4. Key breaking point
//    converging two pointers (like Ferris Wheel / Sum of Three Values):
//    l = 0, r = n - 1. each comparison throws away one whole index for good.
//
// 5. Method
//    step 1 : l = 0, r = n - 1.
//    step 2 : sum = numbers[l] + numbers[r].
//    step 3 : sum == target -> return [l + 1, r + 1].
//             sum < target  -> l++ (numbers[l] is too small for every partner left).
//             sum > target  -> r-- (numbers[r] is too big for every partner left).
//
// 6. Why it works
//    invariant: the answer (a, b) has l <= a and b <= r. true at the start.
//    if sum < target : for every k in [l + 1, r], numbers[l] + numbers[k] <= sum < target,
//    so l pairs with nothing in range, l != a, l++ keeps the invariant.
//    sum > target is the same with r. the range shrinks every step and the answer
//    is always inside it, so we stop exactly at (a, b).
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
    vector<int> twoSum(vector<int>& numbers, int target) {
        ll n = numbers.size() ;
        vector < int > ans ;
        // step 1
        ll l = 0 , r = n - 1 ;
        while(l < r)
        {
            // step 2
            ll sum = numbers[l] + numbers[r] ;
            // step 3
            if(sum == target)
            {
                ans.push_back(l + 1) ;
                ans.push_back(r + 1) ;
                return ans ;
            }
            else if(sum < target)
            {
                l++ ;
            }
            else
            {
                r-- ;
            }
        }
        return ans ; // never reached, the answer always exists
    }
};
