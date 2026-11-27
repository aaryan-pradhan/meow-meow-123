// orz
// 67. Add Binary · LeetCode · Easy
//
// Question:
// given two binary strings a and b, return their sum as a binary string.
// Example 1: a = "11", b = "1"        -> "100"
// Example 2: a = "1010", b = "1011"   -> "10101"
// Constraints: 1 <= a.length, b.length <= 10^4, a and b contain only '0' and '1',
//              no leading zeros except the number zero itself.
//
// 1. Mathematical statement
//    value(s) = sum over k of s[k] * 2^(len - 1 - k) (the last char is the 2^0 digit).
//    return the binary string (no leading zeros) of value(a) + value(b).
//
// 2. Brute force
//    turn a and b into integers, add, turn the sum back into binary.
//    dies at once: 10^4 bits is a number near 2^10000, no integer type holds it.
//
// 3. What the brute force wastes
//    it needs the whole number at once, but school addition only ever needs one column
//    and the carry coming into it.
//
// 4. Key breaking point
//    simulate the statement literally: column addition in base 2, from the last char.
//    in one column: s = carry + (bit of a) + (bit of b), so s is 0, 1, 2 or 3.
//    the digit written is s % 2 and the carry to the next column is s / 2.
//    (s = 2 is "10" in binary: write 0, carry 1. s = 3 is "11": write 1, carry 1.)
//
// 5. Method
//    step 1 : i = last index of a, j = last index of b, carry = 0, ans = "".
//    step 2 : while i >= 0 or j >= 0 or carry = 1:
//             s = carry, plus a[i] - '0' if i >= 0, plus b[j] - '0' if j >= 0.
//             append the char '0' + s % 2, carry = s / 2, i--, j--.
//    step 3 : the digits were appended lowest first, so reverse ans and return it.
//
// 6. Why it works
//    it is the column-by-column addition we do by hand, in base 2. the loop runs while a column
//    still has a digit or a carry, so the last carry becomes the leading 1 (like "11" + "1" = "100").
//    no leading zeros: a column runs only when it has a digit or a carry, and the top column ends in a
//    1 unless both inputs are "0". time O(max(|a| , |b|)), extra space O(1) besides the answer.
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
    string addBinary(string a, string b) {
        // step 1
        ll i = (ll)a.size() - 1 ;
        ll j = (ll)b.size() - 1 ;
        ll carry = 0 ;
        string ans = "" ;
        // step 2 : one column per round, from the right
        while(i >= 0 || j >= 0 || carry == 1)
        {
            ll s = carry ;
            if(i >= 0)
            {
                s += a[i] - '0' ;
            }
            if(j >= 0)
            {
                s += b[j] - '0' ;
            }
            ans += (char)('0' + s % 2) ;
            carry = s / 2 ;
            i-- ;
            j-- ;
        }
        // step 3
        reverse(ans.begin() , ans.end()) ;
        return ans ;
    }
};
