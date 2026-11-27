// orz
// 190. Reverse Bits · LeetCode · Easy
//
// Question:
// reverse the bits of a given 32 bit signed integer: write n with exactly 32 bits
// (leading zeros included), read those 32 bits backwards, and return that number.
// Example 1: n = 43261596   -> 964176192
//            00000010100101000001111010011100 -> 00111001011110000010100101000000
// Example 2: n = 2147483644 -> 1073741822
//            01111111111111111111111111111100 -> 00111111111111111111111111111110
// Constraints: 0 <= n <= 2^31 - 2, n is even.
//
// 1. Mathematical statement
//    n = sum over b = 0 .. 31 of bit(b) * 2^b. return sum over b of bit(b) * 2^(31 - b):
//    bit b of n becomes bit 31 - b of the answer.
//
// 2. Brute force
//    write n as a 32 char string of '0' / '1' (repeated % 2 and / 2), reverse the string,
//    read it back as a number. 32 steps, fine, but it builds a string just to move bits.
//
// 3. What the brute force wastes
//    the bits are already inside n. they can be read and written in place, no string needed.
//
// 4. Key breaking point
//    two small bit tools, nothing else:
//    read bit b of x  : (x >> b) & 1.
//        ">> b" slides every bit of x b places to the right, so bit b lands in place 0.
//        "& 1" keeps only place 0 (1 is 000..001, so every other place is ANDed with 0).
//        the result is 0 or 1: the value of bit b.
//    turn on bit p of ans : ans = ans | (1LL << p).
//        "1LL << p" is a number with only bit p on (it is 2^p).
//        "|" puts a 1 in every place where either side has a 1, so bit p of ans becomes 1
//        and every other bit of ans stays as it was.
//
// 5. Method
//    step 1 : x = n as ll (n >= 0, so there is no sign to worry about), ans = 0.
//    step 2 : for b = 0 .. 31: bit = (x >> b) & 1. if bit = 1, turn on bit 31 - b of ans.
//    step 3 : return ans.
//
// 6. Why it works
//    every bit of n is copied to its mirror place, and the places that get no 1 stay 0.
//    the answer fits in int: n is even, so bit 0 of n is 0, so bit 31 of the answer is 0,
//    so the answer is < 2^31. time O(32), extra space O(1).
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
    int reverseBits(int n) {
        // step 1
        ll x = n ;
        ll ans = 0 ;
        // step 2 : bit b of n goes to place 31 - b
        for(ll b = 0 ; b < 32 ; b++)
        {
            ll bit = (x >> b) & 1 ;
            if(bit == 1)
            {
                ans = ans | (1LL << (31 - b)) ;
            }
            else
            {
                continue ;
            }
        }
        // step 3
        return ans ;
    }
};
