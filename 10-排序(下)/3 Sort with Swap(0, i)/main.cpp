#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1);
    int count = 0,t;
    for (int i = 0; i < n; i++)
    {  
        scanf("%d", &t);
        a[t]=i;
    }

    for (int i = 1; i < n; i++)
    {
        if (i!=a[i])
        {
            while (a[0]!=0)
            {
                swap(a[0],a[a[0]]);
                count++;
            }
            if (i!=a[i])
            {
                swap(a[0],a[i]);
                count++;
            }
        }
    }
    printf("%d", count);
    return 0;
}
