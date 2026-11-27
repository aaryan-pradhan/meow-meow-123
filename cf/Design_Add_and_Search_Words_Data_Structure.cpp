// orz
// 211. Design Add and Search Words Data Structure · LeetCode · Medium
//
// Question:
// design a data structure that supports adding new words and finding if a string
// matches any word added before. implement the class WordDictionary:
//   WordDictionary()     makes an empty dictionary.
//   void addWord(word)   adds word to the dictionary.
//   bool search(word)    true if some added word matches word, else false.
//                        word may contain dots '.', and a dot matches any one letter.
// Example 1: ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
//            [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
//            -> [null,null,null,null,false,true,true,true]
// Constraints: 1 <= word.length <= 25, word in addWord is lowercase letters,
//              word in search is '.' or lowercase letters, at most 2 dots in a search word,
//              at most 10^4 calls in total to addWord and search.
//
// 1. Mathematical statement
//    keep a set S of strings. addWord(w) : S = S + {w}.
//    search(p) : is there a w in S with |w| = |p| and, for every i, p[i] = '.' or p[i] = w[i] ?
//
// 2. Brute force
//    keep a list of words, compare p with every word letter by letter.
//    O(|S| * 25) per search, 10^4 * 10^4 * 25 = 2.5 * 10^9. dead.
//
// 3. What the brute force wastes
//    words with the same start get that start compared again and again, and a letter of p
//    that matches no word at that place still scans the whole list.
//
// 4. Key breaking point
//    it is Implement Trie (208) with one change. put the words in a trie (node 0 = root).
//    a letter of p = follow one child. a dot = try all 26 children.
//    at most 2 dots, so one search walks at most 26 * 26 paths of length <= 25.
//
// 5. Method
//    step 1 : the trie as two arrays (same as 208). nxt[node][c] = child of node by letter c, 0 = no child.
//             endhere[node] = 1 if an added word ends exactly at node.
//    step 2 : newnode() adds an empty node and returns its id. the constructor makes the root, id 0.
//    step 3 : addWord(w) = trie insert : walk down, make a missing child when needed, endhere[last] = 1.
//    step 4 : rec(node , i) = true if p[i ..] can be matched going down from node and ends on a word end.
//             i = |p| : true iff endhere[node] = 1.
//    step 5 : p[i] is a letter c : go to nxt[node][c] if it exists, else false.
//    step 6 : p[i] is a dot : try every child that exists, true as soon as one of them works.
//    step 7 : search(p) = rec(0 , 0).
//
// 6. Why it works
//    the nodes at depth i below the root are exactly the length-i prefixes of the added words.
//    rec follows every child that the pattern allows (one for a letter, all for a dot),
//    so it reaches exactly the nodes whose prefix matches p[0 .. i - 1], and at the end
//    endhere tells if that prefix is a whole added word.
//    time O(L) per addWord, O(26^2 * L) per search (at most 2 dots), space O(26 * total letters).
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
class WordDictionary {
public:
    // step 1 : the trie as two arrays, node 0 = root
    vector < vector < ll > > nxt ; // nxt[node][c] = child of node by letter c, 0 means no child
    vector < ll > endhere ;        // endhere[node] = 1 if an added word ends exactly at node
    ll newnode()
    {
        // step 2 : this makes an empty node and returns its id
        nxt.push_back(vector < ll > (26 , 0)) ;
        endhere.push_back(0) ;
        return (ll)nxt.size() - 1 ;
    }
    bool rec(ll node , ll i , string& p)
    {
        // step 4 : this returns true if p[i ..] can be matched going down from node, ending on a word end
        if(i == (ll)p.size())
        {
            if(endhere[node] == 1)
            {
                return true ;
            }
            else
            {
                return false ;
            }
        }
        if(p[i] == '.')
        {
            // step 6 : a dot, try every child
            for(ll c = 0 ; c < 26 ; c++)
            {
                if(nxt[node][c] == 0)
                {
                    continue ;
                }
                if(rec(nxt[node][c] , i + 1 , p))
                {
                    return true ;
                }
            }
            return false ;
        }
        else
        {
            // step 5 : a letter, only one child
            ll c = p[i] - 'a' ;
            if(nxt[node][c] == 0)
            {
                return false ;
            }
            return rec(nxt[node][c] , i + 1 , p) ;
        }
    }

    WordDictionary() {
        // step 2 : the root, id 0
        newnode() ;
    }

    void addWord(string word) {
        // step 3 : trie insert
        ll node = 0 ;
        for(ll i = 0 ; i < (ll)word.size() ; i++)
        {
            ll c = word[i] - 'a' ;
            if(nxt[node][c] == 0)
            {
                // newnode() grows nxt, so make the node first and store its id after
                ll id = newnode() ;
                nxt[node][c] = id ;
            }
            node = nxt[node][c] ;
        }
        endhere[node] = 1 ;
    }

    bool search(string word) {
        // step 7
        return rec(0 , 0 , word) ;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
