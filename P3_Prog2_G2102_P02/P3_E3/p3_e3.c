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
    int *pe, entero, i;

    l=list_ini(&destroy_intp_function,&copy_intp_function,&print_intp_function,
            &cmp_intp_function);
    
    for(i=10;i>0;i--){
        entero=i;
        pe=&entero;
        list_insertFirst(l,pe);
    }
    
    list_print(stdout, l);
    list_destroy(l);
    return (EXIT_SUCCESS);
}

