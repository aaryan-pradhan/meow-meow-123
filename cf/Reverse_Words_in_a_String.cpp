// orz
// 151. Reverse Words in a String · LeetCode · Medium
//
// Question:
// given a string s, reverse the order of its words. a word is a maximal run of
// non-space characters. s may have leading, trailing or multiple spaces between
// words; the answer has the words in reverse order, joined by single spaces,
// with no leading or trailing space.
// Example 1: s = "the sky is blue"  -> "blue is sky the"
// Example 2: s = "  hello world  "  -> "world hello"
// Example 3: s = "a good   example" -> "example good a"
// Constraints: 1 <= s.length <= 10^4, s has English letters (upper and lower case),
//              digits and spaces ' ', there is at least one word in s
//
// 1. Mathematical statement
//    let w[0], w[1], .. , w[k - 1] be the words of s from left to right.
//    return w[k - 1] + " " + w[k - 2] + " " + .. + " " + w[0].
//
// 2. Brute force
//    find the last word of s, append it to the answer, erase it from s, repeat.
//    each erase shifts the rest of s, so O(n^2).
//
// 3. What the brute force wastes
//    it searches s from the end again for every word, and erasing copies the string
//    every time.
//
// 4. Key breaking point
//    reading the words left to right once gives the list w. reversing the order is then
//    just reading the list from its back.
//
// 5. Method
//    step 1 : walk s with i. skip spaces. at a letter, read the whole word
//             (until a space or the end) and push it to words.
//    step 2 : walk words from the back, append each one, and a single space between two words.
//    step 3 : return the answer.
//
// 6. Why it works
//    step 1 collects exactly the maximal runs of non-spaces, in order, and drops every space.
//    step 2 puts them back in reverse order with exactly one space between neighbours.
//    every char is touched a constant number of times : time O(n), extra space O(n).
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
    string reverseWords(string s) {
        ll n = s.size() ;
        // step 1 : words stores the words of s from left to right
        vector < string > words ;
        ll i = 0 ;
        while(i < n)
        {
            if(s[i] == ' ')
            {
                i++ ;
                continue ;
            }
            string word = "" ;
            while(i < n && s[i] != ' ')
            {
                word += s[i] ;
                i++ ;
            }
            words.push_back(word) ;
        }
        // step 2 : words from the back, one space between two words
        ll k = words.size() ;
        string ans = "" ;
        for(ll j = k - 1 ; j >= 0 ; j--)
        {
            ans += words[j] ;
            if(j > 0)
            {
                ans += ' ' ;
            }
        }
        // step 3
        return ans ;
    }
};
