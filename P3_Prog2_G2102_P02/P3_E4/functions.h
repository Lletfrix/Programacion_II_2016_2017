/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.h
 * Author: rafael
 *
 * Created on 16 de marzo de 2017, 12:36
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void destroy_intp_function(void*);

void* copy_intp_function(const void*);

int print_intp_function(FILE *, const void*);

int cmp_intp_function(const void*, const void*);

/* Las siguientes se usarán cuando se quieran guardar nodos en la pila */
void destroy_node_function(void*);

void * copy_node_function(const void*);

int print_node_function(FILE *, const void*);

int cmp_node_function(const void*, const void*);



#endif /* FUNCTIONS_H */