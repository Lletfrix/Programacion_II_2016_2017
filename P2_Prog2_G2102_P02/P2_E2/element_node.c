#include <stdio.h>
#include <stdlib.h>
#include "element.h"
#include "node.h"

struct _Element {
    Node* info;
};

Element* element_ini() {
    Element* p;
    p = (Element*) malloc(sizeof (Element));

    if (!p) {
        return NULL;
    }
    return p;
}

void element_destroy(Element * e) {
    if ((!e) || (!e->info)) {
        return;
    }
    node_destroy(e->info);
    free(e);
}

Element * element_setInfo(Element * e, void* p) {
    if ((!p) || (!e)) {
        return NULL;
    }
    
    e->info=node_copy((Node*) p);
    return e;
}

void * element_getInfo(Element * e) {
    void* inf;
    if ((!e) || (!e->info)) {
        return NULL;
    }
    if(!(e->info)){
        return NULL;
    }
    inf = (void*) e->info;
    return inf;
}

Element * element_copy(const Element * eOrig) {
    Element* eDest;
    eDest = element_ini();
    if (!eDest || !eOrig || !eOrig->info) {
        return NULL;
    }
    eDest->info=node_copy(eOrig->info);
    if (!eDest->info){
        return NULL;
    }
    return eDest;
}

Bool element_equals(const Element * e1, const Element * e2) {
    if ((!e1) || (!e2) || (!e1->info) || (!e2->info)) {
        return FALSE;
    }
    if (node_equals(e1->info,e2->info)==FALSE){
        return FALSE;
    }
    return TRUE;
}

int element_print(FILE * f, const Element * e) {
    int charsNum;
    if ((!f) || (!e) || (!e->info)) {
        return -1;
    }
    charsNum = node_print(f,e->info);
    return charsNum;
}