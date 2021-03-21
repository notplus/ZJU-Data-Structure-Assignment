#include <iostream>
#include <stack>

using namespace std;

#define MaxVertexNum 100
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

void initGraph(ALGraph *graph, int vexnum, int arcnum)
{
    graph->vexnum = vexnum;
    graph->arcnum = arcnum;
    int s, e, l;
    ArcNode *p;
    for (int i = 0; i < arcnum; i++)
    {
        scanf("%d %d %d", &s, &e, &l);
        p = graph->vertices[s].first;
        if (p == NULL)
            p = graph->vertices[s].first = new ArcNode;
        else
        {
            while (p->next != NULL)
                p = p->next;
            p = p->next = new ArcNode;
        }

        p->adjvex = e;
        p->weight = l;
        p->next = NULL;
        graph->vertices[e].indegree++;
    }
}

int TopologicalSort(ALGraph *graph)
{
    stack<int> s;
    for (int i = 0; i < graph->vexnum; i++)
        if (graph->vertices[i].indegree == 0)
            s.push(i);
    int e[MaxVertexNum] = {};
    int count = 0;
    int cost = 0;
    while (!s.empty())
    {
        int i = s.top();
        s.pop();
        count++;
        for (ArcNode *p = graph->vertices[i].first; p; p = p->next)
        {
            int j = p->adjvex;
            if (--graph->vertices[j].indegree == 0)
                s.push(j);
            if (p->weight + e[i] > e[j])
                e[j] = p->weight + e[i];
        }
        if (graph->vertices[i].first == NULL && e[i] > cost) // destination
            cost = e[i];
    }
    if (count < graph->vexnum)
        return -1;
    else
        return cost;
}

int main()
{
    int vexnum, arcnum;
    scanf("%d %d\n", &vexnum, &arcnum);
    ALGraph *graph = new ALGraph;
    initGraph(graph, vexnum, arcnum);
    int res = TopologicalSort(graph);
    if (res == -1)
        printf("Impossible");
    else
        printf("%d\n", res);
    return 0;
}
