// orz
// 30. Substring with Concatenation of All Words · LeetCode · Hard
//
// Question:
// given a string s and an array of strings words, all of words have the same length.
// a concatenated string is all the strings of words, each used once, glued together
// in any order. return the starting indices of all the concatenated substrings of s,
// in any order.
// Example 1: s = "barfoothefoobarman", words = ["foo","bar"]                   -> [0,9]
// Example 2: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"] -> []
// Example 3: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]       -> [6,9,12]
// Constraints: 1 <= s.length <= 10^4, 1 <= m = words.length <= 5000,
//              1 <= w = words[i].length <= 30, lowercase English letters only
//
// 1. Mathematical statement
//    need[x] = how many times word x is in words. index i is an answer iff
//    i + m * w <= n and the m blocks s[i + j * w .. i + j * w + w - 1] (j = 0 .. m - 1)
//    contain every word x exactly need[x] times.
//
// 2. Brute force
//    for every i, cut the m blocks and count them in a map, compare with need.
//    O(n * m * w) characters, up to 10^4 * 10^4 = 10^8 plus a map lookup per block. too slow.
//
// 3. What the brute force wastes
//    start i and start i + w share m - 1 blocks. the brute force cuts and counts
//    them all again.
//
// 4. Key breaking point
//    split the starts by i % w. for one offset r (0 <= r < w), s is a plain array of
//    blocks b[0], b[1], .. (block j = s[r + j * w ..]). an answer is a window of exactly m
//    consecutive blocks with have[x] == need[x]. "have[x] <= need[x] for every x" is monotone
//    (a sub-window of a good window is good), so it is my sliding window t / h on the blocks,
//    and a good window of length m is an answer (the counts can only add to m if all are equal).
//
// 5. Method
//    step 1 : give every distinct word an id, need[id] = its count in words.
//    step 2 : for every offset r = 0 .. w - 1 (and r < n):
//    step 3 : nb = (n - r) / w full blocks. b[j] = id of block j, -1 if it is not a word.
//    step 4 : have[id] = count in the window. t = 0, h = -1.
//             while h + 1 < nb and b[h + 1] != -1 and have[b[h + 1]] < need[b[h + 1]] :
//             h++, have[b[h]]++.
//    step 5 : if the window has m blocks (h - t + 1 == m), r + t * w is an answer.
//    step 6 : remove block t (have[b[t]]--), t++ (empty window: t++, h = t - 1).
//
// 6. Why it works
//    every start i has exactly one offset r = i % w and block index t = (i - r) / w.
//    for that t, step 4 pushes h as far as no word is used more than needed. the m blocks
//    from t are an answer iff they are all words with have <= need, iff the window reaches
//    length m. h never needs to move back (monotone), so each t is judged exactly.
//    time: over all offsets about n / w blocks each, w offsets, so n blocks total, each cut
//    and looked up in O(w log m). O(n * w * log m), extra space O(m * w) for the map.
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
    vector<int> findSubstring(string s, vector<string>& words) {
        ll n = s.size() ;
        ll m = words.size() ;
        ll w = words[0].size() ;
        vector < int > ans ;
        // step 1 : word -> id, need[id] = how many times it is in words
        map < string , ll > id ;
        vector < ll > need ;
        for(ll i = 0 ; i < m ; i++)
        {
            if(id.find(words[i]) == id.end())
            {
                id[words[i]] = need.size() ;
                need.push_back(0) ;
            }
            need[id[words[i]]]++ ;
        }
        ll k = need.size() ;
        // step 2 : one offset at a time
        for(ll r = 0 ; r < w && r < n ; r++)
        {
            // step 3 : cut s into blocks of length w starting at r
            ll nb = (n - r) / w ;
            vector < ll > b(nb) ; // this stores the word id of block j, -1 if it is not a word
            for(ll j = 0 ; j < nb ; j++)
            {
                string cur = s.substr(r + j * w , w) ;
                if(id.find(cur) != id.end())
                {
                    b[j] = id[cur] ;
                }
                else
                {
                    b[j] = -1 ;
                }
            }
            // step 4 : sliding window over the blocks
            vector < ll > have(k , 0) ; // this stores how many times each word is in the window
            ll t = 0 , h = -1 ;
            while(t < nb)
            {
                while(h + 1 < nb && b[h + 1] != -1 && have[b[h + 1]] < need[b[h + 1]])
                {
                    h++ ;
                    have[b[h]]++ ;
                }
                // step 5 : m blocks, every word exactly need times
                if(h - t + 1 == m)
                {
                    ans.push_back(r + t * w) ;
                }
                // step 6 : drop block t
                if(t > h)
                {
                    t++ ;
                    h = t - 1 ;
                }
                else
                {
                    have[b[t]]-- ;
                    t++ ;
                }
            }
        }
        return ans ;
    }
};
