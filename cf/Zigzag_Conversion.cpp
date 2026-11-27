// orz
// 6. Zigzag Conversion · LeetCode · Medium
//
// Question:
// write the string s in a zigzag on numRows rows : go down the rows one char at a
// time, then diagonally back up, then down again, and so on. then read the rows
// top to bottom, each left to right, and return that string.
// "PAYPALISHIRING" on 3 rows :
//     P   A   H   N
//     A P L S I I G
//     Y   I   R
// Example 1: s = "PAYPALISHIRING", numRows = 3 -> "PAHNAPLSIIGYIR"
// Example 2: s = "PAYPALISHIRING", numRows = 4 -> "PINALSIGYAHRPI"
// Example 3: s = "A", numRows = 1              -> "A"
// Constraints: 1 <= s.length <= 1000, s has English letters (upper and lower case),
//              ',' and '.', 1 <= numRows <= 1000
//
// 1. Mathematical statement
//    the row of char i is r(i) : r(0) = 0, and r goes +1 per char until it hits
//    numRows - 1, then -1 until it hits 0, and so on.
//    return all chars with r = 0 (in order), then r = 1, .. , then r = numRows - 1.
//
// 2. Brute force
//    build the full 2D grid numRows x n of blanks, put every char in its cell,
//    then read the grid row by row skipping blanks. O(numRows * n) = 10^6 cells,
//    almost all of them blank.
//
// 3. What the brute force wastes
//    the column of a char never matters : inside one row the chars are already in
//    the order of s. only the row matters.
//
// 4. Key breaking point
//    keep one string per row. walk s once, append each char to its row's string,
//    and move the row like a ball bouncing between 0 and numRows - 1.
//
// 5. Method
//    step 1 : numRows == 1 : there is no zigzag, return s (the row could not bounce).
//    step 2 : rows[0 .. numRows - 1] empty strings, r = 0, dir = +1.
//    step 3 : for every char : rows[r] += ch. if r == 0, dir = +1.
//             if r == numRows - 1, dir = -1. then r += dir.
//    step 4 : glue rows[0], rows[1], .. , rows[numRows - 1] and return.
//
// 6. Why it works
//    step 3 gives each char exactly the row r(i) of the statement, and inside a row
//    chars are appended in the order of s, which is the left to right order in the grid.
//    time O(n), extra space O(n).
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
    string convert(string s, int numRows) {
        ll n = s.size() ;
        ll k = numRows ;
        // step 1 : one row, nothing moves
        if(k == 1)
        {
            return s ;
        }
        // step 2 : rows[r] stores the chars of row r in order
        vector < string > rows(k , "") ;
        ll r = 0 ;
        ll dir = 1 ;
        // step 3 : bounce between row 0 and row k - 1
        for(ll i = 0 ; i < n ; i++)
        {
            rows[r] += s[i] ;
            if(r == 0)
            {
                dir = 1 ;
            }
            else if(r == k - 1)
            {
                dir = -1 ;
            }
            r += dir ;
        }
        // step 4 : read the rows top to bottom
        string ans = "" ;
        for(ll j = 0 ; j < k ; j++)
        {
            ans += rows[j] ;
        }
        return ans ;
    }
};
