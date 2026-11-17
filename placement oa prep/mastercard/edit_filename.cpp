/*
 * Edit Filename — Mastercard OA
 *
 * An app compares a "Filename" with a "Dictionary String" and applies operations
 * on the Filename to make it exactly equal to the Dictionary String:
 *   I)   Insert:  insert a character in any position within the Filename.
 *   II)  Remove:  remove a character from any position in the Filename.
 *   III) Replace: replace a character with a new character in any position in the Filename.
 * Find the minimum number of operations N to make Filename exactly equal to the
 * Dictionary String. If no operations are performed, print "0".
 *
 * Constraints:
 *   1 < length(Filename), length(Dictionary String) <= 25
 *   Alphabets and numbers only. Stated "case insensitive", but the sample only
 *   gives 5 when letters are compared case-sensitively.
 *
 * Input : line 1 Filename, line 2 Dictionary String
 * Output: N
 *
 * Sample: Hello / There -> 5
 */
#include <bits/stdc++.h>
using namespace std;

int editFilename(string f, string d)
{
    int n = f.size(), m = d.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = j;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + (f[i - 1] != d[j - 1])});
        }
    }
    return dp[n][m];
}

int main() {
    string file,dict;
    cin>>file;
    cin>>dict;
    cout<<editFilename(file,dict);
    return 0;
}
