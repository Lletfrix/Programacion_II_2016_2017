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

/* Extrae del final de la lista realizando una copia del elemento almacenado en dicho nodo. */
void * list_extractLast(List* list){
    void * eleAux;
    ElementList * eleFirst;
    if (!list) {
        fprintf(stderr, "list_extractLast: invalid arguments.\n");
        return NULL;
    }
    eleFirst = list -> element; 
    while(list->element->next->next){
        list->element=list->element->next;
    }
    eleAux = list->copy_element_function(list->element->next->data);
    if (!eleAux){
        fprintf(stderr, "list_extractLast: error copying.\n");
        return NULL;
    }
    list->element = eleFirst;
    return eleAux;
}
/* Comprueba si una lista está vacía o no. */
Bool list_isEmpty(const List* list){
    if (!list || (list->element->data == NULL && list->element->next == NULL)){
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
    ElementList *eleAux;
    if (!list){
        fprintf(stderr, "list_size: invalid arguments.\n");
        return -1;
    }
    if (list->element == NULL){
        return 0;
    }
    eleAux = list->element;
    while(list->element->next){
        list->element=list->element->next;
        aux++;
    }
    list->element = eleAux;
    return aux;
}
/* Imprime una lista devolviendo el número de caracteres escritos. */
int list_print(FILE *fd, const List* list);

