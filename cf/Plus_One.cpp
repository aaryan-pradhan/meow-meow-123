// orz
// 66. Plus One · LeetCode · Easy
//
// Question:
// a large integer is given as an array digits, where digits[i] is the i-th digit,
// most significant first. there are no leading zeros. add one to the integer and
// return the resulting array of digits.
// Example 1: digits = [1,2,3]   -> [1,2,4]
// Example 2: digits = [4,3,2,1] -> [4,3,2,2]
// Example 3: digits = [9]       -> [1,0]
// Constraints: 1 <= digits.length <= 100, 0 <= digits[i] <= 9,
//              digits has no leading 0's
//
// 1. Mathematical statement
//    N = sum of digits[i] * 10^(n - 1 - i). return the base 10 digits of N + 1.
//
// 2. Brute force
//    turn digits into a number, add 1, split it back into digits.
//    100 digits do not fit in any integer type (ll stops at 19 digits). dead.
//
// 3. What the brute force wastes
//    adding 1 only touches the last digit and the carry it makes.
//    the number itself never has to exist.
//
// 4. Key breaking point
//    do school addition on the array: add 1 to the last digit and push the carry left.
//    the carry is 0 or 1, so everything stays a single digit.
//
// 5. Method
//    step 1 : carry = 1 (this is the "+ 1").
//    step 2 : walk i from n - 1 down to 0 : sum = digits[i] + carry,
//             digits[i] = sum % 10, carry = sum / 10.
//    step 3 : if carry is still 1, every digit was 9 and is now 0, so the
//             answer is one digit longer: put a 1 in front.
//
// 6. Why it works
//    this is exactly the column addition of N + 1, right to left.
//    a carry survives step 2 only when N = 99..9, and then N + 1 = 100..0, which is step 3.
//    time O(n), extra space O(1) apart from the answer.
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
    vector<int> plusOne(vector<int>& digits) {
        ll n = digits.size() ;
        vector < int > ans = digits ;
        // step 1 : the + 1 enters as a carry
        ll carry = 1 ;
        // step 2 : column addition from the last digit
        for(ll i = n - 1 ; i >= 0 ; i--)
        {
            ll sum = ans[i] + carry ;
            ans[i] = sum % 10 ;
            carry = sum / 10 ;
        }
        // step 3 : all nines, one more digit in front
        if(carry == 1)
        {
            ans.insert(ans.begin() , 1) ;
        }
        return ans ;
    }
};
