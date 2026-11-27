// orz
// 135. Candy · LeetCode · Hard
//
// Question:
// n children stand in a line and ratings[i] is the rating of child i. give them
// candies so that every child gets at least one candy, and a child with a higher
// rating than a neighbour gets more candies than that neighbour.
// return the minimum total number of candies.
// Example 1: ratings = [1,0,2] -> 5   (2, 1, 2)
// Example 2: ratings = [1,2,2] -> 4   (1, 2, 1 : equal neighbours need nothing)
// Constraints: 1 <= n <= 2 * 10^4, 0 <= ratings[i] <= 2 * 10^4
//
// 1. Mathematical statement
//    find c[0 .. n - 1] with c[i] >= 1,
//    a[i] > a[i - 1] => c[i] > c[i - 1] (left rule),
//    a[i] > a[i + 1] => c[i] > c[i + 1] (right rule),
//    and minimise c[0] + .. + c[n - 1].
//
// 2. Brute force
//    start everyone at 1. sweep the line and fix every broken rule by giving
//    c[i] = c[neighbour] + 1. repeat sweeps until nothing changes.
//    a long decreasing run fixes one child per sweep, so O(n^2), 4 * 10^8. dead.
//
// 3. What the brute force wastes
//    each sweep pushes the information only one child further along the line,
//    and both rules get mixed in the same sweep.
//
// 4. Key breaking point
//    split the two rules. the left rule only looks left, so one left to right pass
//    settles it: L[i] = L[i - 1] + 1 when a[i] > a[i - 1], else 1.
//    the right rule only looks right: R[i] = R[i + 1] + 1 when a[i] > a[i + 1], else 1.
//    a child must satisfy both, so c[i] = max(L[i] , R[i]).
//
// 5. Method
//    step 1 : L[i] = length of the increasing run ending at i, walking left to right.
//    step 2 : R[i] = length of the decreasing run starting at i, walking right to left.
//    step 3 : ans = sum of max(L[i] , R[i]).
//
// 6. Why it works
//    lower bound : any valid c has c[i] >= L[i] (induction along the left rule,
//    c[i] > c[i - 1] >= L[i - 1]) and c[i] >= R[i] (same from the right).
//    valid : if a[i] > a[i - 1] then R[i - 1] = 1 (a[i - 1] is not bigger than a[i]),
//    so c[i - 1] = L[i - 1] < L[i] <= c[i]. the right rule is the mirror.
//    so max(L , R) is valid and every valid c is at least it : it is the minimum.
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
    int candy(vector<int>& ratings) {
        ll n = ratings.size() ;
        // step 1 : L[i] stores the candies child i needs for the left rule alone
        vector < ll > L(n , 1) ;
        for(ll i = 1 ; i < n ; i++)
        {
            if(ratings[i] > ratings[i - 1])
            {
                L[i] = L[i - 1] + 1 ;
            }
            else
            {
                continue ;
            }
        }
        // step 2 : R[i] stores the candies child i needs for the right rule alone
        vector < ll > R(n , 1) ;
        for(ll i = n - 2 ; i >= 0 ; i--)
        {
            if(ratings[i] > ratings[i + 1])
            {
                R[i] = R[i + 1] + 1 ;
            }
            else
            {
                continue ;
            }
        }
        // step 3 : both rules at once
        ll ans = 0 ;
        for(ll i = 0 ; i < n ; i++)
        {
            ans += max(L[i] , R[i]) ;
        }
        return ans ;
    }
};
