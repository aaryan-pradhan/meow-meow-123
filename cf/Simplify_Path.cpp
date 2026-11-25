#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Solution
{
public:
    string simplifyPath(string path)
    {
        ll n = path.size();

        vector<string> parts;
        string cur = "";
        for (ll i = 0; i < n; i++)
        {
            if (path[i] == '/')
            {
                parts.push_back(cur);
                cur = "";
            }
            else
            {
                cur += path[i];
            }
        }
        parts.push_back(cur);

        vector<string> st;
        for (auto x : parts)
        {
            if (x == "" || x == ".")
            {
                continue;
            }
            if (x == "..")
            {
                if (!st.empty())
                {
                    st.pop_back();
                }
                continue;
            }
            st.push_back(x);
        }

        string ans = "";
        for (auto x : st)
        {
            ans += "/";
            ans += x;
        }
        if (ans == "")
        {
            ans = "/";
        }
        return ans;
    }
};
