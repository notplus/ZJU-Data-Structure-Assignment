/*
 * @Description: 
 * @Author: notplus
 * @Date: 2021-03-05 20:05:01
 * @LastEditors: notplus
 * @LastEditTime: 2021-03-08 19:32:26
 */

#include <cstdio>
#include <cmath>

using namespace std;

typedef struct Tree
{
    Tree *left;
    Tree *right;
    int element;
    int bf;
} * Bintree;

Bintree insert(int element, Bintree tree, Bintree &new_leaf);
int computeDepth(Bintree tree);
void computeBlanceFactor(Bintree tree);
Bintree adjustTree(Bintree tree, Bintree new_leaf);
bool flag = true;

int main()
{
    int n;
    scanf("%d", &n);
    Bintree root = NULL;

    for (int i = 0; i < n; i++)
    {
        Bintree new_leaf = NULL;
        int ele;
        scanf("%d", &ele);
        root = insert(ele, root, new_leaf);
        computeBlanceFactor(root);
        flag = true;
        root = adjustTree(root, new_leaf);
    }
    if (root)
        printf("%d\n", root->element);

    return 0;
}

Bintree insert(int element, Bintree tree, Bintree &new_leaf)
{
    if (!tree)
    {
        tree = new Tree;
        tree->left = tree->right = NULL;
        tree->element = element;
        new_leaf = tree;
    }
    else
    {
        if (element < tree->element)
            tree->left = insert(element, tree->left, new_leaf);
        else if (element > tree->element)
            tree->right = insert(element, tree->right, new_leaf);
    }
    return tree;
}

int computeDepth(Bintree tree)
{
    if (tree == NULL)
        return 0;
    return fmax(computeDepth(tree->left), computeDepth(tree->right)) + 1;
}

void computeBlanceFactor(Bintree tree)
{
    if (tree == NULL)
        return;
    tree->bf = computeDepth(tree->left) - computeDepth(tree->right);
    computeBlanceFactor(tree->left);
    computeBlanceFactor(tree->right);
}

void postOrder(Bintree tree, Bintree &trouble)
{
    if (tree == NULL)
        return;
    postOrder(tree->left, trouble);
    postOrder(tree->right, trouble);
    if (abs(tree->bf) == 2 && flag)
    {
        trouble = tree;
        flag = false;
    }
}

Bintree adjustTree(Bintree tree, Bintree new_leaf)
{
    Bintree trouble = NULL;
    postOrder(tree, trouble);
    if (trouble == NULL)
    {
    }
    else if (new_leaf->element < trouble->element && new_leaf->element < trouble->left->element) // LL
    {
        int A = trouble->element;
        Bintree B = trouble->left;
        trouble->element = B->element;
        B->element = A;
        trouble->left = B->left;
        B->left = B->right;
        B->right = trouble->right;
        trouble->right = B;
    }
    else if (new_leaf->element > trouble->element && new_leaf->element > trouble->right->element) // RR
    {
        int A = trouble->element;
        Bintree B = trouble->right;
        trouble->element = B->element;
        B->element = A;
        trouble->right = B->right;
        B->right = B->left;
        B->left = trouble->left;
        trouble->left = B;
    }
    else if (new_leaf->element < trouble->element && new_leaf->element > trouble->left->element) // LR
    {
        int A = trouble->element;
        Bintree B = trouble->left;
        Bintree C = B->right;
        trouble->element = C->element;
        C->element = A;
        B->right = C->left;
        C->left = C->right;
        C->right = trouble->right;
        trouble->right = C;
    }
    else if (new_leaf->element > trouble->element && new_leaf->element < trouble->right->element) // RL
    {
        int A = trouble->element;
        Bintree B = trouble->right;
        Bintree C = B->left;
        trouble->element = C->element;
        C->element = A;
        B->left = C->right;
        C->right = C->left;
        C->left = trouble->left;
        trouble->left = C;
    }
    return tree;
}