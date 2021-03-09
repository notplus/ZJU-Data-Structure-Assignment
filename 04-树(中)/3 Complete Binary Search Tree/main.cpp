#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> root;
vector<int> in;
vector<int> level;
int n;
int t = 0;

void InOrder(int node)
{
    if (node < n )
    {
        InOrder(node * 2 + 1);
        level[node] = in[t++];
        InOrder(node * 2 + 2);
    }
}

int main()
{
    scanf("%d", &n);
    root.resize(n);
    in.resize(n);
    level.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);
    sort(in.begin(), in.end());
    InOrder(0);
    printf("%d",level[0]);
    for (int i = 1; i < n; i++)
        printf(" %d",level[i]);

    return 0;
}
