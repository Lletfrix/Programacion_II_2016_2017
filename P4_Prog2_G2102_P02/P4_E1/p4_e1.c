/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
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
    Tree* t;
    int x;
    t=tree_ini(destroy_intp_function, copy_intp_function, print_intp_function, cmp_intp_function);
    if(!t){
        fprintf(stderr, "error.\n");
        return (EXIT_FAILURE);
    }
    x=6;
    if(tree_insert(t, &x)==ERROR){
        fprintf(stderr, "error.\n");
        tree_destroy(t);
        return (EXIT_FAILURE);
    }
    
    x=8;
    if(tree_insert(t, &x)==ERROR){
        fprintf(stderr, "error.\n");
        tree_destroy(t);
        return (EXIT_FAILURE);
    }
    
    tree_destroy(t);
    fprintf(stderr,"success!.\n");
    return (EXIT_SUCCESS);
}

