// orz
// 125. Valid Palindrome · LeetCode · Easy
//
// Question:
// a phrase is a palindrome if, after turning every uppercase letter into lowercase
// and removing every character that is not a letter or a digit, it reads the same
// forward and backward. given a string s, return true if it is a palindrome.
// Example 1: s = "A man, a plan, a canal: Panama" -> true   ("amanaplanacanalpanama")
// Example 2: s = "race a car"                     -> false  ("raceacar")
// Example 3: s = " "                              -> true   (nothing is left, "" is a palindrome)
// Constraints: 1 <= s.length <= 2 * 10^5, s has printable ASCII characters only
//
// 1. Mathematical statement
//    let c = the letters and digits of s in order, lowercased, k = c.length.
//    true iff c[i] == c[k - 1 - i] for every 0 <= i < k.
//
// 2. Brute force
//    build c as a new string, build its reverse, compare.
//    O(n) time, but O(n) extra space for the two copies.
//
// 3. What the brute force wastes
//    the copies. every comparison only needs one character from the front and
//    one from the back, and both can be read straight from s.
//
// 4. Key breaking point
//    c[i] vs c[k - 1 - i] is a converging two pointers on s itself:
//    l walks right, r walks left, each one skips the characters that are not in c.
//
// 5. Method
//    step 1 : l = 0, r = n - 1.
//    step 2 : while l < r : if s[l] is not a letter / digit, l++ and go again.
//             if s[r] is not a letter / digit, r-- and go again.
//    step 3 : now s[l] and s[r] are the next front / back characters of c.
//             lowercase both, if they differ return false, else l++, r--.
//    step 4 : the pointers met, every pair matched, return true.
//
// 6. Why it works
//    after the skips, s[l] is c[i] and s[r] is c[k - 1 - i] for the same i, because
//    l has passed exactly i kept characters from the front and r exactly i from the back.
//    so the loop checks every pair of c once. when l >= r the middle is reached.
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
bool keep(char c)
{
    // this returns true if c is a letter or a digit
    if(c >= 'a' && c <= 'z')
    {
        return true ;
    }
    if(c >= 'A' && c <= 'Z')
    {
        return true ;
    }
    if(c >= '0' && c <= '9')
    {
        return true ;
    }
    return false ;
}
char low(char c)
{
    // this returns c in lowercase (digits stay the same)
    if(c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 'a' ;
    }
    return c ;
}
class Solution {
public:
    bool isPalindrome(string s) {
        ll n = s.size() ;
        // step 1
        ll l = 0 , r = n - 1 ;
        while(l < r)
        {
            // step 2 : skip what is not a letter or a digit
            if(!keep(s[l]))
            {
                l++ ;
                continue ;
            }
            if(!keep(s[r]))
            {
                r-- ;
                continue ;
            }
            // step 3 : compare the front and the back of c
            if(low(s[l]) != low(s[r]))
            {
                return false ;
            }
            l++ ;
            r-- ;
        }
        // step 4
        return true ;
    }
};
