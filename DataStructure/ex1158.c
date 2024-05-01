#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int number;
    struct Node* pre;
    struct Node* nex;
} NODE;

NODE* getList(int number) {
    NODE* head = (NODE*) malloc(sizeof(NODE));
    head->number = 1;
    NODE* current = head;
    NODE* new;
    for (int i = 1; i < number; i++) {
        new = (NODE*) malloc(sizeof(NODE));
        new->number = i+1;
        new->pre = current;
        current->nex = new;
        current = new;
    }
    current->nex = head;
    head->pre = current;
    return head;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    NODE* head = getList(n);
    NODE* current = head;
    NODE* next;
    printf("<");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k-1; j++) {
            current = current->nex;
        }
        printf("%d", current->number);
        printf((i < n-1) ? ", " : ">");
        if (current->nex == current) {
            break;
        }
        current->pre->nex = current->nex;
        current->nex->pre = current->pre;
        next = current->nex;
        current = next;
    }
    printf("\n");
}