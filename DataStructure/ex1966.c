#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_BUFFER 300
#define True 1
#define False 0

typedef int Bool;

typedef struct {
    Bool isTarget;
    int priority;
} Node;

typedef struct {
    int front;
    int rear;
    int size;
    Node* nodes;
} Queue;

Bool isEmpty(Queue* queue) {
    return queue->front == queue->rear ? True: False;
}

void push(Queue* queue, int priority, Bool isTarget) {
    queue->rear = (queue->rear+1)%queue->size;
    queue->nodes[queue->rear].isTarget = isTarget;
    queue->nodes[queue->rear].priority = priority;
}

Node* pop(Queue* queue) {
    if (isEmpty(queue)) return NULL;
    queue->front = (queue->front+1)%queue->size;
    return &queue->nodes[queue->front];
}

Node* front(Queue* queue) {
    if (isEmpty(queue)) return NULL;
    return &queue->nodes[(queue->front+1)%queue->size];
}

Bool isMax(Queue* queue, int priority) {
    int front = queue->front;
    int rear = queue->rear;
    for (int i = 0; i < queue->size; i++) {
        if (front == rear) return True;
        front = (front+1)%queue->size;
        if (queue->nodes[front].priority > priority) return False;
    }
    return True;
}

int main() {
    char input[INPUT_BUFFER] = { 0 };
    char* token;

    int cases = 0;
    fgets(input, INPUT_BUFFER, stdin);
    char* delimeter = " \n\0";
    token = strtok(input, delimeter);
    cases = atoi(token);
    
    Queue* queue;
    int documentCount, targetIndex, priority;
    for (int i = 0; i < cases; i++) {
        fgets(input, INPUT_BUFFER, stdin);
        token = strtok(input, delimeter);
        documentCount = atoi(token);
        token = strtok(NULL, delimeter);
        targetIndex = atoi(token);
        queue = (Queue*) malloc(sizeof(Queue));
        queue->nodes = (Node*) malloc(sizeof(Node)*(documentCount+1));
        queue->front = 0;
        queue->rear = 0;
        queue->size = documentCount+1;

        fgets(input, INPUT_BUFFER, stdin);
        token = strtok(input, delimeter);
        for (int i = 0; i < documentCount; i++) {
            priority = atoi(token);
            push(queue, atoi(token), i == targetIndex);
            token = strtok(NULL, delimeter);
        }
        
        Node* peek;
        int order = 0;
        while (!isEmpty(queue)) {
            peek = front(queue);
            if (peek == NULL) break;
            if (isMax(queue, peek->priority)) {
                peek = pop(queue);
                if (peek == NULL) break;
                order++;
                if (peek->isTarget) break;
            } else {
                peek = pop(queue);
                if (peek == NULL) break;
                push(queue, peek->priority, peek->isTarget);
            }
        }
        printf("%d\n", order);
        peek = NULL;
        free(queue->nodes);
        free(queue);
    }

    return 0;
}