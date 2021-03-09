/*
 * @Description: 
 * @Author: notplus
 * @Date: 2021-03-05 20:05:01
 * @LastEditors: notplus
 * @LastEditTime: 2021-03-06 16:29:08
 */
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

typedef struct Tree
{
    Tree *left;
    Tree *right;
    int element;
} * Bintree;

int n, sum = 0;
std::stack<int> s;

void buildTree(Bintree &tree);
bool compareTree(Bintree tree1, Bintree tree2);

int main()
{
    scanf("%d", &n);
    while (n != 0)
    {
        int l;
        scanf("%d", &l);
        Bintree init = NULL;
        buildTree(init);
        for (int i = 0; i < l; i++)
        {
            Bintree tmp = NULL;
            buildTree(tmp);
            if (compareTree(init, tmp))
                printf("Yes\n");
            else
                printf("No\n");
            delete tmp;
        }
        delete init;
        scanf("%d", &n);
    }

    return 0;
}

Bintree insert(int element, Bintree tree)
{
    if (!tree)
    {
        tree = new Tree;
        tree->left = tree->right = NULL;
        tree->element = element;
    }
    else
    {
        if (element < tree->element)
            tree->left = insert(element, tree->left);
        else if (element > tree->element)
            tree->right = insert(element, tree->right);
    }
    return tree;
}

void buildTree(Bintree &tree)
{
    for (int i = 0; i < n; i++)
    {
        int ele;
        scanf("%d", &ele);
        tree = insert(ele, tree);
    }
}

bool compareTree(Bintree tree1, Bintree tree2)
{
    if (tree1 == NULL && tree2 == NULL)
        return true;
    if (tree1 == NULL || tree2 == NULL)
        return false;
    if (tree1->element != tree2->element)
        return false;
    return compareTree(tree1->left, tree2->left) && compareTree(tree1->right, tree2->right);
}