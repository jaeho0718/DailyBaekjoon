#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int position;
} Heap;

Heap* getHeap(int size) {
    Heap* temp = (Heap*) malloc(sizeof(Heap));
    temp->arr = (int*) malloc(sizeof(int)*(size+1));
    temp->position = 0;
    return temp;
}

void insertMin(Heap* heap, int element) {
    int position = ++heap->position;

    while (position != 1 && element < heap->arr[position/2]) {
        heap->arr[position] = heap->arr[position/2];
        position /= 2;
    }
    
    heap->arr[position] = element;
}

int popMin(Heap* heap) {
    int minElement = heap->arr[1];
    int lastElement = heap->arr[heap->position--];
    int position = 1;
    int child;
    
    while (position * 2 <= heap->position) {
        child = position * 2;
        if (child < heap->position && heap->arr[child] > heap->arr[child + 1]) {
            child++;
        }
        if (lastElement <= heap->arr[child]) {
            break;
        }
        heap->arr[position] = heap->arr[child];
        position = child;
    }
    
    heap->arr[position] = lastElement;
    
    return minElement;
}

void insertMax(Heap* heap, int element) {
    int position = ++heap->position;
    while (position != 1 && element > heap->arr[position/2]) {
        heap->arr[position] = heap->arr[position/2];
        position /= 2;
    }
    
    heap->arr[position] = element;
}

int popMax(Heap* heap) {
    int maxElement = heap->arr[1];
    int lastElement = heap->arr[heap->position--];
    int position = 1;
    int child;
    
    while (position * 2 <= heap->position) {
        child = position * 2;
        if (child < heap->position && heap->arr[child] < heap->arr[child + 1]) {
            child++;
        }
        if (lastElement >= heap->arr[child]) {
            break;
        }
        heap->arr[position] = heap->arr[child];
        position = child;
    }
    
    heap->arr[position] = lastElement;
    
    return maxElement;
}

int main() {
    int n;
    scanf("%d", &n);

    Heap* min = getHeap(n);
    Heap* max = getHeap(n);

    int input = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &input);
        if (max->position < 1 || input <= max->arr[1])
            insertMax(max, input);
        else
            insertMin(min, input);

        if (max->position > min->position + 1)
            insertMin(min, popMax(max));
        else if (min->position > max->position)
            insertMax(max, popMin(min));

        printf("%d\n", max->arr[1]);
    }
}