/*
Warp divergence masks (source: NVIDIA OA)

(Problem description above "Output Format" not yet captured.)

Output Format
Two lines:
 - Line 1: maskA maskB, each written as 0x followed by exactly 8 uppercase
   hexadecimal digits (zero-padded), for example 0x0000FFFF.
 - Line 2: the number of passes, 1 or 2.

Constraints
Exactly 32 values are given, each 0 or 1.

Example 1
Input:
1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0
Output:
0x0F0F0F0F 0xF0F0F0F0
2
Threads 0-3, 8-11, 16-19 and 24-27 take path A, which sets the low nibble of
every byte of mask A. All other threads take path B. Both paths are used, so
the warp needs 2 passes.

Example 2
Input:
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
Output:
(not yet captured)
*/
#include <bits/stdc++.h>
using namespace std;

void solve()
{
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
