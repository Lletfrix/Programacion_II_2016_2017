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

#define MAX 255

/*
 * 
 */
void print_status(FILE *pf, List* list){
    int size;
    if (!list){
        return;
    }
    size=list_size(list);
    fprintf(pf, "Lista con %d elementos:\n",size);
    list_print(pf,list);
}

int main(int argc, char** argv) {
    FILE *in=NULL, *f=stdout;
    List *mixList, *orderedList;
    char buff[MAX];
    int number, size,i, *element;
    
    if(argc<2){
        fprintf(stderr, "main: invalid number of arguments.\n");
        return (EXIT_FAILURE);
    }
    
    in=fopen(argv[1], "r");
    if(!in){
        fprintf(stderr, "main: error opening file.\n");
        return (EXIT_FAILURE);
    }
    
    mixList=list_ini(&destroy_intp_function, &copy_intp_function,
            &print_intp_function, &cmp_intp_function);
    
    if(!mixList){
        fclose(in);
        fprintf(stderr, "main: error creating list");
        return (EXIT_FAILURE);
    }
    
    while (!feof(in)) {
        fgets(buff, MAX, in);
        number = atoi(buff);
        if (number % 2 == 0) {
            mixList = list_insertFirst(mixList, &number);
            if(!mixList){
                fclose(in);
                fprintf(stderr, "main: error inserting even number");
                return (EXIT_FAILURE);
            }
        } else {
            mixList = list_insertLast(mixList, &number);
            if(!mixList){
                fclose(in);
                fprintf(stderr, "main: error inserting even number");
                return (EXIT_FAILURE);
            }
            
        }
        print_status(f, mixList);
        fprintf(f, "\n");

    }
    fclose(in);
    orderedList=list_ini(&destroy_intp_function, &copy_intp_function,
            &print_intp_function, &cmp_intp_function);
    if(!orderedList){
        list_destroy(mixList);
        return (EXIT_FAILURE);
    }
    size=list_size(mixList);
    for(i=0;i<(size/2);i++){
        fprintf(f, "\nExtrayendo elemento desde el principio de la lista...\n");
        element=list_extractFirst(mixList);
        if(!element){
            fprintf(f, "main: error extracting element");
            list_destroy(mixList);
            list_destroy(orderedList);
            return (EXIT_FAILURE);
        }
        fprintf(f, "Elemento extraído: [%d]\n", *element);
        print_status(f, mixList);
        fprintf(f, "\nInsertando elemento de forma ordenada en lista...\n");
        orderedList=list_insertInOrder(orderedList, element);
        if(!orderedList){
            fprintf(f, "main: error inserting element");
            free(element);
            list_destroy(mixList);
            return (EXIT_FAILURE);
        }
        free(element);
        print_status(f, orderedList);
    }
    while(!list_isEmpty(mixList)){
        fprintf(f, "\nExtrayendo elemento desde el final de la lista...\n");
        element=list_extractLast(mixList);
        if(!element){
            fprintf(f, "main: error extracting element");
            list_destroy(mixList);
            list_destroy(orderedList);
            return (EXIT_FAILURE);
        }
        fprintf(f, "Elemento extraído: [%d]\n", *element);
        print_status(f, mixList);
        fprintf(f, "\nInsertando elemento de forma ordenada en lista...\n");
        orderedList=list_insertInOrder(orderedList, element);
        if(!orderedList){
            fprintf(f, "main: error inserting element");
            free(element);
            list_destroy(mixList);
            return (EXIT_FAILURE);
        }
        free(element);
        print_status(f, orderedList);
    }
    
    
    list_destroy(mixList);
    list_destroy(orderedList);
    return (EXIT_SUCCESS);
}

