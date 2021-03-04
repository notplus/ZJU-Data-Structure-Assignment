/**
 * @file main.cpp
 * @author notplus (notplus@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode
{
    ElementType element;
    Tree left;
    Tree right;
} T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode T[]);
int Issomorphic(Tree R1, Tree R2);

int main()
{
    Tree R1 = BuildTree(T1);
    Tree R2 = BuildTree(T2);
    if (Issomorphic(R1, R2))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

Tree BuildTree(struct TreeNode T[])
{
    int N, root = Null, check[MaxTree], i;
    char left, right;
    scanf("%d\n", &N);
    if (N)
    {
        for (i = 0; i < N; i++)
            check[i] = 0;
        for (i = 0; i < N; i++)
        {
            scanf("%c %c %c\n", &T[i].element, &left, &right);

            if (left != '-')
            {
                T[i].left = left - '0';
                check[T[i].left] = 1;
            }
            else
                T[i].left = Null;
            if (right != '-')
            {
                T[i].right = right - '0';
                check[T[i].right] = 1;
            }
            else
                T[i].right = Null;
        }
        for (i = 0; i < N; i++)
            if (!check[i])
                break;
        root = i;
    }
    return root;
}

int Issomorphic(Tree R1, Tree R2)
{
    if (R1 == Null && R2 == Null)
        return 1;
    if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null))
        return 0;
    if (T1[R1].element != T2[R2].element)
        return 0;
    if (T1[R1].left == Null && T2[R2].left == Null)
        return Issomorphic(T1[R1].right, T2[R2].right);
    if (T1[R1].left != Null && T2[R2].left != Null && T1[T1[R1].left].element == T2[T2[R2].left].element)
        return Issomorphic(T1[R1].left, T2[R2].left) && Issomorphic(T1[R1].right, T2[R2].right);
    else
        return Issomorphic(T1[R1].left, T2[R2].right) && Issomorphic(T1[R1].right, T2[R2].left);
}