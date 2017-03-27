#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack_element.h"
#define MAX 255

Graph * read_graph_from_file(char * filename) {
    FILE * in;
    Graph * g;
    Node * n;
    char buff[MAX], name[MAX];
    int i, nnodes, id1, id2;

    g = graph_ini();
    if (g == NULL) {
        return NULL;
    }
    in = (FILE*) fopen(filename, "r");
    if (in == NULL) {
        graph_destroy(g);
        return NULL;
    }
    /* Format: nnodes \n node1id node1name ... nodenid nodenname connection1a connection1b ... */
    fgets(buff, MAX, in);
    sscanf(buff, "%d", &nnodes);
    /* read nodes line by line */
    for (i = 0; i < nnodes; i++) {
        fgets(buff, MAX, in);
        sscanf(buff, "%d %s", &id1, name);
        /* create node */
        n = node_ini();
        if (node_setId(n, id1) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        if (node_setName(n, name) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        /* add node to graph */
        if (graph_addNode(g, n) == NULL) {
            fclose(in);
            node_destroy(n);
            graph_destroy(g);
            return NULL;
        }
        /* destroy node */
        node_destroy(n);
    }
    /* read connections */
    while (!feof(in)) {
        fgets(buff, MAX, in);
        sscanf(buff, "%d %d", &id1, &id2);
        if (graph_addEdge(g, id1, id2) == NULL) {
            fclose(in);
            graph_destroy(g);
            return NULL;
        }
    }

    fclose(in);

    return g;
}
/*
 * 
 */
int main(int argc, char** argv) {
    Graph* g;
    Stack* s;
    Element* ele;
    int i, j, index, *g_idList, *n_idFrom, *n_idTo;

    s = stack_ini();
    if (!s) {
        return EXIT_FAILURE;
    }
    g = read_graph_from_file(argv[1]);
    if (!g) {
        goto Err_handl1;
    }
    g_idList = graph_getNodeIds(g);
    if (!g_idList) {
        goto Err_handl2;
    }

    for (i = 0; i < graph_getNnodes(g); i++) {

        index = g_idList[i];
        n_idTo = graph_getConnectionsTo(g, index);
        n_idFrom = graph_getConnectionsFrom(g, index);
        for (j = 0; j < graph_getNumberOfConnectionsTo(g, index); j++) {
            ele = element_ini();
            if (!ele) {
                goto Err_handl4;
            }
            ele = element_setInfo(ele, (void*) graph_getNode(g, n_idTo[j]));
            s=stack_push(s, ele);
            if (!s) {
                goto Err_handl5;
            }
            element_destroy(ele);
        }

        for (j = 0; j < graph_getNumberOfConnectionsFrom(g, index); j++) {
            ele = element_ini();
            if (!ele) {
                goto Err_handl4;
            }
            ele = element_setInfo(ele, (void*) graph_getNode(g, n_idFrom[j]));
            s=stack_push(s, ele);
            if (!s) {
                goto Err_handl5;
            }
            element_destroy(ele);
        }
        free(n_idTo);
        free(n_idFrom);
    }

    free(g_idList);
    printf("> %s %s \n", argv[0], argv[1]);
    stack_print(stdout, s);
    stack_destroy(s);
    graph_destroy(g);

    return (EXIT_SUCCESS);
  
    Err_handl5:
    element_destroy(ele);
    Err_handl4:
    free(n_idFrom);
    free(n_idTo);
    free(g_idList);
    Err_handl2:
    graph_destroy(g);
    Err_handl1:
    stack_destroy(s);
  
    return (EXIT_FAILURE);

}

