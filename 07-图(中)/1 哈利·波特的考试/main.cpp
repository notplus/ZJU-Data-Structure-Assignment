#include <iostream>
#include <stack>

using namespace std;

#define MaxVertexNum 100
#define INFINITY 999
typedef int VertexType;
typedef int WeightType;

typedef struct
{
    // VertexType vex[MaxVertexNum];
    WeightType weight[MaxVertexNum][MaxVertexNum] = {};
    VertexType distance[MaxVertexNum][MaxVertexNum];
    VertexType path[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;

void addEdge(MGraph *graph, VertexType v1, VertexType v2, WeightType weight)
{
    graph->weight[v1][v2] = weight;
    graph->weight[v2][v1] = weight;
}

MGraph *initGraph(int vexnum, int arcnum)
{
    MGraph *graph = new MGraph;
    graph->vexnum = vexnum;
    VertexType x, y;
    WeightType weight;
    for (int i = 0; i < arcnum; i++)
    {
        scanf("%d %d %d\n", &x, &y, &weight);
        addEdge(graph, x - 1, y - 1, weight);
    }

    return graph;
}

void Floyd(MGraph *graph)
{
    for (int i = 0; i < graph->vexnum; i++)
        for (int j = 0; j < graph->vexnum; j++)
        {
            if (graph->weight[i][j] == 0)
                graph->distance[i][j] = INFINITY;
            else
                graph->distance[i][j] = graph->weight[i][j];
            graph->path[i][j] = -1;
        }
    for (int k = 0; k < graph->vexnum; k++)
        for (int i = 0; i < graph->vexnum; i++)
            for (int j = 0; j < graph->vexnum; j++)
                if (graph->distance[i][k] + graph->distance[k][j] < graph->distance[i][j])
                {
                    graph->distance[i][j] = graph->distance[i][k] + graph->distance[k][j];
                    graph->path[i][j] = k;
                }
}

int getDistance(MGraph *graph, VertexType v1, VertexType v2)
{
    if (graph->path[v1][v2] == -1)
        return graph->distance[v1][v2];
    return getDistance(graph, v1, graph->path[v1][v2]) + getDistance(graph, graph->path[v1][v2], v2);
}

int getHardest(MGraph *graph, VertexType v)
{
    int distance, max = 0;
    for (int i = 0; i < graph->vexnum; i++)
    {
        if (i != v)
        {
            distance = getDistance(graph, v, i);
            if (distance > max)
                max = distance;
        }
    }
    return max;
}

int main()
{
    int n, arcnum;
    scanf("%d %d\n", &n, &arcnum);
    MGraph *graph = initGraph(n, arcnum);
    Floyd(graph);
    bool flag = false;
    for (int i = 1; i < graph->vexnum; i++)
        if (graph->distance[0][i] == INFINITY)
            flag = true;
    if (flag)
        printf("0");
    else
    {

        int min = INFINITY, min_v;
        for (int i = 0; i < graph->vexnum; i++)
        {
            int distance = getHardest(graph, i);
            if (distance < min)
            {
                min = distance;
                min_v = i;
            }
        }

        printf("%d %d", min_v + 1, min);
    }

    return 0;
}
