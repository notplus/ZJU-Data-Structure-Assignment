#include <iostream>
#include <vector>

using namespace std;

#define MaxVertexNum 1000
#define MinData -999
typedef int Vertex;
typedef int EdgeType;
typedef Vertex ElementType;
typedef Vertex SetName;
typedef ElementType SetType[MaxVertexNum];

struct Edge
{
    int weight;
    Vertex x, y;
};

struct MinHeap
{
    Edge *elements;
    int size;
    int capacity;
};

void initSet(SetType set, int size)
{
    for (int i = 0; i < size; i++)
        set[i] = -1;
}

SetName findSet(SetType set, SetName x)
{
    while (set[x] >= 0)
    {
        x = set[x];
    }
    return x;
}

void unionSet(SetType set, SetName x, SetName y)
{
    int root1 = findSet(set, x);
    int root2 = findSet(set, y);
    if (root1 == root2)
        return;
    if (set[root1] < set[root2])
    {
        set[root1] += set[root2];
        set[root2] = root1;
    }
    else
    {
        set[root2] += set[root1];
        set[root1] = root2;
    }
}

bool checkCycle(SetType set, Vertex v1, Vertex v2)
{
    int root1 = findSet(set, v1);
    int root2 = findSet(set, v2);
    if (root1 == root2)
        return false;
    else
    {
        unionSet(set, v1, v2);
        return true;
    }
}

MinHeap *createMinHeap(int max_size)
{
    MinHeap *heap = new MinHeap;
    heap->capacity = max_size;
    heap->size = 0;
    heap->elements = new Edge[max_size + 1];
    heap->elements[0].weight = MinData;
    return heap;
}

void insertIntoHeap(MinHeap *heap, Edge ele)
{
    if (heap->size == heap->capacity)
        return;
    int i = ++heap->size;
    for (; heap->elements[i / 2].weight > ele.weight; i /= 2)
        heap->elements[i] = heap->elements[i / 2];
    heap->elements[i] = ele;
}

Edge deleteMin(MinHeap *heap)
{
    // if (heap->size == 0)
    //     return ;
    Edge min = heap->elements[1];
    Edge tmp = heap->elements[heap->size--];
    int parent, child;
    for (parent = 1; parent * 2 <= heap->size; parent = child)
    {
        child = parent * 2;
        if (child != heap->size && heap->elements[child + 1].weight < heap->elements[child].weight)
            child++;
        if (tmp.weight <= heap->elements[child].weight)
            break;
        else
            heap->elements[parent] = heap->elements[child];
    }
    heap->elements[parent] = tmp;
    return min;
}

int kruskal(MinHeap *heap, SetType set, int vexnum)
{
    vector<Edge> mst;
    int weight_sum = 0;
    while (mst.size() < vexnum - 1 && heap->size > 0)
    {
        Edge min = deleteMin(heap);
        if (checkCycle(set, min.x, min.y))
        {
            unionSet(set, min.x, min.y);
            mst.push_back(min);
            weight_sum += min.weight;
        }
    }
    if (mst.size() < vexnum - 1)
        return -1;
    else
        return weight_sum;
}

int main()
{
    int vexnum, arcnum;
    scanf("%d %d\n", &vexnum, &arcnum);
    MinHeap *heap = createMinHeap(arcnum);
    SetType set;
    initSet(set, vexnum);
    Edge edge;
    for (int i = 0; i < arcnum; i++)
    {
        scanf("%d %d %d\n", &edge.x, &edge.y, &edge.weight);
        edge.x--;
        edge.y--;
        insertIntoHeap(heap, edge);
    }
    printf("%d\n", kruskal(heap, set,vexnum));

    return 0;
}
