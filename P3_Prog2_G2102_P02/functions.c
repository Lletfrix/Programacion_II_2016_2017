/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.c
 * Author: rafael
 * 
 * Created on 16 de marzo de 2017, 12:36
 */

#include "functions.h"
#include "list.h"
/* Las siguientes funciones se usarán cuando se quieran guardar enteros en la pila. Ojo! Estas funciones
reciben un puntero a entero, no una estructura con un puntero a entero (como en el ejercicio P2_E1) */

void destroy_intp_function(void* e) {
    free((int*) e);
}

void * copy_intp_function(const void* e) {
    int * dst;
    if (e == NULL)
        return NULL;
    dst = (int*) malloc(sizeof (int));
    /*Copiamos el elemento*/
    *(dst) = *((int*) e);
    return dst;
}

int print_intp_function(FILE * f, const void* e) {
    if (f != NULL && e != NULL)
        return fprintf(f, "[%d]", *((int*) e));
    return -1;
}

int cmp_intp_function(const void* e1, const void* e2){
    int *i1, *i2, retorno;
    if (!e1 || !e2){
        fprintf(stderr,"cpm_intp_function: invalid arguments");
        return 0;
    }
    i1=(int*)e1;
    i2=(int*)e2;
    retorno=(*i1)-(*i2);
    return retorno;
}

/* Las siguientes se usarán cuando se quieran guardar nodos en la pila */
void destroy_node_function(void* e) {
    node_destroy((Node *) e);
}

void * copy_node_function(const void* e) {
    return node_copy((Node *) e);
}

int print_node_function(FILE * f, const void* e) {
    return node_print(f, (Node *) e);
}

int cmp_node_function(const void* e1, const void* e2){
    if (!e1 || !e2){
        fprintf(stderr,"cpm_intp_function: invalid arguments");
        return 0;
    }
    return node_getId(e1)-node_getId(e2);
}

/* Las siguientes se usarán cuando se quieran guardar conexiones de nodos en la lista */

typedef struct _NodeConnections {
    int nodeid;
    List* connections; /* Lista de enteros */
} NodeConnections;

void destroy_nodeConnections_function(void* e) {
    NodeConnections* n;
    if(!e){
        fprintf(stderr, "Internal error");
    }
    n=(NodeConnections*)e;
    list_destroy(n->connections);
    free (n);
}

void * copy_nodeConnections_function(const void* e) {
    NodeConnections * dst, *eNode;
    int i, size;
    if (e == NULL)
        return NULL;
    eNode=(NodeConnections*)e;
    dst = (NodeConnections*) malloc(sizeof (NodeConnections));
    dst->connections=list_ini(&destroy_intp_function,&copy_intp_function,&print_intp_function,&cmp_intp_function);
    size=list_size(eNode->connections);
    /*Copiamos el elemento*/
    dst->nodeid = eNode->nodeid;
    for(i=size;i>1;i--){
        list_insertFirst(dst->connections, list_get(eNode->connections, i));
    }
    return dst;
}

int print_nodeOutConnections_function(FILE * f, const void* e) {
    NodeConnections* eNode;
    int chars=0;
    if (f != NULL && e != NULL){
        eNode=(NodeConnections*)e;
        chars+=fprintf(f, "node with id:[%d] is connected to:\n", eNode->nodeid);
        chars+=list_print(f, eNode->connections);
        return chars;
    }
        
    return -1;
}

int print_nodeInConnections_function(FILE * f, const void* e) {
    NodeConnections* eNode;
    int chars=0;
    if (f != NULL && e != NULL){
        eNode=(NodeConnections*)e;
        chars+=fprintf(f, "node with id:[%d] is connected from:\n", eNode->nodeid);
        chars+=list_print(f, eNode->connections);
        return chars;
    }
        
    return -1;
}

int cmp_nodeConnections_function(const void* e1, const void* e2){
    int retorno;
    NodeConnections* ne1, *ne2;
    if (!e1 || !e2){
        fprintf(stderr,"cpm_intp_function: invalid arguments");
        return 0;
    }
    ne1=(NodeConnections*)e1;
    ne2=(NodeConnections*)e2;
    retorno=ne1->nodeid - ne2->nodeid;
    return retorno;
}
