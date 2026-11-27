// orz
// 172. Factorial Trailing Zeroes · LeetCode · Medium
//
// Question:
// given an integer n, return the number of trailing zeroes in n!.
// (n! = n * (n - 1) * .. * 3 * 2 * 1)
// Example 1: n = 3 -> 0  (3! = 6)
// Example 2: n = 5 -> 1  (5! = 120)
// Example 3: n = 0 -> 0  (0! = 1)
// Constraints: 0 <= n <= 10^4
// Follow up: a solution in logarithmic time complexity. -> done here.
//
// 1. Mathematical statement
//    the largest t with 10^t dividing n!.
//    10 = 2 * 5, so t = min(e2 , e5), where e2 / e5 = the power of 2 / 5 in n!.
//
// 2. Brute force
//    compute n! and count the zeros at the end.
//    10^4! has about 35660 digits, no integer type holds it. dead.
//    (better brute : for every k in 1 .. n, count how many 5s divide k. O(n log n), not log.)
//
// 3. What the brute force wastes
//    only the factors 2 and 5 matter, and there are always more 2s than 5s
//    (every second number gives a 2, only every fifth gives a 5).
//    so t = e5. counting 5s number by number repeats the same division again and again.
//
// 4. Key breaking point
//    count 5s by layers instead of by numbers (Legendre):
//    floor(n / 5) numbers give at least one 5, floor(n / 25) give a second one,
//    floor(n / 125) a third, ... e5 = n / 5 + n / 25 + n / 125 + ..
//
// 5. Method
//    step 1 : ans = 0.
//    step 2 : for i = 5, 25, 125, .. while i <= n : ans += n / i.
//    step 3 : return ans.
//
// 6. Why it works
//    a number k with exactly c factors 5 is a multiple of 5, 25, .., 5^c and of no
//    higher power, so the layers count it exactly c times. summing over k gives e5,
//    and e5 <= e2, so e5 = min(e2 , e5) = the number of trailing zeros.
//    time O(log5 n), extra space O(1). i is ll so i *= 5 can never overflow.
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
    int trailingZeroes(int n) {
        // step 1
        ll ans = 0 ;
        // step 2 : the numbers that give a 5, then a second 5, then a third ..
        for(ll i = 5 ; i <= n ; i *= 5)
        {
            ans += n / i ;
        }
        // step 3
        return ans ;
    }
};
