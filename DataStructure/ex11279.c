#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int position;
    int size;
    int* heap;
} Heap;

Heap* getHeap(int size) {
    Heap* temp = (Heap*) malloc(sizeof(Heap)*(size+1));
    temp->size = size+1;
    temp->heap = (int*) malloc(sizeof(int)*(size+1));
    temp->position = 0;
    return temp;
}

void deleteHeap(Heap* heap) {
    free(heap->heap);
    free(heap);
}

void push(Heap* heap, int element) {
    int position = ++heap->position;

    while (position != 1 && element > heap->heap[position/2]) {
        heap->heap[position] = heap->heap[position/2];
        position = position/2;
    }
    heap->heap[position] = element;
}

int pop(Heap* heap) {
    if (heap->position < 1) return 0;
    int parent = 1;
    int child = 2;
    int temp = heap->heap[heap->position];
    heap->position--;
    int max = heap->heap[1];
    while (child <= heap->position) {
        if (child < heap->position && heap->heap[child] < heap->heap[child+1])
            child++;
        if (temp >= heap->heap[child]) break;
        heap->heap[parent] = heap->heap[child];
        parent = child;
        child *= 2;
    }
    heap->heap[parent] = temp;
    return max;
}

int main() {
    int n, input, max;
    scanf("%d", &n);
    Heap* heap = getHeap(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &input);
        if (input == 0) {
            max = pop(heap);
            printf("%d\n", max >= 0 ? max : 0);
        } else {
            push(heap, input);
        }
    }

    deleteHeap(heap);
    return 0;
}