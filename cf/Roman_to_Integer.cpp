// orz
// 13. Roman to Integer · LeetCode · Easy
//
// Question:
// roman numerals use I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000.
// symbols are written largest to smallest and added, except six subtractive pairs:
// IV = 4, IX = 9, XL = 40, XC = 90, CD = 400, CM = 900.
// given a roman numeral s, return its value.
// Example 1: s = "III"     -> 3
// Example 2: s = "LVIII"   -> 58    (L = 50, V = 5, III = 3)
// Example 3: s = "MCMXCIV" -> 1994  (M = 1000, CM = 900, XC = 90, IV = 4)
// Constraints: 1 <= s.length <= 15, s has only I V X L C D M,
//              s is a valid roman numeral in [1 , 3999]
//
// 1. Mathematical statement
//    value(s) = sum over i of sign[i] * val(s[i]), where sign[i] = -1 if
//    val(s[i]) < val(s[i + 1]) (s[i] is the small half of a subtractive pair), else +1.
//
// 2. Brute force
//    write the roman numeral of every number 1 .. 3999 and return the one equal to s.
//    3999 numerals of up to 15 chars each. it works, but it builds 3999 strings to read one.
//
// 3. What the brute force wastes
//    the value can be read straight off s. a symbol's contribution only depends on
//    the symbol right after it.
//
// 4. Key breaking point
//    in a valid numeral a smaller symbol before a bigger one only happens inside
//    a subtractive pair. so: smaller than the next symbol -> subtract, else add.
//
// 5. Method
//    step 1 : val(ch) gives the value of one symbol.
//    step 2 : walk i = 0 .. n - 1. if i + 1 < n and val(s[i]) < val(s[i + 1]),
//             subtract val(s[i]). else add it.
//    step 3 : return the total.
//
// 6. Why it works
//    symbols go largest to smallest except the pairs, so a dip upward only happens at
//    the first symbol of a pair. subtracting it and adding the second gives exactly
//    the pair value (IV = -1 + 5 = 4). every other symbol is added as is.
//    time O(n), extra space O(1).
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
ll val(char ch)
{
    // this returns the value of one roman symbol
    if(ch == 'I')
    {
        return 1 ;
    }
    else if(ch == 'V')
    {
        return 5 ;
    }
    else if(ch == 'X')
    {
        return 10 ;
    }
    else if(ch == 'L')
    {
        return 50 ;
    }
    else if(ch == 'C')
    {
        return 100 ;
    }
    else if(ch == 'D')
    {
        return 500 ;
    }
    else
    {
        return 1000 ;
    }
}
class Solution {
public:
    int romanToInt(string s) {
        ll n = s.size() ;
        ll ans = 0 ;
        // step 2 : subtract a symbol smaller than the next one, add the rest
        for(ll i = 0 ; i < n ; i++)
        {
            // step 1
            ll cur = val(s[i]) ;
            if(i + 1 < n && cur < val(s[i + 1]))
            {
                ans -= cur ;
            }
            else
            {
                ans += cur ;
            }
        }
        // step 3
        return ans ;
    }
};
