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


using namespace std;
ll gcd ( ll a , ll b)
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
ll sign ( ll x)
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
    ll n ; 
    cin >> n ; 
    vector < pair < ll , ll > > a( n + 1 , {0,0}) ; 
    ll x0 , y0 ; 
    cin >> x0 >> y0 ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        cin >> a[i].fr >> a[i].sc ; 
    }
    set < pair < ll , ll > > s ; 
    for(ll i = 1 ; i <= n ; i++)
    {
        ll dx = a[i].fr - x0 ; 
        ll dy = a[i].sc - y0 ;
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
            ll g = gcd(dx , dy) ;
            ll sgn = sign(dx) * sign(dy) ;
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
