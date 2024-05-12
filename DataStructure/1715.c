#include <stdio.h>
#include <stdlib.h>

int pop(int* arr, int* position) {
    if (*position < 1) return 0;
    int parent = 1;
    int child = 2;
    int temp = arr[*position];
    *position = *position-1;
    int first = arr[1];
    while (child <= *position) {
        if (child < *position && arr[child] > arr[child+1])
            child++;
        if (temp <= arr[child]) break;
            arr[parent] = arr[child];
        parent = child;
        child *= 2;
    }
    arr[parent] = temp;
    return first;
}

void insert(int* arr, int* position, int input) {
    int current = ++(*position);

    while (current != 1 && input < arr[current/2]) {
        arr[current] = arr[current/2];
        current = current/2;
    }
    arr[current] = input;
}

int main() {
    int size = 0;
    scanf("%d", &size);
    
    int* arr = (int*) malloc(sizeof(int)*(size+1));
    int position = 0, input = 0;
    for (int i = 0; i < size; i++) {
        scanf("%d", &input);
        insert(arr, &position, input);
    }

    if (size <= 1) {
        printf("0\n");
        return 0;
    }

    int sum = 0;
    int a, b;
    while (position > 1) {
        a = pop(arr, &position);
        b = pop(arr, &position);
        sum += (a+b);
        if (a+b != 0)
            insert(arr, &position, a+b);
    }
    printf("%d\n", sum);
    free(arr);
    return 0;
}