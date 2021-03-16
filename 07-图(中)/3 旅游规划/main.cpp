#include <iostream>
#include <stack>
#include <cmath>
#include <vector>
using namespace std;

#define MaxVertexNum 500
#define MaxDist 9999
typedef int VertexType;
typedef int WeightType;

typedef struct
{
    WeightType weight[MaxVertexNum][MaxVertexNum] = {};
    WeightType dist[MaxVertexNum];
    VertexType path[MaxVertexNum];
    int cost[MaxVertexNum];
    int vexnum, arcnum;
} MGraph;

int cost_list[MaxVertexNum][MaxVertexNum] = {};

void addEdge(MGraph *graph, VertexType v1, VertexType v2, WeightType weight)
{
    graph->weight[v1][v2] = weight;
    graph->weight[v2][v1] = weight;
}

MGraph *initGraph(int vexnum, int arcnum)
{
    MGraph *graph = new MGraph;
    graph->vexnum = vexnum;
    VertexType vx, vy;
    WeightType dist;
    int cost;
    for (int i = 0; i < arcnum; i++)
    {
        scanf("%d %d %d %d\n", &vx, &vy, &dist, &cost);
        addEdge(graph, vx, vy, dist);
        cost_list[vx][vy] = cost;
        cost_list[vy][vx] = cost;
    }

    return graph;
}

void buildGraph(MGraph *graph, VertexType source)
{
    for (int i = 0; i < graph->vexnum; i++)
    {
        graph->path[i] = -1;
        if (graph->weight[source][i] == 0)
            graph->dist[i] = MaxDist;
        else
            graph->dist[i] = graph->weight[source][i];
        if (cost_list[source][i] == 0)
            graph->cost[i] = MaxDist;
        else
            graph->cost[i] = cost_list[source][i];
        for (int j = 0; j < graph->vexnum; j++)
        {
            if (graph->weight[i][j] == 0)
                graph->weight[i][j] = MaxDist;
        }
    }
    graph->dist[source] = 0;
    graph->cost[source] = 0;
}

bool collected[MaxVertexNum] = {};

VertexType getUncollectedMinDistanceVertex(MGraph *graph)
{
    double min = MaxDist;
    int min_v = -1;
    for (int i = 0; i < graph->vexnum; i++)
        if (graph->dist[i] < min && collected[i] == false)
            min_v = i, min = graph->dist[i];
    return min_v;
}

void Dijkstra(MGraph *graph, VertexType source)
{
    collected[source] = true;
    while (true)
    {
        VertexType v = getUncollectedMinDistanceVertex(graph);
        if (v == -1)
            break;
        collected[v] = true;
        for (int w = 0; w < graph->vexnum; w++)
        {
            if (collected[w] == false)
            {
                if (graph->dist[v] + graph->weight[v][w] < graph->dist[w])
                {
                    graph->dist[w] = graph->dist[v] + graph->weight[v][w];
                    graph->path[w] = v;
                    graph->cost[w] = graph->cost[v] + cost_list[v][w];
                }
                else if (graph->dist[v] + graph->weight[v][w] == graph->dist[w] && graph->cost[v] + cost_list[v][w] < graph->cost[w])
                {
                    graph->path[w] = v;
                    graph->cost[w] = graph->cost[v] + cost_list[v][w];
                }
            }
        }
    }
}

int main()
{
    int n, m, s, d;
    scanf("%d %d %d %d\n", &n, &m, &s, &d);
    MGraph *graph = initGraph(n, m);
    buildGraph(graph, s);
    Dijkstra(graph, s);
    printf("%d %d\n", graph->dist[d], graph->cost[d]);

    return 0;
}