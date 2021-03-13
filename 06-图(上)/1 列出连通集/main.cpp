#include <iostream>
#include <queue>

using namespace std;

#define MaxVertexNum 10
typedef int VertexType;
typedef int EdgeType;
typedef struct
{
    // VertexType vex[MaxVertexNum];
    EdgeType edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;

bool visited[MaxVertexNum];

MGraph *initGraph(int vexnum, int arcnum)
{
    MGraph *graph = new MGraph;
    graph->vexnum = vexnum;
    graph->arcnum = arcnum;
    // for (int i = 0; i < vexnum; i++)
    //     graph->vex[i] = 1;

    return graph;
}

void addEdge(MGraph *graph, VertexType v1, VertexType v2)
{
    // if (graph.vex[v1] && graph.vex[v2])
    graph->edge[v1][v2] = 1;
    graph->edge[v2][v1] = 1;
}

void DFS(MGraph *graph, VertexType v)
{
    printf("%d ", v);
    visited[v] = true;

    for (int i = 0; i < graph->vexnum; i++)
        if (graph->edge[v][i] && !visited[i])
            DFS(graph, i);
}

void BFS(MGraph *graph, VertexType v)
{
    printf("%d ", v);
    visited[v] = true;
    queue<VertexType> q;
    q.push(v);
    while (!q.empty())
    {
        v = q.front();
        q.pop();
        for (int i = 0; i < graph->vexnum; i++)
        {
            if (graph->edge[v][i] && !visited[i])
            {
                printf("%d ", i);
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void listComponents(MGraph *graph)
{
    for (int i = 0; i < graph->vexnum; i++)
        if (!visited[i])
        {
            printf("{ ");
            DFS(graph, i);
            printf("}\n");
        }

    for (int i = 0; i < graph->vexnum; i++)
        visited[i] = false;

    for (int i = 0; i < graph->vexnum; i++)
        if (!visited[i])
        {
            printf("{ ");
            BFS(graph, i);
            printf("}\n");
        }
}

int main()
{
    int vexnum, arcnum;
    scanf("%d %d\n", &vexnum, &arcnum);
    MGraph *graph = initGraph(vexnum, arcnum);
    for (int i = 0; i < arcnum; i++)
    {
        int v1, v2;
        scanf("%d %d\n", &v1, &v2);
        addEdge(graph, v1, v2);
    }
    listComponents(graph);

    return 0;
}
