/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   list.c
 * Author: rafael
 * 
 * Created on 29 de marzo de 2017, 21:00
 */

#include "list.h"

typedef struct _ElementList {
    void* data;
    struct _ElementList *next;
} ElementList;

struct _List {
    ElementList *element;
    destroy_elementlist_function_type destroy_element_function;
    copy_elementlist_function_type copy_element_function;
    print_elementlist_function_type print_element_function;
    cmp_elementlist_function_type cmp_element_function;
};

List* list_ini(destroy_elementlist_function_type f1, copy_elementlist_function_type f2,
print_elementlist_function_type f3, cmp_elementlist_function_type f4){
    List* l=NULL;
    l=(List*)calloc(1,sizeof(List));
    if(!l){
        fprintf(stderr, "list_ini: error allocating memory.\n");
        return NULL;
    }
    
    l->element=(ElementList*)calloc(1,sizeof(ElementList));
    if(!l->element){
        fprintf(stderr, "list_ini: error allocating memory.\n");
        free(l);
        return NULL;
    }
    
    l->destroy_element_function=f1;
    l->copy_element_function=f2;
    l->print_element_function=f3;
    l->cmp_element_function=f4;
    
    return l;
}

void list_destroy(List* list) {
    void* aux;
    if (!list) {
        fprintf(stderr, "list_free: list pointing NULL.\n");
        return;
    }
    while (list->element->next) {
        aux = list->element;
        list->element = list->element->next;
        free(aux);
    }
    free(list->element);
    free(list);
}


