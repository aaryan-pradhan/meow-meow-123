// orz
// 17. Letter Combinations of a Phone Number · LeetCode · Medium
//
// Question:
// given a string digits containing digits from 2 to 9, return all letter combinations
// the number could stand for, using the phone keypad: 2 = abc, 3 = def, 4 = ghi, 5 = jkl,
// 6 = mno, 7 = pqrs, 8 = tuv, 9 = wxyz. the answer can be in any order.
// Example 1: digits = "23" -> ["ad","ae","af","bd","be","bf","cd","ce","cf"]
// Example 2: digits = ""   -> []
// Example 3: digits = "2"  -> ["a","b","c"]
// Constraints: 0 <= digits.length <= 4, digits[i] is a digit in ['2', '9'].
//
// 1. Mathematical statement
//    let K(d) = the letters of key d. return every string s with |s| = |digits|
//    and s[i] in K(digits[i]) for every i. for empty digits return nothing.
//
// 2. Brute force
//    the answer itself has up to 4^4 = 256 strings, so listing them is the whole job.
//    the only question is how to loop over a number of digits that is not fixed.
//
// 3. What the brute force wastes
//    nothing to save. but writing one for loop per digit only works if |digits| is known,
//    and it changes from test to test.
//
// 4. Key breaking point
//    one nested loop per digit = a recursion with one level per digit.
//    rec(i) loops over the letters of digit i and calls rec(i + 1): my take / skip rec,
//    with "pick one of the letters" instead of "take or skip".
//
// 5. Method
//    step 1 : keys[d] = the letters of digit d.
//    step 2 : rec(i) : cur holds one letter for each of digits[0 .. i - 1].
//             i = |digits| means cur is complete, push it to ans.
//    step 3 : else for every letter of keys[digits[i]] : push it on cur, rec(i + 1), pop it again.
//    step 4 : reset cur and ans, empty digits returns [], else rec(0).
//
// 6. Why it works
//    every level picks exactly one letter for its digit and tries all of them,
//    so the leaves are exactly the strings of the statement, each one once.
//    time O(4^n * n), space O(n) for cur besides the answer.
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
// step 1 : the keypad
vector < string > keys = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"} ;
string cur ;
vector < string > ans ;
void rec(ll i , string& digits)
{
    // this tries every letter for digit i, then fills digits i + 1 .. n - 1
    // step 2 : all digits have a letter
    if(i == (ll)digits.size())
    {
        ans.push_back(cur) ;
        return ;
    }
    // step 3 : one letter for digit i
    string letters = keys[digits[i] - '0'] ;
    for(ll j = 0 ; j < (ll)letters.size() ; j++)
    {
        cur.push_back(letters[j]) ;
        rec(i + 1 , digits) ;
        cur.pop_back() ;
    }
}
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // step 4 : reset every global, LeetCode keeps them between test cases
        cur = "" ;
        ans.clear() ;
        if(digits.size() == 0)
        {
            return ans ;
        }
        rec(0 , digits) ;
        return ans ;
    }
};
