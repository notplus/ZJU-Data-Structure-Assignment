/*
 * @Description: 
 * @Author: notplus
 * @Date: 2021-03-01 19:12:39
 * @LastEditors: notplus
 * @LastEditTime: 2021-03-09 16:40:42
 */

#include <iostream>

using namespace std;

struct Node
{
    int data;
    int next;
};

Node nodes[100001];

int Reverse(int head, int k)
{
    int now = nodes[head].next, old = nodes[now].next;
    int cnt = 1;
    while (cnt < k)
    {
        int tmp = nodes[old].next;
        nodes[old].next = now;
        now = old;
        old = tmp;
        cnt++;
    }
    nodes[nodes[head].next].next = old;
    return now;
}

int main()
{
    int head, n, k;
    scanf("%d %d %d", &head, &n, &k);
    for (int i = 0; i < n; i++)
    {
        int addr;
        scanf("%d", &addr);
        scanf("%d %d", &nodes[addr].data, &nodes[addr].next);
    }
    nodes[100000].next = head;
    head = 100000;
    n = 0;
    while (nodes[head].next != -1)
    {
        head = nodes[head].next;
        n++;
    }
    head = 100000;
    for (int i = 0; i < n / k; i++)
    {
        int tmp = nodes[head].next;
        nodes[head].next = Reverse(head, k);
        head = tmp;
    }
    head = nodes[100000].next;
    while (nodes[head].next != -1)
    {
        printf("%05d %d %05d\n", head, nodes[head].data, nodes[head].next);
        head = nodes[head].next;
    }
    printf("%05d %d -1", head, nodes[head].data);

    return 0;
}
