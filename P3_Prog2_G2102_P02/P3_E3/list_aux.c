#include "list.h"

typedef struct _ElementList {
    void* data;
    struct _ElementList *next;
} NodeList;

struct _List {
    NodeList *node;
    destroy_elementlist_function_type destroy_element_function;
    copy_elementlist_function_type copy_element_function;
    print_elementlist_function_type print_element_function;
    cmp_elementlist_function_type cmp_element_function;
};

NodeList* element_ini(){
    NodeList* node;
    node=(NodeList*)calloc(1,sizeof(NodeList));
    if(!node){
        fprintf(stderr, "element_ini: error allocating memory.\n");
        return NULL;
    }
    return node;
}

/* Extrae del final de la lista realizando una copia del elemento almacenado en dicho nodo. */
void * list_extractLast(List* list){
    void * nodeAux;
    NodeList * nodeFirst;
    if (!list) {
        fprintf(stderr, "list_extractLast: invalid arguments.\n");
        return NULL;
    }
    nodeFirst = list -> node;
    while(list->node->next->next){
        list->node=list->node->next;
    }
    nodeAux = list->copy_element_function(list->node->next->data);
    if (!nodeAux){
        fprintf(stderr, "list_extractLast: error copying.\n");
        return NULL;
    }
    list->node = nodeFirst;
    return nodeAux;
}
/* Comprueba si una lista está vacía o no. */
Bool list_isEmpty(const List* list){
    if (!list || (list->node->data == NULL && list->node->next == NULL)){
        return TRUE;
    }
    return FALSE;
}
/* Devuelve el elemento i-ésimo almacenado en la lista. En caso de error, devuelve NULL. */
const void* list_get(const List* list, int i){

}
/* Devuelve el tamaño de una lista. */
int list_size(const List* list){
    int aux = 0;
    NodeList *nodeAux;
    if (!list){
        fprintf(stderr, "list_size: invalid arguments.\n");
        return -1;
    }
    if (list->node == NULL){
        return 0;
    }
    nodeAux = list->node;
    while(list->node->next){
        list->node=list->node->next;
        aux++;
    }
    list->node = nodeAux;
    return aux;
}
/* Imprime una lista devolviendo el número de caracteres escritos. */
int list_print(FILE *fd, const List* list);
