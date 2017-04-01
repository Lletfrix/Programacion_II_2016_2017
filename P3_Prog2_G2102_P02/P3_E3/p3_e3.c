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
    int *pe, entero=4;
    pe=&entero;

    l=list_ini(&destroy_intp_function,&copy_intp_function,&print_intp_function,
            &cmp_intp_function);
    list_insertFirst(l, pe);
    list_destroy(l);
    return (EXIT_SUCCESS);
}

