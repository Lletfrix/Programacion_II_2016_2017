#include "stack.h"

struct _Stack {
    int top;
    void * item[MAXSTACK];
    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
};

Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3) {

    Stack* s;
    if (!f1 || !f2 || !f3) {
        fprintf(stderr, "stack_ini: Argument error.\n");
        return NULL;
    }
    s = (Stack*) malloc(sizeof (Stack));
    if (!s) {
        fprintf(stderr, "stack_ini: Error allocating memory.\n");
        return NULL;
    }

    s->destroy_element_function = f1;
    s->copy_element_function = f2;
    s->print_element_function = f3;
    s->top = -1;
    return s;
}

void stack_destroy(Stack *s) {
    int i;
    if (!s) {
        fprintf(stderr, "stack_destroy: Argument error.\n");
        return;
    }
    for (i = 0; i <= s->top; i++) {
        s->destroy_element_function(s->item[i]);
    }
    free(s);
}

Stack * stack_push(Stack *s, const void *e) {
    void* element;
    if (!s || !e) {
        fprintf(stderr, "stack_push: Argument error.\n");
        return NULL;
    }
    
    if(stack_isFull(s)==TRUE){
        fprintf(stderr, "stack_push: Stack is already full.\n");
        return NULL;
    }
    
    element = s->copy_element_function(e);

    if (!element) {
        fprintf(stderr, "stack_push: Error copying element.\n");
        return NULL;
    }

    s->top++;
    s->item[s->top] = element;
    return s;
}

void * stack_pop(Stack *s) {
    if (!s) {
        fprintf(stderr, "stack_pop: Argument error.\n");
        return NULL;
    }
    if (stack_isEmpty(s)) {
        fprintf(stderr, "stack_pop: Stack is empty\n");
        return NULL;
    }
    s->top--;
    return s->item[s->top + 1];
}

void * stack_top(const Stack *s) {
    if (!s) {
        fprintf(stderr, "stack_top: Argument error.\n");
        return NULL;
    }
    if (stack_isEmpty(s)) {
        fprintf(stderr, "stack_top: Stack is empty.\n");
        return NULL;
    }
    return s->item[s->top];

}

Bool stack_isEmpty(const Stack *s) {
    if (!s) {
        fprintf(stderr, "stack_isEmpty: Argument error");
        return FALSE;
    }
    if (s->top == -1) {
        return TRUE;
    }
    return FALSE;
}

Bool stack_isFull(const Stack *s) {
    if (!s) {
        fprintf(stderr, "stack_isFull: Argument error.\n");
        return FALSE;
    }
    if (s->top == MAXSTACK - 1) {
        return TRUE;
    }
    return FALSE;
}

int stack_print(FILE* f, const Stack* s) {
    int chars, i;
    if (!f || !s) {
        fprintf(stderr, "stack_print: Argument error.\n");
        return -1;
    }
    for (i = 0, chars = 0; i <= s->top; i++) {
        chars += s->print_element_function(f, s->item[s->top - i]);
        chars += fprintf(f, "\n");
    }

    return chars;
}
