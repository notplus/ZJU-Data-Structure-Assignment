#include <iostream>
#include <queue>

using namespace std;

#define MaxVertexNum 1000
typedef int VertexType;
typedef int EdgeType;
typedef struct
{
    EdgeType edge[MaxVertexNum][MaxVertexNum] = {};
    int vexnum, arcnum;
} MGraph;

MGraph *initGraph(int vexnum, int arcnum)
{
    MGraph *graph = new MGraph;
    graph->vexnum = vexnum;
    graph->arcnum = arcnum;

    return graph;
}

void addEdge(MGraph *graph, VertexType v1, VertexType v2)
{
    graph->edge[v1][v2] = 1;
    graph->edge[v2][v1] = 1;
}

int getAcquaintance(MGraph *graph, VertexType v)
{
    bool visited[MaxVertexNum] = {};
    int acquaintance_num = 0;
    visited[v] = true;
    acquaintance_num++;
    int depth = 0, count = 0, last = 1;
    queue<VertexType> q;
    q.push(v);

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        count++;

        for (int i = 0; i < graph->vexnum; i++)
        {
            if (graph->edge[v][i] && !visited[i])
            {
                visited[i] = true;
                acquaintance_num++;
                q.push(i);
            }
        }
        if (count == last)
        {
            depth++;
            if (depth > 5)
                return acquaintance_num;
            count = 0;
            last = q.size();
        }
    }
    return acquaintance_num;
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
        addEdge(graph, v1 - 1, v2 - 1);
    }
    for (int i = 0; i < graph->vexnum; i++)
    {
        printf("%d: %.2f%%\n", i + 1, getAcquaintance(graph, i) * 1.0 / vexnum * 100);
    }

    return 0;
}
