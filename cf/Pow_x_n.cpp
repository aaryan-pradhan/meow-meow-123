// orz
// 50. Pow(x, n) · LeetCode · Medium
//
// Question:
// implement pow(x , n), which calculates x raised to the power n (x^n).
// Example 1: x = 2.00000, n = 10 -> 1024.00000
// Example 2: x = 2.10000, n = 3  -> 9.26100
// Example 3: x = 2.00000, n = -2 -> 0.25000  (2^-2 = 1 / 4)
// Constraints: -100.0 < x < 100.0, -2^31 <= n <= 2^31 - 1, n is an integer,
//              either x is not zero or n > 0, -10^4 <= x^n <= 10^4
//
// 1. Mathematical statement
//    n >= 0 : x^n = x * x * .. * x (n times).
//    n < 0  : x^n = (1 / x)^(-n). x != 0 here (given), so 1 / x exists.
//
// 2. Brute force
//    multiply x into the answer |n| times.
//    |n| up to 2^31, about 2 * 10^9 multiplications per call. TLE.
//
// 3. What the brute force wastes
//    x^8 = x * x * x * x * x * x * x * x is 7 multiplications, but
//    x^2 = x * x, x^4 = x^2 * x^2, x^8 = x^4 * x^4 is 3. squares reuse the work.
//
// 4. Key breaking point
//    my binary exponentiation (mpow), with double instead of mod:
//    write b in binary, b = sum of 2^j over the set bits j, so
//    x^b = product of x^(2^j) over the set bits. x^(2^j) is x squared j times.
//    the trap : n = -2^31 and -n = 2^31 does not fit in int. so b is ll.
//
// 5. Method
//    step 1 : b = n as ll, a = x.
//             if b < 0 : a = 1 / a, b = -b. now b >= 0 and the answer is a^b.
//    step 2 : res = 1. while b > 0 :
//             if the last bit of b is 1 : res = res * a.
//             a = a * a (a goes x, x^2, x^4, ..), b >>= 1 (next bit).
//    step 3 : return res.
//
// 6. Why it works
//    at the start of round j, a = x^(2^j) and b holds the bits j, j + 1, .. of |n|.
//    res picks up a exactly when bit j is 1, so at the end res = product of x^(2^j)
//    over the set bits = x^|n|. the last a = a * a may overflow to inf or go to 0,
//    but that value is never multiplied into res.
//    time O(log |n|) = 32 rounds, extra space O(1).
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
    double myPow(double x, int n) {
        // step 1 : ll so that -(-2^31) fits
        ll b = n ;
        double a = x ;
        if(b < 0)
        {
            a = 1 / a ;
            b = -b ;
        }
        // step 2 : binary exponentiation
        double res = 1 ;
        while(b > 0)
        {
            if(b & 1)
            {
                res = res * a ;
            }
            a = a * a ;
            b >>= 1 ;
        }
        // step 3
        return res ;
    }
};
