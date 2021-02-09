Position BinarySearch(List L, ElementType X)
{
    int start = 1;
    int end = L->Last;
    int pos = NotFound;

    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (L->Data[mid] == X)
        {
            pos = mid;
            break;
        }
        else if (X < L->Data[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }

    return pos;
}