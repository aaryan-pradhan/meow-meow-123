/*
Maximum Memory Collection with Row Limit
Difficulty: Hard

You are given an n x m integer matrix memory, where memory[i][j] represents
the amount of memory that can be collected from cell (i, j).
You start at the top-left cell (0, 0) and want to reach the bottom-right cell (n - 1, m - 1).
At every cell, you may perform exactly one of the following actions:
1. Read the current cell and collect its memory value.
2. Skip the current cell and collect nothing.
After that, you must move either:
- one cell to the right, or
- one cell down,
provided the move stays inside the matrix.

Constraint:
For every row, you may read at most k cells from that row.
Return the maximum total memory that can be collected.

Example 1:
Input:
memory = [
  [4, 5, 9],
  [1, 2, 4],
  [6, 5, 2]
]
k = 2
Output: 21 (or optimal achievable value)

Example 2:
Input:
memory = [
  [5, 1],
  [3, 7]
]
k = 1
Output: 12

Constraints:
1 <= n, m <= 200
1 <= memory[i][j] <= 10^9
1 <= k <= m
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumMemory(vector<vector<int>>& memory, int k) {
        // Write your code here
        return 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Testing logic here

    return 0;
}

