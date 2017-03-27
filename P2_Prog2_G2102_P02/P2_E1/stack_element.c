#include <stdio.h>
#include <stdlib.h>
#include "stack_element.h"

/*
 * 
 */

struct _Stack {
    Element* data[MAXSTACK];
    int top;
};

Stack * stack_ini() {
    Stack* stack;

    stack = (Stack*) malloc(sizeof (Stack));

    if (!stack) {
        return NULL;
    }

    stack->top = -1;

    return stack;
}

void stack_destroy(Stack* stack) {
    int i=0;

    if (!stack) {
        return;
    }

    for (i = 0; i <= stack->top; i++) {
        element_destroy(stack->data[i]);
    }
  

    free(stack);
}

Stack * stack_push(Stack *stack, const Element *ele) {

    if ((!stack) || (!ele)) {
        return NULL;
    }

    stack->data[stack->top + 1] = element_copy(ele);

    if (stack->data[stack->top + 1] == NULL) {
        return NULL;
    }
    stack->top++;
    return stack;
}


Element * stack_pop(Stack *stack) {

  if (!stack ||  stack_isEmpty(stack) ==TRUE ){
    return NULL;
  }

    stack->top--;

    return (stack->data[stack->top+1]);
}

Element * stack_top(const Stack *stack) {
    Element* ele;

  if (!stack ||  stack_isEmpty(stack) ==TRUE ){
    return NULL;
  }

    return (stack->data[stack->top]);
}

Bool stack_isEmpty(const Stack *stack) {
    if (stack->top < 0) {
        return TRUE;
    }
    return FALSE;
}

Bool stack_isFull(const Stack *stack) {
    if (stack->top == MAXSTACK - 1) {
        return TRUE;
    }
    return FALSE;
}

int stack_print(FILE*pf, const Stack*stack) {
    int charsNum = 0, i;

    if ((!pf) || (!stack)) {
        return -1;
    }

    for (i = stack->top; i >= 0; i--) {

        charsNum += element_print(pf, stack->data[i]);

        charsNum += fprintf(pf, "\n");

    }

    return charsNum;
}
