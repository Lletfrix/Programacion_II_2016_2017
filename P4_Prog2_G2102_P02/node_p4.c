#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "types.h"

struct _Node {
    char *name;
    int id;
    int fatherId;
    Color color;
};

Node * node_ini() {
    Node* n;
    n = (Node*) calloc(1, sizeof (Node));
    /* if n is NULL return NULL*/
    if (!n) {
        return NULL;
    }
    n->color = WHITE;
    n->fatherId = 0;
    return n;
}

void node_destroy(Node* n) {
    if (!n) {
        return;
    }
    if (n->name) {
        free(n->name);
    }
    free(n);
}

int node_getId(const Node * n) {
    if (!n) {
        /*if n is null return -1*/
        return -1;
    }
    return n->id;
}

char* node_getName(const Node * n) {
    if (!n) {
        /*if n is null return NULL*/
        return NULL;
    }
    if (!n->name) {
        fprintf(stderr, "node name is NULL\n");
    }
    return n->name;
}

Color node_getColor(const Node*n) {
    if (!n) {
        return WHITE;
    }
    return n->color;
}

int node_getFatherId(Node*n) {
    if (!n) {
        return -1;
    }
    return n->fatherId;
}

Node* node_setId(Node* n, const int id) {
    if (!n) {
        /*if n is null return NULL*/
        return NULL;
    }
    n->id = id;
    return n;
}

Node * node_setName(Node * n, const char* name) {
    if (!n) {
        /*if n is null return NULL*/
        return NULL;
    }
    if (n->name) {
        free(n->name);
    }
    n->name = calloc(strlen(name)+1, sizeof (char));
    strcpy(n->name, name);
    return n;
}

Node* node_setColor(Node* n, const Color color) {
    if (!n) {
        return NULL;
    }
    n->color = color;
    return n;
}

Node* node_setFatherId(Node* n, int fatherId) {
    if (!n) {
        return NULL;
    }
    n->fatherId = fatherId;
    return n;
}

Bool node_equals(const Node * n1, const Node * n2) {
    /* if id and name from n1 is equal to those from n2 return true, if not return false*/
    if ((n1->id == n2->id) && (n1->color == n2->color) && (strcmp(n1->name, n2->name) == 0)) {
        return TRUE;
    }
    return FALSE;
}

int node_cmp(Node* n1, Node* n2){
    int vId, vName;
    if(!n1||!n2){
        fprintf(stderr, "%s\n", "Invalid arguments");
        return 0;
    }
    vId=node_getId(n1)-node_getId(n2);
    if(vId != 0){
        return vId;
    }
    vName=strcmp(node_getName(n1), node_getName(n2));
    return vId + vName;
}

Node* node_copy(const Node * src) {
    Node *temp;
    if (!src) {

        /*if src is null return NULL*/
        return NULL;
    }
    temp = node_ini();

    if (!temp) {
        return NULL;
    }

    temp->id = src->id;
    temp->color = src->color;
    temp->name=(char*)calloc(strlen(src->name)+1, sizeof(char));
    strcpy(temp->name, src->name);

    return temp;
}

int node_print(FILE *pf, const Node * n) {
    int chars;

    if ((!pf) || (!n)) {
        /* if pf or n is NULL, return NULL*/
        return -1;
    }

    chars = fprintf(pf, "[%d, %s]", n->id, n->name);
    return chars;
}
