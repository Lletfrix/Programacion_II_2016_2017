/*
 * File:   p4_e2_test.c
 * Author: rafael
 *
 * Created on 18 de abril de 2017, 12:16
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "functions.h"

/*
 *
 */

int main(int argc, char** argv) {

    Node *n1,*n2;

    n1 = node_ini();
    n2 = node_ini();

    n1 = node_setName (n1,"first");
    n1 = node_setId (n1,111);
    n2 = node_setName (n2, "second");
    n2 = node_setId (n2, 222);

    node_print (stdout,n1);
    node_print (stdout,n2);

    if  (node_equals(n1,n2)) fprintf(stdout,"\nSon iguales? Si\n");
    if  (!node_equals(n1,n2)) fprintf(stdout,"\nSon iguales? No\n");

    fprintf(stdout,"Id del primer nodo: %d \n",node_getId(n1));
    fprintf(stdout,"Nombre del segundo nodo es: %s \n",node_getName(n2));

    node_destroy(n2);
    
    n2 = node_copy(n1);

    node_print (stdout,n1);
    node_print (stdout,n2);

    if  (node_equals(n1,n2)) fprintf(stdout,"\nSon iguales? Si\n");
    if  (!node_equals(n1,n2)) fprintf(stdout,"\nSon iguales? No\n");

    node_destroy(n1);
    node_destroy(n2);

    return EXIT_SUCCESS;
}
