#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

typedef struct Tree
{
    Tree* left;
    Tree* right;
    int element;
} * Bintree;

int n, sum = 0;
std::stack<int> s;

void buildTree(Bintree &tree);
void postOrder(Bintree tree);

int main()
{
    scanf("%d", &n);
    Tree *tree = new Tree;
    buildTree(tree);
    postOrder(tree);
    return 0;
}

void buildTree(Bintree &tree)
{
    if (sum == 2 * n)
        return;
    char str[5];
    scanf("%s", str);
    sum++;
    if (strlen(str) == 4)
    {
        int element;
        scanf("%d", &element);
        s.push(element);
        tree = new Tree;
        tree->left = NULL;
        tree->right = NULL;
        buildTree(tree->left);
        tree->element = s.top();
        s.pop();
        buildTree(tree->right);
    }
    return;
}

void postOrder(Bintree tree)
{
    if (tree == NULL)
        return;
    postOrder(tree->left);
    postOrder(tree->right);
    if (sum == 2 * n)
        printf("%d", tree->element);
    else
        printf(" %d", tree->element);
    sum++;
}