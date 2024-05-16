#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 1000003

int main() {
    char input[MAX_BUFFER];
    fgets(input, MAX_BUFFER, stdin);
    int i = 0;

    int topOfSticks = -1;
    int topOfLasers = -1;

    int total = 0;
    while (input[i] != '\0') {
        if (input[i] == '(') {
            if (topOfLasers >= 0) topOfSticks++;
            else  topOfLasers++;
        } else if (input[i] == ')') {
            if (topOfLasers >= 0) {
                topOfLasers--;
                total += (topOfSticks+1);
            } else {
                topOfSticks--;
                total += 1;
            }
        }
        i++;
    }

    printf("%d\n", total);

    return 0;
}