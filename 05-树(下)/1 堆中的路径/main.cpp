#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MinData -10001;

struct MinHeap
{
    int *elements;
    int size;
    int capacity;
};

MinHeap *createMinHeap(int max_size)
{
    MinHeap *heap = new MinHeap;
    heap->capacity = max_size;
    heap->size = 0;
    heap->elements = new int[max_size + 1];
    heap->elements[0] = MinData;
    return heap;
}

void insert(MinHeap *heap, int element)
{
    if (heap->size == heap->capacity)
        return;
    int i = ++heap->size;
    for (; heap->elements[i / 2] > element; i /= 2)
        heap->elements[i] = heap->elements[i / 2];
    heap->elements[i] = element;
}

void printPath(MinHeap *heap, int index)
{
    for (int i = index; i >= 2; i /= 2)
        printf("%d ", heap->elements[i]);
    printf("%d\n", heap->elements[1]);
}

int main()
{
    int max_size, count;
    scanf("%d %d", &max_size, &count);
    MinHeap *heap = createMinHeap(max_size);
    for (size_t i = 0; i < max_size; i++)
    {
        int num;
        scanf("%d", &num);
        insert(heap, num);
    }
    for (size_t i = 0; i < count; i++)
    {
        int cnt;
        scanf("%d", &cnt);
        printPath(heap, cnt);
    }

    return 0;
}
