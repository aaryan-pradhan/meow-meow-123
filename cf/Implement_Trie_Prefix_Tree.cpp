// orz
// 208. Implement Trie (Prefix Tree) · LeetCode · Medium
//
// Question:
// a trie (prefix tree) stores a set of strings so that words and prefixes can be
// looked up fast. implement the class Trie:
//   Trie()                  makes an empty trie.
//   void insert(word)       adds word to the trie.
//   bool search(word)       true if word was inserted before, else false.
//   bool startsWith(prefix) true if some inserted word starts with prefix, else false.
// Example 1: ["Trie","insert","search","search","startsWith","insert","search"]
//            [[],["apple"],["apple"],["app"],["app"],["app"],["app"]]
//            -> [null,null,true,false,true,null,true]
// Constraints: 1 <= word.length, prefix.length <= 2000, only lowercase English letters,
//              at most 3 * 10^4 calls in total to insert, search and startsWith.
//
// 1. Mathematical statement
//    keep a set S of strings.
//    insert(w) : S = S + {w}.
//    search(w) : is w in S ?
//    startsWith(p) : is there a w in S with w[0 .. |p| - 1] = p ?
//
// 2. Brute force
//    keep every inserted word in a list. search compares w with every word,
//    startsWith compares p with the first |p| letters of every word.
//    O(|S| * L) per call: 3 * 10^4 calls on up to 3 * 10^4 words of 2000 letters. dead.
//
// 3. What the brute force wastes
//    words that share a start ("apple", "apply", "app") get that same start compared
//    again for every one of them. the answer only needs one walk over the letters of the query.
//
// 4. Key breaking point
//    put all words into one rooted tree of letters. every node is a prefix of some word,
//    and the edge out of a node with letter c goes to (that prefix + c).
//    shared starts become shared nodes. a query is then one walk from the root, one letter per step.
//    it is my g with node ids, except a node has at most 26 children and I pick the child by its letter.
//
// 5. Method
//    step 1 : the trie is two arrays. node 0 = root = the empty prefix.
//             nxt[node][c] = id of the child of node by letter c (c = 0 for 'a' .. 25 for 'z'), 0 = no child.
//             0 can mean "no child" because the root is never anyone's child.
//             endhere[node] = 1 if some inserted word ends exactly at node.
//    step 2 : newnode() adds an empty row (26 zeros) to nxt and a 0 to endhere, and returns the new id.
//             the constructor calls it once to make the root.
//    step 3 : insert(w) : node = 0. for each letter c of w : if nxt[node][c] is 0, make a new node
//             and store its id there. then node = nxt[node][c]. at the end endhere[node] = 1.
//    step 4 : walk(s) : node = 0. for each letter c of s : if nxt[node][c] is 0, no word starts with s,
//             return -1. else node = nxt[node][c]. at the end return node, the node of prefix s.
//    step 5 : search(w) : the node of w exists and endhere[node] = 1.
//             "exists" alone is wrong: "app" is a node inside "apple" but was never inserted.
//    step 6 : startsWith(p) : the node of p exists. every node lies on the path of an inserted word.
//
// 6. Why it works
//    walking s from the root reaches exactly the node of prefix s, and that node exists iff
//    some inserted word starts with s (insert makes every node on the path of its word, nothing else
//    makes nodes). endhere marks exactly the inserted words.
//    time O(L) per call, space O(26 * total inserted letters).
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
class Trie {
public:
    // step 1 : the trie as two arrays, node 0 = root
    vector < vector < ll > > nxt ; // nxt[node][c] = child of node by letter c, 0 means no child
    vector < ll > endhere ;        // endhere[node] = 1 if an inserted word ends exactly at node
    ll newnode()
    {
        // step 2 : this makes an empty node and returns its id
        nxt.push_back(vector < ll > (26 , 0)) ;
        endhere.push_back(0) ;
        return (ll)nxt.size() - 1 ;
    }
    ll walk(string& s)
    {
        // step 4 : this returns the node of prefix s, or -1 if no inserted word starts with s
        ll node = 0 ;
        for(ll i = 0 ; i < (ll)s.size() ; i++)
        {
            ll c = s[i] - 'a' ;
            if(nxt[node][c] == 0)
            {
                return -1 ;
            }
            node = nxt[node][c] ;
        }
        return node ;
    }

    Trie() {
        // step 2 : the root, id 0
        newnode() ;
    }

    void insert(string word) {
        // step 3 : walk down, make the missing nodes, mark the last one
        ll node = 0 ;
        for(ll i = 0 ; i < (ll)word.size() ; i++)
        {
            ll c = word[i] - 'a' ;
            if(nxt[node][c] == 0)
            {
                // newnode() grows nxt, so make the node first and store its id after (safe in every C++ version)
                ll id = newnode() ;
                nxt[node][c] = id ;
            }
            node = nxt[node][c] ;
        }
        endhere[node] = 1 ;
    }

    bool search(string word) {
        // step 5 : the node exists and a word ends there
        ll node = walk(word) ;
        if(node == -1)
        {
            return false ;
        }
        if(endhere[node] == 1)
        {
            return true ;
        }
        else
        {
            return false ;
        }
    }

    bool startsWith(string prefix) {
        // step 6 : the node exists
        ll node = walk(prefix) ;
        if(node == -1)
        {
            return false ;
        }
        else
        {
            return true ;
        }
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
