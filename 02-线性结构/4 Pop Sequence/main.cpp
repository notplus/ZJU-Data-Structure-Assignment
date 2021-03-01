/*
 * @Description: 
 * @Author: notplus
 * @Date: 2021-03-01 19:12:39
 * @LastEditors: notplus
 * @LastEditTime: 2021-03-01 19:42:08
 */

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main()
{
    int m, n, k;
    cin >> m >> n >> k;
    for (int i = 0; i < k; i++)
    {
        bool flag = false;
        vector<int> seq(n + 1);
        for (int j = 1; j <= n; j++)
            cin >> seq[j];
        stack<int> sta;
        int current = 1;
        for (int j = 1; j <= n; j++)
        {
            sta.push(j);
            if (sta.size() > m)
                break;
            while (!sta.empty() && sta.top() == seq[current])
            {
                sta.pop();
                current += 1;
            }
        }
        if (current == n + 1)
            flag = true;
        if (flag)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
