// orz
// 68. Text Justification · LeetCode · Hard
//
// Question:
// given an array of words and a width maxWidth, format the text so every line has
// exactly maxWidth characters. pack words greedily : put as many words as fit on
// each line (one space at least between two words). pad with extra spaces so the
// line is exactly maxWidth wide, spread as evenly as possible between the words;
// if they do not split evenly, the gaps on the left get one more space than the
// gaps on the right. the last line, and any line with a single word, is left
// justified : single spaces between words, the rest of the spaces at the end.
// Example 1: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
//            -> ["This    is    an",
//                "example  of text",
//                "justification.  "]
// Example 2: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
//            -> ["What   must   be",
//                "acknowledgment  ",
//                "shall be        "]
// Example 3: words = ["Science","is","what","we","understand","well","enough","to","explain",
//                     "to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
//            -> ["Science  is  what we",
//                "understand      well",
//                "enough to explain to",
//                "a  computer.  Art is",
//                "everything  else  we",
//                "do                  "]
// Constraints: 1 <= words.length <= 300, 1 <= words[i].length <= 20,
//              words[i] has only English letters and symbols (no spaces),
//              1 <= maxWidth <= 100, words[i].length <= maxWidth
//
// 1. Mathematical statement
//    a line holds words t .. h when (sum of their lengths) + (h - t) <= maxWidth, and
//    greedy means h is the largest such index. for a line with g = h - t gaps and
//    sp = maxWidth - (sum of lengths) spaces : if it is the last line or g = 0, single spaces
//    then sp - g spaces at the end. else every gap gets sp / g spaces, and the first
//    sp % g gaps get one more.
//
// 2. Brute force
//    for every line, try every end h = t, t + 1, .. and add up the lengths of t .. h from
//    scratch each time, keep the largest h that fits. O(n^2) adding for the packing.
//
// 3. What the brute force wastes
//    the sum for t .. h + 1 is the sum for t .. h plus one word, and it recomputes it.
//
// 4. Key breaking point
//    a line is a window [t , h] that only grows while the next word fits : my sliding
//    window t / h, with a running width. the next line starts at h + 1.
//    the spacing is then the statement turned into numbers : sp / g and sp % g.
//
// 5. Method
//    step 1 : t = 0. while t < n : h = t, width = |words[t]|.
//             while h + 1 < n and width + 1 + |words[h + 1]| <= maxWidth : h++, width += 1 + |words[h]|.
//    step 2 : g = h - t gaps, letters = width - g (the single spaces taken out),
//             sp = maxWidth - letters.
//    step 3 : last line (h == n - 1) or one word (g == 0) : words with single spaces,
//             then pad the end with spaces up to maxWidth.
//    step 4 : else base = sp / g, extra = sp % g. after word t + j (j < g) put base spaces,
//             plus one more when j < extra.
//    step 5 : push the line, t = h + 1.
//
// 6. Why it works
//    step 1 is greedy packing : it stops exactly when one more word plus its space would
//    overflow. steps 3 and 4 are the spacing rules word for word : base * g + extra = sp, so
//    the line is exactly maxWidth, and the left gaps get the extra ones.
//    every word is added once and every output char written once : time O(n * maxWidth),
//    extra space O(1) besides the answer.
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
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        ll n = words.size() ;
        ll w = maxWidth ;
        vector < string > ans ;
        ll t = 0 ;
        while(t < n)
        {
            // step 1 : grow the line [t , h] while the next word still fits
            ll h = t ;
            ll width = words[t].size() ; // this stores the words t .. h with single spaces
            while(h + 1 < n && width + 1 + (ll)words[h + 1].size() <= w)
            {
                h++ ;
                width += 1 + words[h].size() ;
            }
            // step 2 : letters, spaces, gaps
            ll g = h - t ;
            ll letters = width - g ;
            ll sp = w - letters ;
            string line = "" ;
            if(h == n - 1 || g == 0)
            {
                // step 3 : left justified
                for(ll j = t ; j <= h ; j++)
                {
                    line += words[j] ;
                    if(j < h)
                    {
                        line += ' ' ;
                    }
                }
                while((ll)line.size() < w)
                {
                    line += ' ' ;
                }
            }
            else
            {
                // step 4 : base spaces per gap, the first extra gaps get one more
                ll base = sp / g ;
                ll extra = sp % g ;
                for(ll j = 0 ; j <= g ; j++)
                {
                    line += words[t + j] ;
                    if(j == g)
                    {
                        continue ;
                    }
                    ll cnt = base ;
                    if(j < extra)
                    {
                        cnt++ ;
                    }
                    line += string(cnt , ' ') ;
                }
            }
            // step 5 : next line starts after h
            ans.push_back(line) ;
            t = h + 1 ;
        }
        return ans ;
    }
};
