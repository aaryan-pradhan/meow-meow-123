// orz
// 58. Length of Last Word · LeetCode · Easy
//
// Question:
// given a string s of words and spaces, return the length of the last word.
// a word is a maximal run of non-space characters.
// Example 1: s = "Hello World"                 -> 5  ("World")
// Example 2: s = "   fly me   to   the moon  " -> 4  ("moon")
// Example 3: s = "luffy is still joyboy"       -> 6  ("joyboy")
// Constraints: 1 <= s.length <= 10^4, s has only English letters and spaces,
//              there is at least one word in s
//
// 1. Mathematical statement
//    let e = the last index with s[e] != ' ', and b = the last index < e with s[b] == ' '
//    (b = -1 if there is none). answer = e - b.
//
// 2. Brute force
//    split s into all its words, store them, return the size of the last one.
//    O(n) time but O(n) extra space for words we never look at.
//
// 3. What the brute force wastes
//    every word but the last is stored for nothing.
//
// 4. Key breaking point
//    the last word sits at the end, so read s backwards : skip the trailing spaces,
//    then count letters until the next space.
//
// 5. Method
//    step 1 : i = n - 1. while s[i] is a space, i--.
//    step 2 : while i >= 0 and s[i] is not a space, len++ and i--.
//    step 3 : return len.
//
// 6. Why it works
//    after step 1, s[i] is the last letter of the last word (there is at least one word).
//    step 2 walks exactly that word back to its start.
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
class Solution {
public:
    int lengthOfLastWord(string s) {
        ll n = s.size() ;
        // step 1 : skip the trailing spaces
        ll i = n - 1 ;
        while(i >= 0 && s[i] == ' ')
        {
            i-- ;
        }
        // step 2 : count the letters of the last word
        ll len = 0 ;
        while(i >= 0 && s[i] != ' ')
        {
            len++ ;
            i-- ;
        }
        // step 3
        return len ;
    }
};
