#include <stdlib.h>
#include "node.h"

int main() {

    Node *n1,*n2;
    
    n1 = node_ini();
    n2 = node_ini();
    
    n1 = node_setName (n1,"first");
    n1 = node_setId (n1,111);
    n2 = node_setName (n2, "second");
    n2 = node_setId (n2, 222);
    
    node_print (stdout,n1);
    node_print (stdout,n2);
    fprintf(stdout,"\n");
    
    if  (node_equals(n1,n2) == FALSE) fprintf(stdout,"Son iguales? No\n");
    
    fprintf(stdout,"Id del primer nodo: %d \n",node_getId(n1));
    fprintf(stdout,"Nombre del segundo nodo es: %s \n",node_getName(n2));
    
    node_destroy(n2);
    
    /* we must free the memory of the node before copying it */
    
    n2 = node_copy(n1);
    
    node_print (stdout,n1);
    node_print (stdout,n2);
    fprintf(stdout,"\n");
    
    if  (node_equals(n1,n2) == TRUE) fprintf(stdout,"Son iguales? Si\n");
    
    node_destroy(n1);
    node_destroy(n2);
    
    return EXIT_SUCCESS;
}

