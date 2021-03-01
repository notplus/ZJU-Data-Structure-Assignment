void attach(List *p, List list, List *pl);

List Merge(List L1, List L2)
{
    List p1 = L1->Next;
    List p2 = L2->Next;
    List res = (List *)malloc(sizeof(List));
    List p = res;
    while (p1 && p2)
    {
        if (p1->Data <= p2->Data)
            attach(&p, L1, &p1);
        else
            attach(&p, L2, &p2);
    }
    while (p1)
        attach(&p, L1, &p1);
    while (p2)
        attach(&p, L2, &p2);
    p->Next = NULL;
    return res;
}

void attach(List *p, List list, List *pl)
{
    (*p)->Next = *pl;
    *p = *pl;
    list->Next = (*pl)->Next;
    *pl = (*pl)->Next;
}