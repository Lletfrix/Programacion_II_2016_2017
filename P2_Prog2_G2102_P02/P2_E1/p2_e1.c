#include "stack_element.h"
#include <stdio.h>
#include <stdlib.h>

void stack_printCheck(Stack* stack) {
    switch (stack_isEmpty(stack)) {

        case TRUE:
            printf("(no llena, vacía)");
            break;

        default:
            switch (stack_isFull(stack)) {
                case TRUE:
                    printf("(llena, no vacía)");
                    break;

                default:
                    printf("(no llena, no vacía)");
            }
    }
}

int main(int argc, char** argv) {
    int numElem, myInt, i;
    Stack* stack, *stackEven, *stackOdd;
    Element* ele;

    if (argc < 2) {
        printf("\nInvalid number of arguments.\n");
        return EXIT_FAILURE;
    }

    stack = stack_ini();
    stackEven = stack_ini();
    stackOdd = stack_ini();
    ele = element_ini();
    numElem = atoi(argv[1]);

    printf("> %s %s\n", argv[0], argv[1]);

    printf("Pila total ");
    stack_printCheck(stack);
    printf(":\n");

    printf("\n");

    for (i = 0; i < numElem; i++) {
        printf("Introduce número: ");
        scanf("%d", &myInt);
        element_setInfo(ele, &myInt);
        stack = stack_push(stack, ele);
    }
    printf("\n");
    element_destroy(ele);

    printf("Pila total ");
    stack_printCheck(stack);
    printf(":\n");
    stack_print(stdout, stack);

    while (!(stack_isEmpty(stack))) {

        ele = stack_pop(stack);
        myInt = *((int*) element_getInfo(ele));

        if ((myInt % 2) == 0) {
            stackEven = stack_push(stackEven, ele);
            element_destroy(ele);
        }
        else{
            stackOdd = stack_push(stackOdd, ele);
            element_destroy(ele);
        }
    }

    printf("\n");
    printf("Imprimiendo la pila ");
    stack_printCheck(stackEven);
    printf(" con números pares:\n");
    stack_print(stdout, stackEven);

    printf("Imprimiendo la pila ");
    stack_printCheck(stackOdd);
    printf(" con números impares:\n");
    stack_print(stdout, stackOdd);

    printf("\n\n");
    printf("Pila total ");
    stack_printCheck(stack);
    printf(":\n");

    
    stack_destroy(stack);
    stack_destroy(stackOdd);
    stack_destroy(stackEven);

    return (EXIT_SUCCESS);
}