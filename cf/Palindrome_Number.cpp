// orz
// 9. Palindrome Number · LeetCode · Easy
//
// Question:
// given an integer x, return true if x is a palindrome (it reads the same
// from left to right and from right to left), and false otherwise.
// Example 1: x = 121  -> true
// Example 2: x = -121 -> false  (right to left it reads 121-)
// Example 3: x = 10   -> false  (right to left it reads 01)
// Constraints: -2^31 <= x <= 2^31 - 1
// Follow up: solve it without converting the integer to a string. -> done here.
//
// 1. Mathematical statement
//    write x = d(k - 1) d(k - 2) .. d(1) d(0) in base 10.
//    x is a palindrome iff x >= 0 and d(i) = d(k - 1 - i) for every i,
//    i.e. x equals the number whose digits are x's digits reversed.
//
// 2. Brute force
//    turn x into a string, reverse it, compare.
//    O(digits) time, but it builds a string, which the follow up forbids.
//
// 3. What the brute force wastes
//    the string is only a way to read the digits back to front.
//    % 10 and / 10 already hand me the digits back to front, one by one.
//
// 4. Key breaking point
//    build rev = x with its digits reversed, using only % 10 and / 10.
//    x is a palindrome iff rev == x. rev can pass 2^31 - 1 (2147483647 reversed
//    is 7463847412), so rev is ll.
//
// 5. Method
//    step 1 : x < 0 -> false. the '-' sits on the left only.
//    step 2 : temp = x, rev = 0. while temp > 0 : digit = temp % 10,
//             rev = rev * 10 + digit, temp /= 10.
//             every round moves the last digit of temp to the end of rev.
//    step 3 : return rev == x.
//
// 6. Why it works
//    after step 2 rev has the digits d(0) d(1) .. d(k - 1), x reversed.
//    two numbers without leading zeros are equal iff their digit strings are equal,
//    so rev == x iff x reads the same both ways. (x = 10 gives rev = 1 != 10, correct.)
//    time O(number of digits) = O(log x), extra space O(1).
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
    bool isPalindrome(int x) {
        // step 1 : a negative number is never a palindrome
        if(x < 0)
        {
            return false ;
        }
        // step 2 : rev = x with its digits reversed
        ll temp = x ;
        ll rev = 0 ;
        while(temp > 0)
        {
            ll digit = temp % 10 ;
            rev = rev * 10 + digit ;
            temp /= 10 ;
        }
        // step 3
        if(rev == x)
        {
            return true ;
        }
        else
        {
            return false ;
        }
    }
};
