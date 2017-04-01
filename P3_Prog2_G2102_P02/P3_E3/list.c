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

ElementList* element_ini(){
    ElementList* ele;
    ele=(ElementList*)calloc(1,sizeof(ElementList));
    if(!ele){
        fprintf(stderr, "element_ini: error allocating memory.\n");
        return NULL;
    }
    return ele;
}

List* list_ini(destroy_elementlist_function_type f1, copy_elementlist_function_type f2,
print_elementlist_function_type f3, cmp_elementlist_function_type f4){
    List* l=NULL;
    l=(List*)calloc(1,sizeof(List));
    if(!l){
        fprintf(stderr, "list_ini: error allocating memory.\n");
        return NULL;
    }
    
    l->element=element_ini();
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
    ElementList* aux;
    if (!list) {
        fprintf(stderr, "list_free: list pointing NULL.\n");
        return;
    }
    
    while (list->element->next) {
        aux = list->element;
        list->element = list->element->next;
        list->destroy_element_function(aux->data);
        free(aux);
    }
    
    list->destroy_element_function(list->element->data);
    free(list->element);
    free(list);
}

List* list_insertFirst(List* list, const void *elem){
    ElementList *eleAux;
    if (!list || !elem){
        fprintf(stderr, "list_insertFirst: invalid arguments.\n");
        list_destroy(list);
        return NULL;
    }
    eleAux=element_ini();
    if(!eleAux){
        fprintf(stderr, "list_insertFirst: error allocating memory\n");
        list_destroy(list);
        return NULL;
    }
    eleAux->next=list->element;
    eleAux->data=list->copy_element_function(elem);
    if (!eleAux->data){
        fprintf(stderr,"list_insertFirst: error copying element\n");
        free(eleAux);
        list_destroy(list);
        return NULL;
    }
    list->element=eleAux;
    
    return list;
}

List* list_insertLast(List* list, const void *elem){
    ElementList *eleFirst, *eleAux;
    if(!list || !elem){
        fprintf(stderr, "list_insertLast: invalid arguments.\n");
        list_destroy(list);
        return NULL;
    }
    /* save the first element direction */
    eleFirst=list->element;
    
    /* advance the list till the first element is the last one */
    while(list->element->next){
        list->element=list->element->next;
    }
    /* creation of the element to insert */
    eleAux->data=list->copy_element_function(elem);
    if (!eleAux->data){
        fprintf(stderr,"list_insertLast: error copying element");
        free(eleAux);
        list_destroy(list);
        return NULL;
    }
    eleAux->next=NULL;
    list->element->next=eleAux;
    
    /* first element come back */
    list->element=eleFirst;
    
    return list;
}


List* list_insertInOrder(List* list,const void* pElem){
    
}











