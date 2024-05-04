#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sort(const void* rhs, const void* lhs) {
    int n1 = *((int*) rhs);
    int n2 = *((int*) lhs);
    return n1-n2;
}

int binarySearch(int* arr, int size, int target) {
    int start = 0, end = size-1, mid = 0;
    while (start < end) {
        mid = (start+end)/2;
        if (arr[mid] > target) {
            end = mid-1;
        } else if (arr[mid] == target) {
            return mid;
        } else {
            start = mid+1;
        }
    }
    return (arr[start] == target) ? start : -1;
}

int main() {
    int n, m;
    scanf("%d", &n);

    int* decks = (int*) malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &decks[i]);
    }
    qsort(decks, n, sizeof(int), sort);

    scanf("%d", &m);
    int target = 0, result = -1;
    for (int i = 0; i < m; i++) {
        scanf("%d", &target);
        result = binarySearch(decks, n, target);
        printf("%d", result >= 0 ? 1 : 0);
        if (i < m-1) {
            printf(" ");
        }
    }
    printf("\n");

    free(decks);
    return 0;
}