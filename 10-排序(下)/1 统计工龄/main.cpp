#include <iostream>
using namespace std;

int main()
{
    int n, a;
    scanf("%d", &n);
    int age[51] = {};
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        age[a]++;
    }
    for (int i = 0; i < 51; i++)
        if (age[i])
            printf("%d:%d\n",i,age[i]);
    
    return 0;
}
