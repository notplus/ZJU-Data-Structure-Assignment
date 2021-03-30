#include <iostream>

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

void BubbleSort(ElementType array[], int n)
{
    bool flag = false;
    for (int p = n - 1; p > 0; p--)
    {
        for (int i = 0; i < p; i++)
        {
            if (array[i] > array[i + 1])
            {
                int tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                flag = true;
            }
        }
        if (!flag)
            break;
    }
}

void InsertionSort(ElementType array[], int n)
{
    for (int p = 1; p < n; p++)
    {
        ElementType tmp = array[p];
        int i = p;
        for (; i > 0 && array[i - 1] > tmp; i--)
            array[i] = array[i - 1];
        array[i] = tmp;
    }
}

void ShellSort(ElementType array[], int n)
{
    for (int d = n / 2; d > 0; d /= 2)
        for (int p = d; p < n; p++)
        {
            ElementType tmp = array[p];
            int i = p;
            for (; i >= d && array[i - d] > tmp; i -= d)
                array[i] = array[i - d];
            array[i] = tmp;
        }
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

void HeapSort(ElementType array[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        PercDown(array, i, n);
    for (int i = n - 1; i >= 0; i--)
    {
        ElementType tmp = array[i];
        array[i] = array[0];
        array[0] = tmp;
        PercDown(array, 0, i);
    }
}

void Merge(ElementType array[], ElementType tmp_a[], int left, int right, int right_end)
{
    int left_end = right - 1;
    int tmp = left;
    int num_elements = right_end - left + 1;
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
    for (int i = 0; i < num_elements; i++, right_end--)
        array[right_end] = tmp_a[right_end];
}

void MSort(ElementType array[], ElementType tmp_a[], int left, int right_end)
{
    int center;
    if (left < right_end)
    {
        center = (left + right_end) / 2;
        MSort(array, tmp_a, left, center);
        MSort(array, tmp_a, center + 1, right_end);
        Merge(array, tmp_a, left, center + 1, right_end);
    }
}

void MergeSort(ElementType array[], int n)
{
    ElementType *tmp_a = new ElementType[n];
    if (tmp_a != NULL)
    {
        MSort(array, tmp_a, 0, n - 1);
        delete[] tmp_a;
    }
    else
        printf("OOM");
}

void Merge1(ElementType array[], ElementType tmp_a[], int left, int right, int right_end)
{
    int left_end = right - 1;
    int tmp = left;
    int num_elements = right_end - left_end + 1;
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

void MergeSortLoop(ElementType array[], int n)
{
    ElementType *tmp_a = new ElementType[n];
    if (tmp_a != NULL)
    {
        int length = 1;
        while (length < n)
        {
            MergePass(array, tmp_a, n, length);
            length *= 2;
            MergePass(tmp_a, array, n, length);
            length *= 2;
        }
        delete[] tmp_a;
    }
    else
        printf("OOM");
}

int main()
{
    int n;
    scanf("%d", &n);
    ElementType *array = inputArray(n);
    // BubbleSort(array, n);
    // InsertionSort(array, n);
    // ShellSort(array, n);
    // HeapSort(array, n);
    // MergeSort(array, n);
    MergeSortLoop(array, n);

    printArray(array, n);
    return 0;
}
