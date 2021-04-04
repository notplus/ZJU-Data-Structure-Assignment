#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    int id;
    vector<int> score;
    int ac_count = 0;
    int total = 0;
    bool is_shown = false;
};

vector<int> full_mark;
vector<Node *> users;

bool cmpl(Node *a, Node *b)
{
    if (a->total != b->total)
        return a->total > b->total;
    else if (a->ac_count != b->ac_count)
        return a->ac_count > b->ac_count;
    else
        return a->id < b->id;
}

int main()
{
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    full_mark.resize(k);
    for (int i = 0; i < k; i++)
        scanf("%d", &full_mark[i]);
    users.resize(n);
    for (int i = 0; i < n; i++)
    {
        users[i] = new Node;
        users[i]->id = i + 1;
        users[i]->score.resize(k);
        for (int j = 0; j < k; j++)
            users[i]->score[j] = -2;
    }
    for (int i = 0; i < m; i++)
    {
        int id, p, s;
        scanf("%d %d %d", &id, &p, &s);
        if (s > users[id - 1]->score[p - 1])
        {
            if (s == -1)
                users[id - 1]->score[p - 1] = 0;
            else
            {
                users[id - 1]->is_shown = true;
                users[id - 1]->score[p - 1] = s;
                if (s == full_mark[p - 1])
                    users[id - 1]->ac_count++;
            }
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            if (users[i]->score[j] != -2)
                users[i]->total += users[i]->score[j];

    sort(users.begin(), users.end(), cmpl);
    int rank = -1, last_total = 0;
    for (int i = 0; i < n; i++)
    {
        if (users[i]->is_shown)
        {
            if (users[i]->total != last_total)
            {
                rank = i + 1;
                last_total = users[i]->total;
            }

            printf("%d %05d %d", rank, users[i]->id, users[i]->total);
            for (int j = 0; j < k; j++)
            {
                if (users[i]->score[j] == -2)
                    printf(" %c", '-');
                else
                    printf(" %d", users[i]->score[j]);
            }
            printf("\n");
        }
    }

    return 0;
}
