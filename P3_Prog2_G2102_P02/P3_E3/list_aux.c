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


