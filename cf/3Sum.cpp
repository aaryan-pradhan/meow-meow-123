// orz
// 15. 3Sum · LeetCode · Medium
//
// Question:
// given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
// with i, j, k all different and nums[i] + nums[j] + nums[k] == 0.
// the answer must not contain duplicate triplets (as sets of values). any order.
// Example 1: nums = [-1,0,1,2,-1,-4] -> [[-1,-1,2],[-1,0,1]]
// Example 2: nums = [0,1,1]          -> []
// Example 3: nums = [0,0,0]          -> [[0,0,0]]
// Constraints: 3 <= n <= 3000, -10^5 <= nums[i] <= 10^5
//
// 1. Mathematical statement
//    the set of value triples {a <= b <= c} such that a + b + c == 0 and
//    a, b, c sit at three different indices of nums.
//
// 2. Brute force
//    three loops over i < j < k, sort each hit, put it in a set.
//    O(n^3), n = 3000 gives 4.5 * 10^9. dead.
//
// 3. What the brute force wastes
//    once nums[i] is fixed, the other two only need to sum to -nums[i]:
//    that is two sum, and it searches it pair by pair.
//
// 4. Key breaking point
//    sort. fix the smallest value a = nums[i], then find b + c == -a in nums[i + 1 ..]
//    with the converging two pointers of Two Sum II (my Sum of Three Values loop).
//    sorted order also makes duplicates sit next to each other, so they are
//    skipped by comparing with the neighbour, no set needed.
//
// 5. Method
//    step 1 : sort nums.
//    step 2 : for every i : if i > 0 and nums[i] == nums[i - 1], this a was already
//             tried, skip it.
//    step 3 : l = i + 1, r = n - 1. while l < r : sum = nums[i] + nums[l] + nums[r].
//             sum < 0 -> l++. sum > 0 -> r--.
//    step 4 : sum == 0 -> save [nums[i], nums[l], nums[r]], then l++ and r--,
//             and keep moving l while nums[l] == nums[l - 1], so the next b is a new value.
//
// 6. Why it works
//    every answer has a smallest value a, it is tried once (step 2 picks its first copy,
//    which leaves the most room on the right). for a fixed a, the two pointers see every
//    pair b + c == -a (same invariant as Two Sum II). after a hit, b must change to give a
//    new triple (c is then forced), and step 4 jumps to the next different b. so every
//    triple shows up exactly once.
//    time O(n^2) (n two-pointer walks of O(n)), extra space O(1) besides the answer and the sort.
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
    vector<vector<int>> threeSum(vector<int>& nums) {
        ll n = nums.size() ;
        vector < vector < int > > ans ;
        // step 1
        sort(nums.begin() , nums.end()) ;
        for(ll i = 0 ; i < n ; i++)
        {
            // step 2 : this smallest value was already tried
            if(i > 0 && nums[i] == nums[i - 1])
            {
                continue ;
            }
            // step 3 : two sum on nums[i + 1 .. n - 1]
            ll l = i + 1 , r = n - 1 ;
            while(l < r)
            {
                ll sum = nums[i] + nums[l] + nums[r] ;
                if(sum < 0)
                {
                    l++ ;
                }
                else if(sum > 0)
                {
                    r-- ;
                }
                else
                {
                    // step 4 : save it, then move l to the next different value
                    ans.push_back({nums[i] , nums[l] , nums[r]}) ;
                    l++ ;
                    r-- ;
                    while(l < r && nums[l] == nums[l - 1])
                    {
                        l++ ;
                    }
                }
            }
        }
        return ans ;
    }
};
