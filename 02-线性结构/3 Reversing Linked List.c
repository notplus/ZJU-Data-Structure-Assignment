List Reverse( List L )
{
    int n=0;
    List p=L->Next;
    while(p)
    {
        n++;
        p=p->Next;
    }
    ElementType* array=(ElementType*)malloc(sizeof(ElementType)*n);
    p=L->Next;
    for(int i=0;i<n;i++)
    {
        array[i]=p->Element;
        p=p->Next;
    }
    p=L->Next;
    for(int i=0;i<n;i++)
    {
        p->Element=array[n-i-1];
        p=p->Next;
    }
    return L;
}