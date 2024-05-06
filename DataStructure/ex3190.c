#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct {
    short row;
    short column;
} Position;

typedef struct {
    Position* positions;
    int front;
    int rear;
    int size;
} Dequeue;

Dequeue* setDequeue(int size) {
    Dequeue* temp = (Dequeue*) malloc(sizeof(Dequeue));
    temp->size = size+1;
    temp->positions = (Position*) malloc(sizeof(Position));
    temp->front = 0;
    temp->rear = 0;
    return temp;
}

Position popFront(Dequeue* dequeue) {
    dequeue->front = (dequeue->front+1)%dequeue->size;
    return dequeue->positions[dequeue->front];
}

void pushRear(Dequeue* dequeue, short row, short column) {
    dequeue->rear = (dequeue->rear+1)%dequeue->size;
    dequeue->positions[dequeue->rear].row = row;
    dequeue->positions[dequeue->rear].column = column;
}

Position rear(Dequeue* dequeue) {
    return dequeue->positions[dequeue->rear];
}

int isEmpty(Dequeue* dequeue) {
    return dequeue->front == dequeue->rear;
}

int isFull(Dequeue* dequeue) {
    return dequeue->front == (dequeue->rear+1)%dequeue->size;
}

int isExit(Dequeue* dequeue, Position target) {
    int front = dequeue->front;
    for (int i = 0; i<dequeue->size; i++) {
        if (front == dequeue->rear) break;
        front = (front+1)%dequeue->size;
        if (dequeue->positions[front].row == target.row && dequeue->positions[front].column == target.column) {
            return 1;
        }
    }
    return 0;
}

int isOut(Position pos, int size) {
    return pos.column < 0 || pos.column >= size || pos.row < 0 || pos.row >= size;
}

int main() {
    int size = 0, appleCount = 0;
    scanf("%d", &size);
    scanf("%d", &appleCount);

    short** apples = (short**) malloc(sizeof(short*)*size);
    for (int i = 0; i < size; i++) {
        apples[i] = (short*) malloc(sizeof(short)*size);
        for (int j = 0; j < size; j++) {
            apples[i][j] = 0;
        }
    }

    short row, column;
    for (int i = 0; i < appleCount; i++) {
        scanf("%hd %hd", &row, &column);
        apples[row-1][column-1] = 1;
    }

    int changeCount;
    scanf("%d", &changeCount);
    int currentOrient = RIGHT;
    int** changes = (int**) malloc(sizeof(int*)*changeCount);
    char letter[2];
    for (int i = 0; i < changeCount; i++) {
        changes[i] = (int*) malloc(sizeof(int)*2);
        scanf("%d %s", &changes[i][0], letter);
        switch (currentOrient) {
            case UP: currentOrient = letter[0] == 'D' ? RIGHT: LEFT; break;
            case DOWN: currentOrient = letter[0] == 'D' ? LEFT: RIGHT; break;
            case RIGHT: currentOrient = letter[0] == 'D' ? DOWN: UP; break;
            case LEFT: currentOrient = letter[0] == 'D' ? UP: DOWN; break;
        }
        changes[i][1] = currentOrient;
    }

    int orient = RIGHT, timer = 0, currentChange = 0;
    Position nextPosition = {0, 0};
    Dequeue* snake = setDequeue(size*size);
    pushRear(snake, 0, 0);
    while(!isOut(rear(snake), size)) {
        if (currentChange < changeCount && changes[currentChange][0] == timer) {
            orient = changes[currentChange++][1];
        }
        switch (orient) {
            case UP: nextPosition.row--; break;
            case DOWN: nextPosition.row++; break;
            case LEFT: nextPosition.column--; break;
            case RIGHT: nextPosition.column++; break;
        }
        timer++;
        // 자기몸과 부딪치는지 확인
        if (isExit(snake, nextPosition)) {
            break;
        }
        pushRear(snake, nextPosition.row, nextPosition.column);
        if (nextPosition.row >= 0 && nextPosition.row < size && nextPosition.column >= 0 && nextPosition.column < size) {
            if (apples[nextPosition.row][nextPosition.column] > 0) {
                apples[nextPosition.row][nextPosition.column] = 0;
            } else {
                popFront(snake);
            }
        }
    }
    
    printf("%d\n", timer);

    return 0;
}