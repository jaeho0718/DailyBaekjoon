#include <stdio.h>
#define SIZE 3
#define SIDE_COUNT 6
#define TOTAL SIZE*SIZE*SIDE_COUNT

enum SIDE {U, D, F, B, L, R};
/*            U
          0  1  2
          3  4  5
          6  7  8
L        __________    R            B
36 37 38|F18 19 20 | 45 46 47 | 27 28 29
39 40 41| 21 22 23 | 48 49 50 | 30 31 32
42 43 44| 24 25 26 | 51 52 53 | 33 34 35
        -----------
          9  10 11
          12 13 14
          15 16 17
          D
*/ 
int sides[SIDE_COUNT][SIZE*4] = {
        {36, 37, 38, 18, 19, 20, 45, 46, 47, 27, 28, 29}, // U
        {33, 34, 35, 51, 52, 53, 24, 25, 26, 42, 43, 44}, // D
        {6, 7, 8, 44, 41, 38, 11, 10, 9, 45, 48, 51}, // F
        {2, 1, 0, 53, 50, 47, 15, 16, 17, 36, 39, 42}, // B
        {0, 3, 6, 35, 32, 29, 9, 12, 15, 18, 21, 24}, // L
        {8, 5, 2, 26, 23, 20, 17, 14, 11, 27, 30, 33} // R
    };

char colors[SIDE_COUNT] = {'w', 'y', 'r', 'o', 'g', 'b'};

void rotate(enum SIDE side, char arr[TOTAL], int count) {
    char temp[SIZE*4];
    char face[SIZE][SIZE];
    int index = 0;

    while (count--) {
        for (int i = 0; i < SIZE*4; i++) {
            temp[i] = arr[sides[side][i]];
        }
        // 3칸씩 오른쪽으로 이동
        for (int i = 0; i < 12; i++) {
            arr[sides[side][i]] = temp[(i+3)%(SIZE*4)];
        }

        // 기준면 회전
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                index = side*SIZE*SIZE+i*SIZE+j;
                face[j][SIZE-1-i] = arr[index];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                index = side*SIZE*SIZE+i*SIZE+j;
                arr[index] = face[i][j];
            }
        }
    }
}

int main() {
    char arr[TOTAL];
    int testCase = 0;
    scanf("%d", &testCase);

    char input[3];
    int count = 0, index = 0;
    int cases[256] = { 0 };
    cases['+'] = 1;
    cases['-'] = 3;
    cases['U'] = U;
    cases['D'] = D;
    cases['F'] = F;
    cases['B'] = B;
    cases['L'] = L;
    cases['R'] = R;

    while (testCase--) {
        // 큐브 초기화
        for (int s = 0; s < SIDE_COUNT; s++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    arr[s*SIZE*SIZE+i*SIZE+j] = s*SIZE*SIZE+i*SIZE+j;
                }
            }
        }

        scanf("%d", &count);
        
        while (count--) {
            scanf("%s", input);
            rotate((enum SIDE)cases[input[0]], arr, cases[input[1]]);
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                index = U*SIZE*SIZE+i*SIZE+j;
                printf("%c", colors[arr[index]/(SIZE*SIZE)]);
            }
            printf("\n");
        }
    }
}
