// orz
// 71. Simplify Path · LeetCode · Medium
//
// Question:
// given an absolute Unix-style path (it starts with '/'), return its simplified
// canonical path. the rules of the file system:
//   '.' is the current directory, '..' is the parent directory, and any run of
//   slashes like '//' counts as one '/'. any other name made of periods, like
//   '...' or '....', is a normal file or directory name.
// the canonical path starts with a single '/', directories are split by a single
// '/', it does not end with '/' (unless it is just the root), and it has no '.'
// or '..' parts.
// Example 1: path = "/home/"                            -> "/home"
// Example 2: path = "/home//foo/"                       -> "/home/foo"
// Example 3: path = "/home/user/Documents/../Pictures"  -> "/home/user/Pictures"
// Example 4: path = "/../"                              -> "/"
// Example 5: path = "/.../a/../b/c/../d/./"             -> "/.../b/d"
// Constraints: 1 <= path.length <= 3000, path is English letters, digits, '.', '/'
//              or '_', path is a valid absolute Unix path
//
// 1. Mathematical statement
//    cut path at every '/' into parts. start at the root and read the parts left to
//    right: "" and "." stay where you are, ".." goes up one level (the root stays the
//    root), any other part goes down into that directory. output where you end up,
//    as '/' + names joined by '/' ("/" for the root).
//
// 2. Brute force
//    rewrite the string until it stops changing: squash "//" to "/", delete "/./",
//    delete "/name/..", fix the ends. each rewrite is O(n), up to O(n) rewrites,
//    O(n^2), and the edge cases ("/..." vs "/..", the root) are easy to get wrong.
//
// 3. What the brute force wastes
//    it rescans the whole string after every rewrite. but ".." only ever cancels
//    the LAST directory that is still open, so the open directories can be kept
//    in order as they are read.
//
// 4. Key breaking point
//    the current directory is a list of names from the root. going down pushes a
//    name, ".." pops the last one. "last in, first out" is a stack.
//
// 5. Method
//    step 1 : split path on '/' into parts (runs of '/' make "" parts).
//    step 2 : for every part: "" or "." -> skip.
//             ".." -> pop the last name if there is one (at the root, stay).
//             anything else -> push it.
//    step 3 : join: ans = "/" + name for every name on the stack, bottom to top.
//    step 4 : an empty stack means the root, ans = "/".
//
// 6. Why it works
//    after each part the stack is exactly the list of directories from the root to
//    where the path stands now, so after the last part it is the final directory.
//    step 3 writes it in the canonical form: one '/' before each name, no trailing '/'.
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
    string simplifyPath(string path) {
        ll n = path.size() ;
        // step 1 : split on '/'
        vector < string > parts ;
        string cur = "" ;
        for(ll i = 0 ; i < n ; i++)
        {
            if(path[i] == '/')
            {
                parts.push_back(cur) ;
                cur = "" ;
            }
            else
            {
                cur += path[i] ;
            }
        }
        parts.push_back(cur) ;
        // step 2 : st stores the directories from the root to where we stand
        vector < string > st ;
        for(auto x : parts)
        {
            if(x == "" || x == ".")
            {
                continue ;
            }
            else if(x == "..")
            {
                if(!st.empty())
                {
                    st.pop_back() ;
                }
                continue ;
            }
            else
            {
                st.push_back(x) ;
            }
        }
        // step 3 : join the names
        string ans = "" ;
        for(auto x : st)
        {
            ans += "/" ;
            ans += x ;
        }
        // step 4 : the root
        if(ans == "")
        {
            ans = "/" ;
        }
        return ans ;
    }
};
