#include <iostream>

using namespace std;

int *Create(int size)
{
    int *set = new int[size + 1];
    for (int i = 0; i < size + 1; i++)
        set[i] = -1;
    return set;
}

int Find(int S[], int x)
{
    while (S[x] >= 0)
        x = S[x];
    return x;
}

void Union(int S[], int x, int y)
{
    int root1 = Find(S, x);
    int root2 = Find(S, y);
    if (S[root1] < S[root2]) // root2's height < root1's height
        S[root2] = root1;
    else
    {
        if (S[root1] == S[root2])
            S[root2]--;
        S[root1] = root2;
    }
}

void PrintComponent(int S[], int size)
{
    int cnt = 0;
    for (int i = 1; i <= size; i++)
        if (S[i] < 0)
            cnt++;
    if (cnt == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", cnt);
}

int main()
{
    int N;
    scanf("%d\n", &N);
    int *set = Create(N);

    char command;
    scanf("%c", &command);
    while (command != 'S')
    {
        int x, y;
        scanf("%d %d\n", &x, &y);
        if (command == 'I')
            Union(set, x, y);
        else if (command == 'C')
        {
            if (Find(set, x) == Find(set, y))
                printf("yes\n");
            else
                printf("no\n");
        }
        scanf("%c", &command);
    }

    PrintComponent(set, N);
    return 0;
}
