#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* heap;
    int position;
} Heap;

Heap* setHeap(int size) {
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->heap = (int*) malloc(sizeof(int)*(size+10));
    heap->position = 0;
    return heap;
}

void freeHeap(Heap* heap) {
    free(heap->heap);
    free(heap);
}

void insert(Heap* heap, int data) {
    int position = ++heap->position;

    while (position != 1 && data < heap->heap[position/2]) {
        heap->heap[position] = heap->heap[position/2];
        position = position/2;
    }
    heap->heap[position] = data;
}

int pop(Heap* heap) {
    if (heap->position == 0) return -1;
    int temp = heap->heap[heap->position--];
    int first = heap->heap[1];
    int parent = 1;
    int child = 2;

    while (child <= heap->position) {
        if (child<heap->position && heap->heap[child] > heap->heap[child+1])
            child++;
        
        if (temp <= heap->heap[child]) break;

        heap->heap[parent] = heap->heap[child];
        parent = child;
        child *= 2;
    }

    heap->heap[parent] = temp;
    return first;
}

int main() {
    int n, x, min;
    scanf("%d", &n);
    
    Heap* heap = setHeap(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        if (x == 0) {
            min = pop(heap);
            printf("%d\n", min >= 0 ? min : 0);
        } else {
            insert(heap, x);
        }
    }

    freeHeap(heap);
    return 0;
}