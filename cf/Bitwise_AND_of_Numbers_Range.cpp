// orz
// 201. Bitwise AND of Numbers Range · LeetCode · Medium
//
// Question:
// given two integers left and right that represent the range [left, right], return
// the bitwise AND of all numbers in this range, inclusive.
// Example 1: left = 5, right = 7              -> 4   (101 & 110 & 111 = 100)
// Example 2: left = 0, right = 0              -> 0
// Example 3: left = 1, right = 2147483647     -> 0
// Constraints: 0 <= left <= right <= 2^31 - 1
//
// 1. Mathematical statement
//    return left & (left + 1) & .. & right.
//    "&" looks at each bit place on its own: the result bit is 1 only if every number has a 1 there.
//
// 2. Brute force
//    AND every number from left to right. up to 2^31 numbers. dead.
//
// 3. What the brute force wastes
//    a bit place becomes 0 as soon as one number in the range has a 0 there,
//    and in a long range the low bits flip all the time. most of the work is on bits already dead.
//
// 4. Key breaking point
//    write left and right in binary. they agree on some top bits (the common prefix), then at the
//    first place p from the top where they differ, left has 0 and right has 1 (because left < right).
//    (a) the prefix survives: every x in [left , right] has the same top bits, since x sits between
//        two numbers that both start with that prefix.
//    (b) every place <= p dies: m = prefix, then 1 at p, then all 0 is <= right (right has 1 at p),
//        and m - 1 = prefix, then 0 at p, then all 1 is >= left (left has 0 at p). so both m - 1 and m
//        are in the range, and at every place <= p one of them has a 0.
//    so the answer = the common prefix, followed by zeros.
//    bit tools: x >> 1 drops the lowest bit of x (everything slides one place right).
//               x << s adds s zeros at the bottom (everything slides s places left).
//
// 5. Method
//    step 1 : shift = 0.
//    step 2 : while left != right: drop the lowest bit of both (>> 1), shift++.
//             when they become equal, only the common prefix is left.
//    step 3 : return left << shift: the prefix back in its place, zeros under it.
//
// 6. Why it works
//    step 2 stops exactly when everything below the common prefix has been dropped, and (a) + (b)
//    say the answer is that prefix with zeros under it. left = right gives left itself.
//    time O(31), extra space O(1).
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
    int rangeBitwiseAnd(int left, int right) {
        ll l = left ;
        ll r = right ;
        // step 1
        ll shift = 0 ;
        // step 2 : drop bits until only the common prefix is left
        while(l != r)
        {
            l = l >> 1 ;
            r = r >> 1 ;
            shift++ ;
        }
        // step 3 : the prefix with zeros under it
        return l << shift ;
    }
};
