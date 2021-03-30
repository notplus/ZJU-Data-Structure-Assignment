#include <iostream>
#include <cstring>

using namespace std;

#define ElementType int

ElementType *inputArray(int n)
{
    ElementType *array = new ElementType[n];
    for (int i = 0; i < n; i++)
        scanf("%d ", &array[i]);
    return array;
}

void printArray(ElementType array[], int n)
{
    printf("%d", array[0]);
    for (int i = 1; i < n; i++)
        printf(" %d", array[i]);
}

void InsertionSort(ElementType array[], int iter)
{
    for (int p = 1; p <= iter; p++)
    {
        ElementType tmp = array[p];
        int i = p;
        for (; i > 0 && array[i - 1] > tmp; i--)
            array[i] = array[i - 1];
        array[i] = tmp;
    }
}

int FindMinSortIndex(ElementType array[], int n)
{
    int i = 0;
    for (; i < n; i++)
        if (array[i] > array[i + 1])
            break;
    return i;
}

bool IsSame(ElementType array[], ElementType array2[], int n)
{
    for (int i = 0; i < n; i++)
        if (array[i] != array2[i])
            return false;
    return true;
}

void PercDown(ElementType array[], int p, int n)
{
    ElementType x = array[p];
    int child, parent;
    for (parent = p; (parent * 2 + 1) < n; parent = child)
    {
        child = parent * 2 + 1;
        if (child != n - 1 && array[child] < array[child + 1])
            child++;
        if (x >= array[child])
            break;
        else
            array[parent] = array[child];
    }
    array[parent] = x;
}

int main()
{
    int n;
    scanf("%d", &n);
    ElementType *array = inputArray(n);
    ElementType *seq = inputArray(n);
    int min_sort_index = FindMinSortIndex(seq, n);
    ElementType *array_copy = new ElementType[n];
    memcpy(array_copy, array, n * sizeof(ElementType));

    InsertionSort(array_copy, min_sort_index);
    int i = min_sort_index + 1;
    for (; i < n; i++)
        if (array_copy[i] != seq[i])
            break;
    if (i == n)
    {
        printf("Insertion Sort\n");
        ElementType tmp = seq[min_sort_index + 1];
        int j = min_sort_index + 1;
        for (; j > 0 && seq[j - 1] > tmp; j--)
            seq[j] = seq[j - 1];
        seq[j] = tmp;
        printArray(seq, n);
    }
    else
    {
        printf("Heap Sort\n");
        bool flag = false;
        for (int i = n / 2 - 1; i >= 0; i--)
            PercDown(array, i, n);
        for (int i = n - 1; i >= 0; i--)
        {
            if (IsSame(seq, array, n))
                flag = true;
            ElementType tmp = array[i];
            array[i] = array[0];
            array[0] = tmp;
            PercDown(array, 0, i);
            if (flag)
            {
                printArray(array, n);
                break;
            }
        }
    }

    return 0;
}
