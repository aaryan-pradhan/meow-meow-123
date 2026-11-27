// orz
// 12. Integer to Roman · LeetCode · Medium
//
// Question:
// roman numerals use I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000.
// a number is written one decimal place at a time, from thousands down to ones:
// a digit 4 or 9 uses the subtractive form (IV = 4, IX = 9, XL = 40, XC = 90,
// CD = 400, CM = 900); any other digit uses the 5-symbol (V, L, D) at most once
// and the 1-symbol (I, X, C, M) at most 3 times. given num, return its roman numeral.
// Example 1: num = 3749 -> "MMMDCCXLIX"  (MMM + DCC + XL + IX)
// Example 2: num = 58   -> "LVIII"       (L + VIII)
// Example 3: num = 1994 -> "MCMXCIV"     (M + CM + XC + IV)
// Constraints: 1 <= num <= 3999
//
// 1. Mathematical statement
//    num = 1000 * a + 100 * b + 10 * c + d. write a, b, c, d one after the other,
//    each with its place's symbols : digit 9 -> (one)(ten), 5 .. 8 -> (five) + (digit - 5) ones,
//    4 -> (one)(five), 0 .. 3 -> that many ones.
//
// 2. Brute force
//    hand-write all four cases for every place : 4 places * 10 digits = 40 strings,
//    and glue the four lookups together.
//
// 3. What the brute force wastes
//    the 40 strings are the same 4 patterns repeated with different letters.
//
// 4. Key breaking point
//    there are only 13 "chunks" : 1000 M, 900 CM, 500 D, 400 CD, 100 C, 90 XC,
//    50 L, 40 XL, 10 X, 9 IX, 5 V, 4 IV, 1 I.
//    greedy : take the biggest chunk that still fits, write it, subtract, repeat.
//
// 5. Method
//    step 1 : the 13 chunks, biggest first, in val[] and sym[].
//    step 2 : for every chunk k, while num >= val[k], append sym[k] and num -= val[k].
//    step 3 : return the string.
//
// 6. Why it works
//    take one place, say the hundreds digit b. the greedy first takes 900 if b = 9,
//    else 500 if b >= 5, else 400 if b = 4, then 100s for the rest. that is exactly the
//    digit rule above. a chunk of a place never fits after that place is done
//    (what is left is below 100), so the places come out one after the other.
//    at most 15 symbols, time O(1), extra space O(1).
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
    string intToRoman(int num) {
        // step 1 : the 13 chunks, biggest first
        vector < ll > val = {1000 , 900 , 500 , 400 , 100 , 90 , 50 , 40 , 10 , 9 , 5 , 4 , 1} ;
        vector < string > sym = {"M" , "CM" , "D" , "CD" , "C" , "XC" , "L" , "XL" , "X" , "IX" , "V" , "IV" , "I"} ;
        // step 2 : biggest chunk that still fits
        ll x = num ;
        string ans = "" ;
        for(ll k = 0 ; k < 13 ; k++)
        {
            while(x >= val[k])
            {
                ans += sym[k] ;
                x -= val[k] ;
            }
        }
        // step 3
        return ans ;
    }
};
