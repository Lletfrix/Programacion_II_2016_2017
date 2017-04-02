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

typedef struct _NodeList {
    void* data;
    struct _NodeList *next;
} NodeList;

struct _List {
    NodeList *node;
    destroy_elementlist_function_type destroy_element_function;
    copy_elementlist_function_type copy_element_function;
    print_elementlist_function_type print_element_function;
    cmp_elementlist_function_type cmp_element_function;
};

NodeList* element_ini() {
    NodeList* n;
    n = (NodeList*) calloc(1, sizeof (NodeList));
    if (!n) {
        fprintf(stderr, "element_ini: error allocating memory.\n");
        return NULL;
    }
    return n;
}

List* list_ini(destroy_elementlist_function_type f1, copy_elementlist_function_type f2,
        print_elementlist_function_type f3, cmp_elementlist_function_type f4) {
    List* l = NULL;
    l = (List*) calloc(1, sizeof (List));
    if (!l) {
        fprintf(stderr, "list_ini: error allocating memory.\n");
        return NULL;
    }

    l->destroy_element_function = f1;
    l->copy_element_function = f2;
    l->print_element_function = f3;
    l->cmp_element_function = f4;

    return l;
}

void list_destroy(List* list) {
    NodeList* aux;
    if (!list) {
        fprintf(stderr, "list_free: list pointing NULL.\n");
        return;
    }
    if (list->node) {
        while (list->node->next) {
            aux = list->node;
            list->node = list->node->next;
            list->destroy_element_function(aux->data);
            free(aux);
        }
        list->destroy_element_function(list->node->data);
        free(list->node);
    }
    free(list);
}

List* list_insertFirst(List* list, const void *elem) {
    NodeList *nodeAux;
    if (!list || !elem) {
        fprintf(stderr, "list_insertFirst: invalid arguments.\n");
        list_destroy(list);
        return NULL;
    }

    nodeAux = element_ini();
    if (!nodeAux) {
        fprintf(stderr, "list_insertFirst: error allocating memory\n");
        list_destroy(list);
        return NULL;
    }
    nodeAux->next = list->node;
    nodeAux->data = list->copy_element_function(elem);
    if (!nodeAux->data) {
        fprintf(stderr, "list_insertFirst: error copying node\n");
        free(nodeAux);
        list_destroy(list);
        return NULL;
    }
    list->node = nodeAux;

    return list;
}

List* list_insertLast(List* list, const void *elem) {
    NodeList *nodeAdv, *nodeAux;
    if (!list || !elem) {
        fprintf(stderr, "list_insertLast: invalid arguments.\n");
        list_destroy(list);
        return NULL;
    }

    nodeAdv = list->node;

    if (!nodeAdv) {
        list_insertFirst(list, elem);
        return list;
    }
    /* advance the list till the first node is the last one */
    while (nodeAdv->next) {
        nodeAdv = nodeAdv->next;
    }

    /* creation of the node to insert */
    nodeAux = element_ini();
    if (!nodeAux) {
        fprintf(stderr, "list_insertLast: error allocating memory.\n");
        list_destroy(list);
        return NULL;
    }
    nodeAux->data = list->copy_element_function(elem);
    if (!nodeAux->data) {
        fprintf(stderr, "list_insertLast: error copying node\n");
        free(nodeAux);
        list_destroy(list);
        return NULL;
    }
    nodeAux->next = NULL;
    nodeAdv->next = nodeAux;


    return list;
}

List* list_insertInOrder(List* list, const void* pElem) {
    NodeList *node1, *node2, *nodeAux;
    node2 = list->node;
    if(!list){
        fprintf(stderr,"list_insertInOrder: invalid arguments\n");
        list_destroy(list);
        return NULL;
    }
    if (!node2) {
        list=list_insertFirst(list, pElem);
        if(!list){
            fprintf (stderr, "list_insertInOrder: error inserting node\n");
            list_destroy(list);
            return NULL;
        }
        return list;
    }
    if (list->cmp_element_function(node2->data, pElem) > 0) {
        list=list_insertFirst(list, pElem);
        if(!list){
            fprintf (stderr, "list_insertInOrder: error inserting node\n");
            list_destroy(list);
            return NULL;
        }
        return list;
    }
    node1 = list->node->next;
    while (1) {
        if (!node1) {
            nodeAux = element_ini();
            if(!nodeAux){
                fprintf(stderr, "list_insertInOrder: error creating node\n");
                list_destroy(list);
                return NULL;
            }
            nodeAux->data = list->copy_element_function(pElem);
            if(!nodeAux->data){
                fprintf(stderr, "list_insertInOrder: error copying element\n");
                free(nodeAux);
                list_destroy(list);
                return NULL;
            }
            
            nodeAux->next = node1;
            node2->next = nodeAux;
            return list;
        }
        if (list->cmp_element_function(node1->data, pElem) > 0) {
            nodeAux = element_ini();
            if(!nodeAux){
                fprintf(stderr, "list_insertInOrder: error creating node\n");
                list_destroy(list);
                return NULL;
            }
            nodeAux->data = list->copy_element_function(pElem);
            if(!nodeAux->data){
                fprintf(stderr, "list_insertInOrder: error copying element\n");
                free(nodeAux);
                list_destroy(list);
                return NULL;
            }
            nodeAux->next = node1;
            node2->next = nodeAux;
            return list;
        }
        node2 = node1;
        node1 = node1->next;
    }
}

void * list_extractFirst(List* list) {
    NodeList* nodeAux;
    void* returnElement;
    if (!list) {
        fprintf(stderr, "list_extractFirst: invalid arguments\n");
        return NULL;
    }
    nodeAux = list->node;
    list->node = list->node->next;
    returnElement = list->copy_element_function(nodeAux->data);
    if(!returnElement){
        fprintf(stderr, "list_extractFirst: error copying element\n");
    }
    list->destroy_element_function(nodeAux->data);
    free(nodeAux);
    return returnElement;
}

void * list_extractLast(List* list) {
    void * eleAux;
    NodeList * nodeFirst;
    if (!list) {
        fprintf(stderr, "list_extractLast: invalid arguments.\n");
        return NULL;
    }
    nodeFirst = list -> node;
    while (list->node->next->next) {
        list->node = list->node->next;
    }
    eleAux = list->copy_element_function(list->node->next->data);
    if (!eleAux) {
        fprintf(stderr, "list_extractLast: error copying element.\n");
        return NULL;
    }
    list->node = nodeFirst;
    return eleAux;
}

Bool list_isEmpty(const List* list) {
    if (!list) {
        fprintf(stderr, "list_isEmpty: error, list is pointing NULL.");
        return TRUE;
    }
    if (!list->node) {
        return TRUE;
    }
    return FALSE;
}

/* Devuelve el elemento i-ésimo almacenado en la lista. En caso de error, devuelve NULL. */
const void* list_get(const List* list, int i){
    int count;
    void *eleAux;
    NodeList *nodeAux;
    if (!list){
        fprintf(stderr, "list_get: invalid arguments.\n");
        return NULL;
    }
    nodeAux = list->node;
    for (count = 1; count <= i; count++){
        nodeAux = nodeAux->next;
    }
    eleAux = list->copy_element_function(nodeAux->data);
    if (!eleAux){
        fprintf(stderr, "list_get: error copying element.\n");
        return NULL;
    }
    return eleAux;
}

/* Devuelve el tamaño de una lista. */
int list_size(const List* list) {
    int aux = 1;
    NodeList *nodeAux;
    if (!list) {
        fprintf(stderr, "list_size: invalid arguments.\n");
        return -1;
    }
    if (list->node == NULL) {
        return 0;
    }
    nodeAux = list->node;
    while (nodeAux->next) {
        nodeAux = nodeAux->next;
        aux++;
    }
    return aux;
}

int list_print(FILE *fd, const List* list) {
    int chars = 0;
    NodeList* nodeFirst;
    if (!fd || !list) {
        fprintf(stderr, "list_print: invalid arguments\n");
        return -1;
    }
    nodeFirst = list->node;
    while (nodeFirst->next) {
        chars = list->print_element_function(fd, nodeFirst->data);
        chars = fprintf(fd, "\n");
        nodeFirst = nodeFirst->next;
    }
    chars = list->print_element_function(fd, nodeFirst->data);
    chars = fprintf(fd, "\n");
    return chars;
}
