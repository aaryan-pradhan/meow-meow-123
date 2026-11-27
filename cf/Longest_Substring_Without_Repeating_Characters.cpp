// orz
// 3. Longest Substring Without Repeating Characters · LeetCode · Medium
//
// Question:
// given a string s, return the length of the longest substring that has no
// repeating characters.
// Example 1: s = "abcabcbb" -> 3  ("abc")
// Example 2: s = "bbbbb"    -> 1  ("b")
// Example 3: s = "pwwkew"   -> 3  ("wke", "pwke" is a subsequence, not a substring)
// Constraints: 0 <= s.length <= 5 * 10^4, s has English letters, digits, symbols and spaces
//
// 1. Mathematical statement
//    maximise h - t + 1 over all 0 <= t <= h < n such that s[t .. h] has all characters
//    distinct. 0 when s is empty.
//
// 2. Brute force
//    every t, every h >= t, check distinct with a seen table. O(n^2) pairs,
//    n = 5 * 10^4 gives about 1.25 * 10^9. dead.
//
// 3. What the brute force wastes
//    if s[t .. h] has a repeat, so does every longer window, so for a fixed t only the
//    longest distinct window matters. and when t moves right, a distinct window stays
//    distinct, so the best h for t + 1 is at least the best h for t. the brute force
//    restarts h from t every time.
//
// 4. Key breaking point
//    "all distinct" is monotone (a sub-window of a good window is good): my sliding window
//    t / h with a freq table, exactly like Playlist.
//
// 5. Method
//    step 1 : freq[c] = how many times c is in the window. 128 slots, s is ASCII.
//             t = 0, h = -1 (empty window), ans = 0.
//    step 2 : while h + 1 < n and freq[s[h + 1]] == 0 : h++, freq[s[h]]++.
//    step 3 : [t, h] is the longest distinct window starting at t, ans = max(ans, h - t + 1).
//    step 4 : remove s[t] (freq[s[t]]--), t++ (empty window: t++, h = t - 1).
//    step 5 : return ans.
//
// 6. Why it works
//    for each t, step 2 pushes h as far as the window stays distinct, so [t, h] is the
//    longest good window starting at t. h never has to move back (monotone), so no window
//    is missed, and ans is the max over every t.
//    t and h each move at most n times: time O(n), extra space O(128).
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
    int lengthOfLongestSubstring(string s) {
        ll n = s.size() ;
        // step 1
        vector < ll > freq(128 , 0) ; // this stores how many times each character is in the window
        ll t = 0 , h = -1 , ans = 0 ;
        while(t < n)
        {
            // step 2 : grow while the next character is new
            while(h + 1 < n && freq[s[h + 1]] == 0)
            {
                h++ ;
                freq[s[h]]++ ;
            }
            // step 3 : longest distinct window starting at t
            ans = max(ans , h - t + 1) ;
            // step 4 : drop s[t]
            if(t > h)
            {
                t++ ;
                h = t - 1 ;
            }
            else
            {
                freq[s[t]]-- ;
                t++ ;
            }
        }
        // step 5
        return ans ;
    }
};
