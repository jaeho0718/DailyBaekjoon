// Created on iPhone.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
   int value;
   int order;
} Element;

int main() {
   int n, input;
   scanf("%d", &n);
   
   Element* stack = (Element*) malloc(sizeof(Element)*n);
   int top = -1;
   
   for (int i = 0; i < n; i++) {
      scanf("%d", &input);
      while (top > -1 && stack[top].value < input) {
         top--;
      }
      if (top >= 0 && stack[top].value >= input) {
         printf("%d", stack[top].order);
      } else {
         printf("0");
      }
      stack[++top].order = i+1;
      stack[top].value = input;
      if (i < n-1)
         printf(" ");
      else
         printf("\n");
   }
   free(stack);
   return 0;
}