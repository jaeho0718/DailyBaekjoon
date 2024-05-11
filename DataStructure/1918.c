#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 110

int isAlphabet(char value) {
    return (value-'A' >= 0) && ('Z'-value >= 0);
}

int order(char value) {
    switch (value) {
        case '(': return 0;
        case '-': return 2;
        case '+': return 2;
        case '*': return 3;
        case '/': return 3;
        case ')': return 5;
    }
    return 0;
}

int main() {
    char input[BUFFER_SIZE] = { 0 };
    fgets(input, BUFFER_SIZE, stdin);
    int length = strlen(input);

    char result[BUFFER_SIZE] = { 0 };
    char stack[BUFFER_SIZE] = { 0 };
    int topOfResult = -1;
    int topOfStack = -1;

    for (int i = 0; i < length; i++) {
        if (isAlphabet(input[i])) {
            result[++topOfResult] = input[i];
        } else if (input[i] == ')') {
            if (topOfStack >= 0)
                while(stack[topOfStack] != '(')
                    result[++topOfResult] = stack[topOfStack--];
            topOfStack--;
        } else if (input[i] == '(') {
            stack[++topOfStack] = input[i];
        } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            while (topOfStack >= 0 && order(stack[topOfStack]) >= order(input[i]))
                result[++topOfResult] = stack[topOfStack--];
            stack[++topOfStack] = input[i];
        }
    }

    while (topOfStack >= 0) {
        result[++topOfResult] = stack[topOfStack--];
    }

    for (int i = 0; i < topOfResult+1; i++)
        printf("%c", result[i]);
    printf("\n");

    return 0;
}