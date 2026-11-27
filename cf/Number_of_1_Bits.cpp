// orz
// 191. Number of 1 Bits · LeetCode · Easy
//
// Question:
// given a positive integer n, return the number of set bits (bits equal to 1)
// in its binary representation (also known as the Hamming weight).
// Example 1: n = 11          -> 3    (1011)
// Example 2: n = 128         -> 1    (10000000)
// Example 3: n = 2147483645  -> 30   (1111111111111111111111111111101)
// Constraints: 1 <= n <= 2^31 - 1
//
// 1. Mathematical statement
//    n = sum over b = 0 .. 30 of bit(b) * 2^b with each bit(b) in {0 , 1}. return sum of bit(b).
//
// 2. Brute force
//    write n in binary as a string (repeated % 2 and / 2) and count the '1' chars.
//    31 steps, fine, but it builds a string it doesn't need.
//
// 3. What the brute force wastes
//    the bits are already inside n, so each one can be read directly and added up.
//
// 4. Key breaking point
//    read bit b of x with (x >> b) & 1:
//        ">> b" slides every bit of x b places to the right, so bit b lands in place 0.
//        "& 1" keeps only place 0 (1 is 000..001, every other place is ANDed with 0).
//        the result is 0 or 1: the value of bit b. adding these up counts the ones.
//
// 5. Method
//    step 1 : x = n as ll, cnt = 0.
//    step 2 : for b = 0 .. 31: cnt += (x >> b) & 1.
//    step 3 : return cnt.
//
// 6. Why it works
//    every bit place of n is visited once and adds exactly its own value, 0 or 1.
//    n < 2^31, so places 0 .. 31 cover every bit. time O(32), extra space O(1).
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
    int hammingWeight(int n) {
        // step 1
        ll x = n ;
        ll cnt = 0 ;
        // step 2 : add the value of every bit
        for(ll b = 0 ; b < 32 ; b++)
        {
            ll bit = (x >> b) & 1 ;
            cnt += bit ;
        }
        // step 3
        return cnt ;
    }
};
