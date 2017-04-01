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
