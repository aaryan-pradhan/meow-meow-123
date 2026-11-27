// orz
// 74. Search a 2D Matrix · LeetCode · Medium
//
// Question:
// you are given an m x n integer matrix with two properties: each row is sorted
// in non-decreasing order, and the first integer of each row is greater than the
// last integer of the previous row. given an integer target, return true if
// target is in the matrix and false otherwise. you must write a solution in
// O(log(m * n)) time.
// Example 1: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3  -> true
// Example 2: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13 -> false
// Constraints: 1 <= m, n <= 100, -10^4 <= matrix[i][j], target <= 10^4
//
// 1. Mathematical statement
//    read the matrix row by row into one list a[0 .. m * n - 1], so cell k is
//    a[k] = matrix[k / n][k % n]. the two properties say a is sorted.
//    answer: does some k have a[k] = target?
//
// 2. Brute force
//    look at all m * n cells. O(m * n) = 10^4, and the judge asks for O(log(m * n)).
//
// 3. What the brute force wastes
//    the whole matrix is one sorted list in disguise, and it never uses that.
//
// 4. Key breaking point
//    don't copy the matrix into a list: cell k is matrix[k / n][k % n].
//    k / n = how many full rows of n come before cell k = its row, k % n = what is left = its column.
//    then it is Search Insert Position on a: first k with a[k] >= target, then look at that cell.
//
// 5. Method
//    step 1 : check(k) returns true if a[k] = matrix[k / n][k % n] >= target.
//             false .. false true .. true along k because a is sorted.
//    step 2 : lo = 0, hi = m * n - 1, ans = m * n (m * n means "every cell is < target").
//    step 3 : the binary search template for the first k where check is true.
//    step 4 : target is in the matrix exactly when ans < m * n and a[ans] = target.
//
// 6. Why it works
//    a is sorted, so if target is anywhere it sits at the first cell >= target.
//    time O(log(m * n)), extra space O(1).
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
// step 1
bool check(ll k , vector<vector<int>>& matrix , ll target)
{
    // this returns true if cell k (reading row by row) is >= target
    ll n = matrix[0].size() ;
    ll row = k / n ;
    ll col = k % n ;
    if(matrix[row][col] >= target)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        ll m = matrix.size() ;
        ll n = matrix[0].size() ;
        // step 2
        ll lo = 0 , hi = m * n - 1 , ans = m * n ;
        // step 3 : first cell where check is true
        while(lo <= hi)
        {
            ll mid = lo + (hi - lo) / 2 ;
            if(check(mid , matrix , target))
            {
                ans = mid ;
                hi = mid - 1 ;
            }
            else
            {
                lo = mid + 1 ;
            }
        }
        // step 4
        if(ans == m * n)
        {
            return false ;
        }
        if(matrix[ans / n][ans % n] == target)
        {
            return true ;
        }
        else
        {
            return false ;
        }
    }
};
