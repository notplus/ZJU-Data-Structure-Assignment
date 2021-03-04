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

#include <iostream>
#include <queue>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode
{
    ElementType element;
    Tree left;
    Tree right;
} T1[MaxTree];

Tree BuildTree(struct TreeNode T[]);
void ListLeaves(Tree root);

int main()
{
    ListLeaves(BuildTree(T1));
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
            scanf("%c %c\n", &left, &right);

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

void ListLeaves(Tree root)
{
    std::queue<Tree> q;
    Tree node;
    if (root != Null)
    {
        q.push(root);
        node = root;
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            if (T1[node].left == Null && T1[node].right == Null)
            {
                if (q.empty())
                    printf("%d", node);
                else
                    printf("%d ", node);
            }
            if (T1[node].left != Null)
                q.push(T1[node].left);
            if (T1[node].right != Null)
                q.push(T1[node].right);
        }
    }
}