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

void Merge1(ElementType array[], ElementType tmp_a[], int left, int right, int right_end)
{
    int left_end = right - 1;
    int tmp = left;
    while (left <= left_end && right <= right_end)
    {
        if (array[left] < array[right])
            tmp_a[tmp++] = array[left++];
        else
            tmp_a[tmp++] = array[right++];
    }
    while (left <= left_end)
        tmp_a[tmp++] = array[left++];
    while (right <= right_end)
        tmp_a[tmp++] = array[right++];
}

void MergePass(ElementType array[], ElementType tmp_a[], int n, int length)
{
    int i = 0;
    for (; i <= n - 2 * length; i += 2 * length)
        Merge1(array, tmp_a, i, i + length, i + 2 * length - 1);
    if (i + length < n)
        Merge1(array, tmp_a, i, i + length, n - 1);
    else
        for (int j = i; j < n; j++)
            tmp_a[j] = array[j];
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
        printf("Merge Sort\n");

        int length = 1;
        while (length < n)
        {
            if (IsSame(seq, array_copy, n))
            {
                MergePass(array, array_copy, n, length);
                printArray(array_copy, n);
                break;
            }
            MergePass(array, array_copy, n, length);
            length *= 2;
            if (IsSame(seq, array_copy, n))
            {
                MergePass(array_copy, array, n, length);
                printArray(array, n);
                break;
            }
            MergePass(array_copy, array, n, length);
            length *= 2;
        }
    }

    return 0;
}
