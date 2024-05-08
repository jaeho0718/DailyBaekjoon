#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int Bool;

typedef struct {
    int value;
    int index;
} Element;

typedef struct {
    Element* arr;
    int size;
    int top;
} Stack;

Stack* setStack(int size) {
    Stack* temp = (Stack*) malloc(sizeof(Stack));
    temp->arr = (Element*) malloc(sizeof(Element)*size);
    temp->size = size;
    temp->top = -1;
    return temp;
}

Bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

Bool isFull(Stack* stack) {
    return stack->top == stack->size-1;
}

void push(Stack* stack, int index, int element) {
    if (isFull(stack)) return;
    stack->arr[++stack->top].index = index;
    stack->arr[stack->top].value = element;
}

Element pop(Stack* stack) {
    Element temp = {-1, -1};
    if (isEmpty(stack)) return temp;
    return stack->arr[stack->top--];
}

Element top(Stack* stack) {
    Element temp = {-1, -1};
    if (isEmpty(stack)) return temp;
    return stack->arr[stack->top];
}

int size(Stack* stack) {
    if (isEmpty(stack)) return 0;
    return stack->top+1;
}

int main() {
    int size, element;
    scanf("%d", &size);

    int* result = (int*) malloc(sizeof(int)*size);
    Stack* temp = setStack(size);

    Element topElement;
    for (int i = 0; i < size; i++) {
        scanf("%d", &element);
        topElement = top(temp);
        if (!isEmpty(temp) && topElement.value < element) {
            while (!isEmpty(temp)) {
                if (topElement.value < element) {
                    pop(temp);
                    result[topElement.index] = element;
                    topElement = top(temp);
                } else {
                    result[topElement.index] = -1;
                    break;
                }
            }
        }
        push(temp, i, element);
    }

    while (!isEmpty(temp)) {
        topElement = pop(temp);
        result[topElement.index] = -1;
    }

    for (int i = 0; i < size; i++) {
        printf("%d", result[i]);
        if (i < size-1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

    return 0;
}