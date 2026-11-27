// orz
// 373. Find K Pairs with Smallest Sums · LeetCode · Medium
//
// Question:
// you are given two integer arrays nums1 and nums2 sorted in non-decreasing order,
// and an integer k. a pair (u, v) has one element u from nums1 and one element v
// from nums2. return the k pairs (u1, v1), (u2, v2), .., (uk, vk) with the smallest sums.
// Example 1: nums1 = [1,7,11], nums2 = [2,4,6], k = 3 -> [[1,2],[1,4],[1,6]]
// Example 2: nums1 = [1,1,2], nums2 = [1,2,3], k = 2  -> [[1,1],[1,1]]
// Constraints: 1 <= n1, n2 <= 10^5, -10^9 <= nums1[i], nums2[i] <= 10^9,
//              both sorted in non-decreasing order, 1 <= k <= 10^4, k <= n1 * n2
//
// 1. Mathematical statement
//    among all index pairs (i , j), 0 <= i < n1, 0 <= j < n2, output k of them with the
//    smallest nums1[i] + nums2[j] (as values [nums1[i] , nums2[j]]).
//
// 2. Brute force
//    build all n1 * n2 pairs, sort by sum, take the first k.
//    n1 * n2 = 10^10. dead.
//
// 3. What the brute force wastes
//    only k <= 10^4 pairs are needed, and it builds and sorts all 10^10.
//
// 4. Key breaking point
//    fix i. row i = the pairs (i , 0), (i , 1), (i , 2), .. and because nums2 is sorted,
//    their sums only go up along the row. so I have n1 sorted rows and I want the k smallest
//    values over all rows: a k-way merge with a min-heap, like Dijkstra's pq.
//    the heap holds the current front of every row. the smallest pair not yet taken is always
//    some row's front, so pop the top, output it, and push the next pair of that row.
//    only rows i < k matter: row i >= k starts at (i , 0), and (0 , 0) .. (k - 1 , 0) are
//    k pairs with sums <= it (nums1 sorted), so it is never needed.
//
// 5. Method
//    step 1 : min-heap pq of {sum , {i , j}}.
//    step 2 : push the front of each row: {nums1[i] + nums2[0] , {i , 0}} for i < min(n1 , k).
//    step 3 : k times: pop the top {sum , {i , j}}, add [nums1[i] , nums2[j]] to ans.
//             if j + 1 < n2, push the next pair of row i: {nums1[i] + nums2[j + 1] , {i , j + 1}}.
//    step 4 : return ans.
//
// 6. Why it works
//    every pair not yet output is at or behind its row's front, and its row is sorted, so it is
//    >= that front. so the smallest pair left is the smallest front = pq.top().
//    sums reach 2 * 10^9, so they are kept in ll.
//    time O(k log k) (the heap never has more than k entries), extra space O(k).
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
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        ll n1 = nums1.size() ;
        ll n2 = nums2.size() ;
        vector < vector < int > > ans ;
        // step 1 : this stores {sum , {i , j}} for the front of every row, smallest sum on top
        priority_queue < pair < ll , pll > , vector < pair < ll , pll > > , greater < pair < ll , pll > > > pq ;
        // step 2 : the front of rows 0 .. min(n1 , k) - 1
        for(ll i = 0 ; i < min(n1 , (ll)k) ; i++)
        {
            ll sum = (ll)nums1[i] + nums2[0] ;
            pq.push({sum , {i , 0}}) ;
        }
        // step 3
        for(ll cnt = 0 ; cnt < k ; cnt++)
        {
            pair < ll , pll > top = pq.top() ;
            pq.pop() ;
            ll i = top.sc.fr ;
            ll j = top.sc.sc ;
            ans.push_back({nums1[i] , nums2[j]}) ;
            if(j + 1 < n2)
            {
                ll sum = (ll)nums1[i] + nums2[j + 1] ;
                pq.push({sum , {i , j + 1}}) ;
            }
            else
            {
                continue ;
            }
        }
        // step 4
        return ans ;
    }
};
