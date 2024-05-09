#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int destination, int element) {
    arr[element] = destination;
}

int find(int* arr, int target) {
    if (arr[target] == target) return target;
    int parent = arr[target];
    arr[target] = arr[parent];
    return find(arr, arr[target]);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int* arr = (int*) malloc(sizeof(int)*(n+1));
    for (int i = 0; i < n+1; i++) {
        arr[i] = i; // 0, 1, 2, 3...n로 초기화
    }

    int type, a, b;
    int aGroup, bGroup;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &type, &a, &b);
        switch (type) {
            case 0:
                if (arr[a] != a || arr[b] != b) {
                    // 대표노드가 아닐시, 대표노드를 찾아 병합
                    aGroup = find(arr, a);
                    bGroup = find(arr, b);
                    merge(arr, aGroup, bGroup);
                } else {
                    merge(arr, a, b);
                }
                break;
            case 1:
                aGroup = find(arr, a);
                bGroup = find(arr, b);
                printf(aGroup == bGroup ? "YES" : "NO");
                printf("\n");
                break;
        }
    }

    free(arr);
    
    return 0;
}