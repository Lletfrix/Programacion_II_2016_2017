/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p3_e3.c
 * Author: rafael
 *
 * Created on 29 de marzo de 2017, 20:59
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "functions.h"

/*
 * 
 */
int main(int argc, char** argv) {
    List* l;
    l=list_ini(&destroy_node_function,&copy_node_function,&print_node_function,
            &cmp_node_function);
    list_destroy(l);
    return (EXIT_SUCCESS);
}

