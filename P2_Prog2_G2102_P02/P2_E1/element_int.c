#include <stdio.h>
#include <stdlib.h>
#include "element.h"

struct _Element {
    int* info;
};

Element* element_ini() {
    Element* p;
    p = (Element*) malloc(sizeof (Element));

    p->info = (int*) malloc(sizeof (Element));

    if (!(p->info)) {
        return NULL;
    }

    if (!p) {
        return NULL;
    }
    return p;
}

void element_destroy(Element * e) {
    if (!e) {
        return;
    }
    free(e->info);
    free(e);
}

Element * element_setInfo(Element * e, void* p) {
    if ((!p) || (!e)) {
        return NULL;
    }
    *(e->info) = *(int*) p;
    return e;
}

void * element_getInfo(Element * e) {
    void* inf;
    if (!e) {
        return NULL;
    }
    inf = (void*) e->info;
    return inf;
}

Element * element_copy(const Element * eOrig) {
    Element* eDest;
    eDest = element_ini();
    if (!eDest) {
        return NULL;
    }
    *(eDest->info) = *(eOrig->info);
    return eDest;
}

Bool element_equals(const Element * e1, const Element * e2) {
    if ((!e1) || (!e2)) {
        return FALSE;
    }
    if (*(e1->info) != *(e2->info)) {
        return FALSE;
    }
    return TRUE;
}

int element_print(FILE * f, const Element * e) {
    int charsNum;
    if ((!f) || (!e)) {
        return -1;
    }
    charsNum = fprintf(f, "[%d]", *(e->info));
    return charsNum;
}