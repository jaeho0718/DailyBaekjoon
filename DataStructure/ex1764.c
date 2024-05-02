#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 21

int sortByAlphabet(const void* lhs, const void* rhs) {
    char* str1 = *((char**) lhs);
    char* str2 = *((char**) rhs);
    return strcmp(str1, str2);
}

// 찾으면 인덱스 반환 없으면 -1 반환
int search(const char** strs, const int strsSize,  char* input) {
    int start = 0;
    int end = strsSize-1;
    int mid = (start+end)/2;

    while (start < end) {
        int compare = strcmp(strs[mid], input);
        if (compare < 0) {
            start = mid+1;
        } else if (compare == 0) {
            return mid;
        } else {
            end = mid-1;
        }
        mid = (start+end)/2;
    }
    if (strcmp(strs[start], input) == 0) return start;
    return -1;
}

int main() {
    int n, k;
    char input[MAX_BUFFER];

    fgets(input, MAX_BUFFER, stdin);
    char* token = strtok(input, " ");
    n = atoi(token);
    token = strtok(NULL, "\n \0");
    k = atoi(token);

    // 듣도못한사람 입력
    char** unheard = (char**) malloc(sizeof(char*)*n);
    for (int i = 0; i < n; i++) {
        fgets(input, MAX_BUFFER, stdin);
        input[strcspn(input, "\n")] = 0;
        unheard[i] = (char*) malloc(sizeof(char)*strlen(input));
        strcpy(unheard[i], input);
    }
    qsort(unheard, n, sizeof(char*), sortByAlphabet);

    // 보지못한사람 입력후 듣도못한사람리스트에 포함여부 확인
    char** result = (char**) malloc(sizeof(char*)*k);
    int resultSize = 0;
    int searchIndex = -1;
    for (int i = 0; i < k; i++) {
        fgets(input, MAX_BUFFER, stdin);
        input[strcspn(input, "\n")] = 0;
        searchIndex = search(unheard, n, input);
        if (searchIndex >= 0) {
            result[resultSize++] = unheard[searchIndex];
        }
    }

    // 결과 출력
    qsort(result, resultSize, sizeof(char*), sortByAlphabet);
    printf("%d\n", resultSize);
    for (int i = 0; i < resultSize; i++) {
        printf("%s\n", result[i]);
    }

    // 메모리 해제
    for (int i = 0; i < n; i++) {
        free(unheard[i]);
    }
    free(unheard);
    free(result);

    return 0;
}