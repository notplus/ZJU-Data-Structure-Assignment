#include <iostream>
#include <stack>
#include <cmath>
#include <vector>
using namespace std;

#define MaxVertexNum 102
#define MaxDist 999
typedef struct
{
    int x, y;
} DataType;

typedef int VertexType;
typedef double WeightType;

typedef struct
{
    DataType *vex[MaxVertexNum];
    WeightType weight[MaxVertexNum][MaxVertexNum] = {};
    WeightType dist[MaxVertexNum];
    VertexType path[MaxVertexNum];
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
        DataType *tmp = new DataType;
        tmp->x = x, tmp->y = y;
        graph->vex[i] = tmp;
    }

    return graph;
}

void addEdge(MGraph *graph, VertexType v1, VertexType v2, WeightType weight)
{
    graph->weight[v1][v2] = weight;
    graph->weight[v2][v1] = weight;
}

double computeDist(DataType *v1, DataType *v2)
{
    return sqrt((v1->x - v2->x) * (v1->x - v2->x) + (v1->y - v2->y) * (v1->y - v2->y));
}

void handleLandEdge(MGraph *graph, VertexType v, int D)
{
    DataType *v1 = graph->vex[v];
    double dist1 = 50 - v1->y;
    double dist2 = 50 + v1->y;
    double dist3 = 50 - v1->x;
    double dist4 = 50 + v1->x;

    double min_dist = min(dist1, dist2);
    min_dist = min(min_dist, dist3);
    min_dist = min(min_dist, dist4);

    if (min_dist <= D && min_dist > 0 && v != graph->vexnum)
        addEdge(graph, v, graph->vexnum + 1, 1);
    else if (v == graph->vexnum && min_dist <= D)
        addEdge(graph, v, graph->vexnum + 1, 1);
    else
        addEdge(graph, v, graph->vexnum + 1, MaxDist);
}

void buildGraph(MGraph *graph, int D)
{
    DataType *origin = new DataType;
    origin->x = 0, origin->y = 0;
    DataType *land = new DataType;
    graph->vex[graph->vexnum] = origin;
    graph->vex[graph->vexnum + 1] = land;
    for (int i = 0; i < graph->vexnum; i++)
    {
        double dist_to_origin = computeDist(graph->vex[i], origin);
        if (dist_to_origin <= 7.5 + D && dist_to_origin > 7.5)
        {
            addEdge(graph, i, graph->vexnum, 1);
            graph->dist[i] = 1;
        }
        else
            graph->dist[i] = MaxDist;

        handleLandEdge(graph, i, D);

        for (int j = 0; j < graph->vexnum; j++)
        {
            double dist = computeDist(graph->vex[i], graph->vex[j]);
            if (i != j && dist <= D)
                addEdge(graph, i, j, 1);
            else
                addEdge(graph, i, j, MaxDist);
        }
    }
    graph->dist[graph->vexnum] = 0;
    graph->dist[graph->vexnum + 1] = MaxDist;
    handleLandEdge(graph, graph->vexnum, D);
    for (int i = 0; i < graph->vexnum + 2; i++)
    {
        if (i != graph->vexnum && graph->weight[graph->vexnum][i] == 0)
            addEdge(graph, graph->vexnum, i, MaxDist);
    }
}

bool collected[MaxVertexNum] = {};

VertexType getUncollectedMinDistanceVertex(MGraph *graph)
{
    double min = MaxDist;
    int min_v = -1;
    for (int i = 0; i < graph->vexnum + 2; i++)
        if (graph->dist[i] < min && collected[i] == false)
            min_v = i, min = graph->dist[i];
    return min_v;
}

void Dijkstra(MGraph *graph, VertexType source)
{
    for (int i = 0; i < graph->vexnum + 2; i++)
        graph->path[i] = -1;
    if (graph->weight[source][graph->vexnum + 1] != MaxDist)
    {
        graph->dist[graph->vexnum + 1] = graph->dist[source] + graph->weight[source][graph->vexnum + 1];
        graph->path[graph->vexnum + 1] = -1;
        return;
    }
    collected[source] = true;
    while (true)
    {
        VertexType v = getUncollectedMinDistanceVertex(graph);
        if (v == -1)
            break;
        collected[v] = true;
        for (int w = 0; w < graph->vexnum + 2; w++)
        {
            if (collected[w] == false)
            {
                if (graph->dist[v] + graph->weight[v][w] == graph->dist[w])
                {
                    VertexType p = graph->path[w];
                    while (graph->path[p] != -1)
                        p = graph->path[p];
                    VertexType q = v;
                    while (graph->path[q] != -1)
                        q = graph->path[q];
                    if (computeDist(graph->vex[graph->vexnum], graph->vex[p]) < computeDist(graph->vex[graph->vexnum], graph->vex[q]))
                        continue;
                }
                if (graph->dist[v] + graph->weight[v][w] <= graph->dist[w])
                {
                    graph->dist[w] = graph->dist[v] + graph->weight[v][w];
                    graph->path[w] = v;
                }
            }
        }
    }
}

void printEscapePath(MGraph *graph)
{
    VertexType w;
    stack<int> s;
    s.push(graph->path[graph->vexnum + 1]);
    while (s.top() != -1)
    {
        s.push(graph->path[s.top()]);
    }
    if (graph->path[graph->vexnum + 1] == -1)
        printf("1\n");
    else
    {
        printf("%d\n", s.size());
        s.pop();
        while (!s.empty())
        {
            w = s.top();
            printf("%d %d\n", graph->vex[w]->x, graph->vex[w]->y);
            s.pop();
        }
    }
}

int main()
{
    int n, d;
    scanf("%d %d\n", &n, &d);
    MGraph *graph = initGraph(n);
    buildGraph(graph, d);
    Dijkstra(graph, n);
    if (graph->dist[n + 1] != MaxDist)
        printEscapePath(graph);
    else
        printf("0\n");
    return 0;
}