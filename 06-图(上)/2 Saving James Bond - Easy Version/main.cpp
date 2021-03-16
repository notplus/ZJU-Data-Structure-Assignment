#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

#define MaxVertexNum 102
typedef struct
{
    int x, y;
} VertexType;

typedef int EdgeType;

typedef struct
{
    VertexType *vex[MaxVertexNum];
    EdgeType edge[MaxVertexNum][MaxVertexNum]={};
    int vexnum, arcnum;
} MGraph;

MGraph *initGraph(int vexnum)
{
    MGraph *graph = new MGraph;
    graph->vexnum = vexnum;
    int x, y;
    for (int i = 0; i < vexnum; i++)
    {
        scanf("%d %d\n", &x, &y);
        VertexType *tmp = new VertexType;
        tmp->x = x, tmp->y = y;
        graph->vex[i] = tmp;
        
    }

    return graph;
}

void addEdge(MGraph *graph, EdgeType v1, EdgeType v2)
{
    graph->edge[v1][v2] = 1;
    graph->edge[v2][v1] = 1;
}

double computeDist(VertexType *v1, VertexType *v2)
{
    return sqrt((v1->x - v2->x) * (v1->x - v2->x) + (v1->y - v2->y) * (v1->y - v2->y));
}

bool isConnectToLand(MGraph *graph, VertexType *v1, int D)
{
    VertexType v2;
    v2.x = -50, v2.y = v1->y;
    if (computeDist(v1, &v2) <= D)
        return true;
    v2.x = 50;
    if (computeDist(v1, &v2) <= D)
        return true;
    v2.x = v1->x, v2.y = -50;
    if (computeDist(v1, &v2) <= D)
        return true;
    v2.y = 50;
    if (computeDist(v1, &v2) <= D)
        return true;
    return false;
}

void buildGraph(MGraph *graph, int D)
{
    VertexType *origin = new VertexType;
    origin->x = 0, origin->y = 0;
    VertexType *land = new VertexType;
    // land->x = 0, land->y = 0;
    graph->vex[graph->vexnum] = origin;
    graph->vex[graph->vexnum + 1] = land;
    for (int i = 0; i < graph->vexnum; i++)
    {
        if (computeDist(graph->vex[i], origin) <= 7.5 + D)
            addEdge(graph, i, graph->vexnum);
        if (isConnectToLand(graph, graph->vex[i], D))
            addEdge(graph, i, graph->vexnum + 1);
        for (int j = 0; j < graph->vexnum; j++)
            if (i != j && computeDist(graph->vex[i], graph->vex[j]) <= D)
                addEdge(graph, i, j);
    }
}

bool canEscape(MGraph *graph)
{
    bool visited[MaxVertexNum]={};
    stack<int> s;
    s.push(graph->vexnum);
    EdgeType p;
    while (!s.empty())
    {
        p = s.top();
        visited[p] = true;
        if (p == graph->vexnum + 1)
            return true;
        s.pop();
        for (int i = 0; i < graph->vexnum+2; i++)
            if (graph->edge[p][i] && !visited[i])
                s.push(i);
    }
    return false;
}

int main()
{
    int n, d;
    scanf("%d %d\n", &n, &d);
    MGraph *graph = initGraph(n);
    buildGraph(graph, d);
    if (canEscape(graph))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
