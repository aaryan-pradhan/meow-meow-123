#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Solution
{
public:
    int removeDuplicates(vector<int>& nums)
    {
        ll n = nums.size();
        ll k = 0;
        for (ll i = 0; i < n; i++)
        {
            auto x = nums[i];

            while (k >= 2 && nums[k - 1] == x && nums[k - 2] == x)
            {
                k--;
            }

            nums[k] = x;
            k++;
        }
        return k;
    }
};
