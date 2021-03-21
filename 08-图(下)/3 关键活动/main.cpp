#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define MaxVertexNum 101
#define MaxDist 9999999
#define VertexType int
#define WeightType int
struct ArcNode
{
    int adjvex;
    ArcNode *next;
    WeightType weight;
};
typedef struct VNode
{
    // VertexType data;
    ArcNode *first = NULL;
    int indegree = 0;
} VNode, AdjList[MaxVertexNum];

struct ALGraph
{
    AdjList vertices;
    int vexnum, arcnum;
};
int change[MaxVertexNum];

void initGraph(ALGraph *graph, int vexnum, int arcnum)
{
    graph->vexnum = vexnum;
    graph->arcnum = arcnum;

    for (int i = 0; i < arcnum; i++)
    {
        int s, e, l;
        scanf("%d %d %d", &s, &e, &l);
        ArcNode *p = new ArcNode;
        p->adjvex = e;
        p->weight = l;
        p->next = graph->vertices[s].first;
        graph->vertices[s].first = p;
        graph->vertices[e].indegree++;
    }
}

void TopologicalSort(ALGraph *graph)
{
    queue<int> que;
    bool flag[MaxVertexNum] = {};
    for (int i = 1; i <= graph->vexnum; i++)
    {
        if (graph->vertices[i].indegree == 0)
        {
            que.push(i);
            flag[i] = true;
        }
    }
    int ve[MaxVertexNum] = {};
    int vl[MaxVertexNum];
    int count = 0;
    while (!que.empty())
    {
        int i = que.front();
        que.pop();
        change[++count] = i;

        for (ArcNode *p = graph->vertices[i].first; p; p = p->next)
        {
            int j = p->adjvex;
            graph->vertices[j].indegree--;
            if (p->weight + ve[i] > ve[j])
                ve[j] = p->weight + ve[i];
        }

        for (int i = 1; i <= graph->vexnum; i++)
            if (graph->vertices[i].indegree == 0 && flag[i] == false)
            {
                que.push(i);
                flag[i] = true;
            }
    }
    if (count < graph->vexnum)
    {
        printf("0");
        return;
    }

    for (int i = 1; i <= graph->vexnum; i++)
        vl[i] = ve[change[graph->vexnum]];

    printf("%d\n", ve[change[graph->vexnum]]);
    for (int i = graph->vexnum; i > 0; i--)
    {
        ArcNode *p = graph->vertices[change[i]].first;
        while (p != NULL)
        {
            int j = p->adjvex;
            if (vl[j] - p->weight < vl[change[i]])
                vl[change[i]] = vl[j] - p->weight;
            p = p->next;
        }
    }

    for (int i = 1; i <= graph->vexnum; i++)
    {
        ArcNode *p = graph->vertices[i].first;
        while (p != NULL)
        {
            int j = p->adjvex;
            int e = ve[i];
            int l = vl[j] - p->weight;
            if (e == l)
                printf("%d->%d\n", i, j);
            p = p->next;
        }
    }
}

int main()
{
    int vexnum, arcnum;
    scanf("%d %d\n", &vexnum, &arcnum);
    ALGraph *graph = new ALGraph;
    initGraph(graph, vexnum, arcnum);
    TopologicalSort(graph);
    return 0;
}
