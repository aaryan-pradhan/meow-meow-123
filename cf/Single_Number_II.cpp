// orz
// 137. Single Number II · LeetCode · Medium
//
// Question:
// given an integer array nums where every element appears exactly three times except
// for one, which appears exactly once. find the single element and return it.
// you must implement a solution with linear runtime complexity and use only
// constant extra space.
// Example 1: nums = [2,2,3,2]             -> 3
// Example 2: nums = [0,1,0,1,0,1,99]      -> 99
// Constraints: 1 <= n <= 3 * 10^4, -2^31 <= nums[i] <= 2^31 - 1,
//              every element appears exactly three times except one which appears once.
//
// 1. Mathematical statement
//    the multiset nums = {u} plus three copies of each of some values. return u.
//
// 2. Brute force
//    for every i count how many j have nums[j] = nums[i], return the one with count 1.
//    O(n^2) = 9 * 10^8. too slow. (a count map is O(n) but O(n) extra space, the judge wants O(1).)
//
// 3. What the brute force wastes
//    it counts whole values. xor from Single Number doesn't help (three copies xor to the value,
//    not to 0), but the same idea of looking at one bit place at a time does.
//
// 4. Key breaking point
//    look at one bit place b at a time and count how many numbers have bit b on.
//    a value that appears three times adds 0 or 3 to that count, u adds 1 or 0.
//    so count % 3 = bit b of u. 32 places, each one a simple count.
//    the bit tools, in small steps:
//    read bit b of x : (x >> b) & 1. ">> b" slides bit b into place 0, "& 1" keeps only place 0.
//    negative numbers: an int is 32 bits in two's complement, and bit 31 is the sign bit,
//    worth -2^31 instead of +2^31 (e.g. -1 = all 32 bits on = -2^31 + (2^31 - 1)).
//    putting the int in an ll copies bit 31 into all the new high bits, so bits 0 .. 31 read the same.
//
// 5. Method
//    step 1 : for b = 0 .. 31: cnt = number of x in nums with (x >> b) & 1 = 1.
//    step 2 :     if cnt % 3 = 1, bit b of u is on.
//    step 3 :     add what that bit is worth: 2^b for b = 0 .. 30, and -2^31 for the sign bit b = 31.
//    step 4 : return ans.
//
// 6. Why it works
//    per bit place the triples add a multiple of 3, so the remainder mod 3 is exactly u's bit.
//    rebuilding with the two's complement weights gives u itself, negative or not.
//    time O(32 * n), extra space O(1).
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
        ll ans = 0 ;
        for(ll b = 0 ; b < 32 ; b++)
        {
            // step 1 : how many numbers have bit b on
            ll cnt = 0 ;
            for(ll i = 0 ; i < n ; i++)
            {
                ll x = nums[i] ;
                cnt += (x >> b) & 1 ;
            }
            // step 2 : cnt % 3 is 0 or 1, and 0 means bit b of u is off
            if(cnt % 3 == 0)
            {
                continue ;
            }
            // step 3 : bit b of u is on
            if(b < 31)
            {
                ans += (1LL << b) ;
            }
            else
            {
                ans -= (1LL << 31) ; // the sign bit
            }
        }
        // step 4
        return ans ;
    }
};
