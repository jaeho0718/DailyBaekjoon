#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 400001
#define TRUE 1
#define FALSE 0

typedef int Bool;

typedef struct {
    int* arr;
    int size;
    int front;
    int rear;
} Dequeue;

Dequeue* setDequeue(int size) {
    Dequeue* temp = (Dequeue*) malloc(sizeof(Dequeue));
    temp->arr = (int*) malloc(sizeof(int)*(size+1));
    temp->front = 0;
    temp->rear = 0;
    temp->size = size+1;
    return temp;
}

void removeDequeue(Dequeue* dequeue) {
    free(dequeue->arr);
    free(dequeue);
}

int isEmpty(Dequeue* dequeue) {
    return dequeue->front == dequeue->rear;
}

int isFull(Dequeue* dequeue) {
    return dequeue->front == (dequeue->rear+1)%dequeue->size;
}

void pushFront(Dequeue* dequeue, int element) {
    if (isFull(dequeue)) return;
    dequeue->arr[dequeue->front] = element;
    dequeue->front = (dequeue->front-1 >= 0) ? dequeue->front-1 : dequeue->size-1;
}

void pushRear(Dequeue* dequeue, int element) {
    if (isFull(dequeue)) return;
    dequeue->rear = (dequeue->rear+1)%dequeue->size;
    dequeue->arr[dequeue->rear] = element;
}

int popFront(Dequeue* dequeue) {
    if (isEmpty(dequeue)) return -1;
    dequeue->front = (dequeue->front+1)%dequeue->size;
    return dequeue->arr[dequeue->rear];
}

int popRear(Dequeue* dequeue) {
    if (isEmpty(dequeue)) return -1;
    int element = dequeue->arr[dequeue->rear];
    dequeue->rear = (dequeue->rear-1 >= 0) ? dequeue->rear-1 : dequeue->size-1;
    return element;
}

void printDequeue(Dequeue* dequeue) {
    printf("[");
    int front = dequeue->front;
    for (int i = 0; i < dequeue->size; i++) {
        if (front == dequeue->rear) {
            break;
        }
        front = (front+1)%dequeue->size;
        printf("%d", dequeue->arr[front]);
        if (front != dequeue->rear) {
            printf(",");
        }
    }
    printf("]\n");
}

void printReverseDequeue(Dequeue* dequeue) {
    printf("[");
    int rear = dequeue->rear;
    for (int i = 0; i < dequeue->size; i++) {
        if (dequeue->front == rear) {
            break;
        }
        printf("%d", dequeue->arr[rear]);
        rear = (rear-1 >= 0) ? (rear-1)%dequeue->size: rear-1;
        if (dequeue->front != rear) {
            printf(",");
        }
    }
    printf("]\n");
}

int main() {
    char input[10] = { 0 };
    char* delimeter = " \n\0[],";
    fgets(input, MAX_BUFFER, stdin);
    char* token = strtok(input, delimeter);

    int testCases = atoi(token);
    char arrStr[MAX_BUFFER] = { 0 };
    char operator[MAX_BUFFER] = { 0 };
    char countStr[10] = { 0 };
    int count = 0, popResult = 0, operateCount = 0;
    Dequeue* dequeue;
    Bool isReverse = FALSE;
    for (int i = 0; i < testCases; i++) {
        isReverse = FALSE;
        popResult = 0;
        fgets(operator, MAX_BUFFER, stdin); // 연산함수

        fgets(countStr, 10, stdin);
        token = strtok(countStr, delimeter);
        count = atoi(token);
        dequeue = setDequeue(count);

        fgets(arrStr, MAX_BUFFER, stdin);
        token = strtok(arrStr, "[,]");
        for (int j = 0; j < count; j++) {
            if (token == NULL) break;
            pushRear(dequeue, atoi(token));
            token = strtok(NULL, "[,]");
        }

        operateCount = 0;
        while (TRUE) {
            if (operator[operateCount] == 'D') {
                if (isReverse) {
                    popResult = popRear(dequeue);
                } else {
                    popResult = popFront(dequeue);
                }
                if (popResult == -1) {
                    printf("error\n");
                    break;
                }
            } else if (operator[operateCount] == 'R'){
                isReverse = isReverse ? FALSE: TRUE;
            } else {
                break;
            }
            operateCount++;
        }

        if (popResult >= 0) {
            if (isReverse) {
                printReverseDequeue(dequeue);
            } else {
                printDequeue(dequeue);
            }
        }

        removeDequeue(dequeue);
    }

    return 0;
}