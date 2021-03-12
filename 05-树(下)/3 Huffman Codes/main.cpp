#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

map<char, int> weight;

struct HuffmanTree
{
    int weight;
    HuffmanTree *left, *right;
};

struct MinHeap
{
    HuffmanTree **elements;
    int size;
    int capacity;
};

MinHeap *createMinHeap(int size)
{
    MinHeap *heap = new MinHeap;
    heap->capacity = size;
    heap->size = 0;
    heap->elements = new HuffmanTree *[size + 1];
    heap->elements[0] = new HuffmanTree;
    heap->elements[0]->weight = -1;
    return heap;
}

void insert(MinHeap *heap, HuffmanTree *tree)
{
    if (heap->size == heap->capacity)
        return;
    int i = ++heap->size;
    for (; heap->elements[i / 2]->weight > tree->weight; i /= 2)
        heap->elements[i] = heap->elements[i / 2];
    heap->elements[i] = tree;
}

HuffmanTree *deleteMin(MinHeap *heap)
{
    if (heap->size == 0)
        return NULL;
    HuffmanTree *min_item = heap->elements[1];
    HuffmanTree *tmp = heap->elements[heap->size--];
    int parent = 1;
    for (int child; parent * 2 <= heap->size; parent = child)
    {
        child = parent * 2;
        if ((child != heap->size) && heap->elements[child]->weight > heap->elements[child + 1]->weight)
            child++;
        if (tmp->weight < heap->elements[child]->weight)
            break;
        else
            heap->elements[parent] = heap->elements[child];
    }
    heap->elements[parent] = tmp;
    return min_item;
}

HuffmanTree *createHuffmanTree(MinHeap *heap, int n)
{
    for (int i = 0; i < n; i++)
    {
        char c;
        int f;
        scanf("%c %d ", &c, &f);
        HuffmanTree *tmp = new HuffmanTree;
        tmp->weight = f;
        tmp->left = tmp->right = NULL;
        insert(heap, tmp);
        weight[c] = f;
    }

    for (int i = 1; i < n; i++)
    {
        HuffmanTree *tmp = new HuffmanTree;
        tmp->left = deleteMin(heap);
        tmp->right = deleteMin(heap);
        tmp->weight = tmp->left->weight + tmp->right->weight;
        insert(heap, tmp);
    }
    return deleteMin(heap);
}

int computeAPL(HuffmanTree *tree, int height)
{
    if (tree->left == NULL && tree->right == NULL)
        return tree->weight * height;
    else
        return computeAPL(tree->left, height + 1) + computeAPL(tree->right, height + 1);
}

HuffmanTree *createTreeNode(HuffmanTree *tree)
{
    if (!tree)
    {
        tree = new HuffmanTree;
        tree->left = tree->right = NULL;
    }
    return tree;
}

bool judgeAtNode(HuffmanTree *tree)
{
    stack<HuffmanTree *> s;

    while (tree || !s.empty())
    {
        if (tree)
        {
            if (tree->weight && (tree->left || tree->right))
                return true;
            s.push(tree);
            tree = tree->left;
        }
        else
        {
            tree = s.top();
            tree = tree->right;
            s.pop();
        }
    }
    return false;
}

bool judge(int n, int optim_apl)
{
    int apl = 0;
    HuffmanTree *tree = new HuffmanTree;
    tree->left = tree->right = NULL;
    for (int i = 0; i < n; i++)
    {
        HuffmanTree *p = tree;
        char c;
        string str;
        cin >> c >> str;
        apl += str.length() * weight[c];
        for (int j = 0; j < str.length(); j++)
        {
            if (str[j] == '0')
            {
                p->left = createTreeNode(p->left);
                p = p->left;
            }
            else if (str[j] == '1')
            {
                p->right = createTreeNode(p->right);
                p = p->right;
            }
        }
        if (p->weight > 0)
            return false;
        p->weight = weight[c];
    }
    if (apl != optim_apl || judgeAtNode(tree))
        return false;
    else
        return true;
}

int main()
{
    int N;
    scanf("%d\n", &N);
    HuffmanTree *root = createHuffmanTree(createMinHeap(N), N);
    int min_apl = computeAPL(root, 0);
    int count;
    scanf("%d\n", &count);
    for (int i = 0; i < count; i++)
    {
        if (judge(N, min_apl))
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}
