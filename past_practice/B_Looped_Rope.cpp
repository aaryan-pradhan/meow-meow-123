// orz
#include <bits/stdc++.h>
#include<iostream>
#include<iomanip>
#define ll long long 
#define endl "\n"
#define fr first
#define sc second
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define mp make_pair
#define PI acos(-1) 
#define py cout << "Yes" << endl
#define pn cout << "No" << endl

using namespace std;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int h , w ;


bool check ( int x , int y , vector<vector<char>> &v)
{
    int c = 0 ;
    for( ll i = 0 ; i < 4 ; i++)
    {
        int newx = x + dx[i] ;
        int newy = y + dy[i] ;
        if(newx >=0 && newx < h && newy >= 0 && newy < w)
        {
            if(v[newx][newy] == '#')
            {
                c++ ; 
            }
        }
    }
    if(c==2 || c==4)
    {
        return true ;
    }
    return false ;
}
void solve() 
{

    cin >> h >> w ; 
    vector<vector<char>> v(h,vector<char>(w)) ;
    for(int i = 0 ; i < h ; i++)
    {
        for(int j = 0 ; j < w ; j++)
        {
            cin >> v[i][j] ;
        }
    }
    for(int i = 0 ; i < h ; i++)
    {
        for(int j = 0 ; j < w ; j++)
        {
            if(v[i][j] == '#')
            {
                if(check(i,j,v) == false)
                {
                    pn ; 
                    return ;
                }
            }
        }
    }
    py ; 



   






}
signed main() 
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    solve() ; 
}
    
  