/*
Minimum lines to cover all points  (NatWest OA; source: GeeksforGeeks)

Given N points in 2-dimensional space, we need to print the count of the
minimum number of lines which traverse through all these N points and which
go through a specific (xO, yO) point also.

Input format (assumed, statement gives none):
    N
    xO yO
    x1 y1
    ...
    xN yN

Output: the minimum number of lines.

Example:
    Input:
    5
    1 0
    -1 3
    4 3
    2 1
    -1 -2
    3 -3

    Output:
    2

    Explanation: every line must pass through (1, 0); two such lines are
    needed to cover all five points.
*/

#include <bits/stdc++.h>

#define int long long 
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


using namespace std;
int gcd ( int a , int b)
{
    if(  b == 0 )
    {
        return a ;
    }
    else
    {
        return gcd( b , a % b) ;
    }

}
int sign ( int x)
{
    if(x > 0 )
    {
        return 1 ;
    }
    else if ( x == 0 )
    {
        return 0 ;
    }
    else 
    {
        return - 1 ; 
    }

}
void solve()
{   
    int n ; 
    cin >> n ; 
    vector < pair < int , int > > a( n + 1 , {0,0}) ; 
    int x0 , y0 ; 
    cin >> x0 >> y0 ; 
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> a[i].fr >> a[i].sc ; 
    }
    set < pair < int , int > > s ; 
    for(int i = 1 ; i <= n ; i++)
    {
        int dx = a[i].fr - x0 ; 
        int dy = a[i].sc - y0 ;
        if(dx == 0 && dy == 0)
        {
            continue ;
        }
        if(dy==0)
        {
            s.insert({1,0});
        }
        else
        {
            int g = gcd(dx , dy) ;
            int sgn = sign(dx) * sign(dy) ;
            s.insert({sgn * abs(dx / g) , abs(dy / g)});
        }
    }
    cout << s.size() << endl ;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
}
