#include <stdio.h>
#include <stdlib.h>
#include "stack_element.h"
#include "graph.h"

#define MAX 255
#define ROWS 2
#define NODE_ID 0
#define FATHER_ID 1

Graph* graph_discoverFromNode(Graph* g, Node* n) {
    Stack* s;
    Element *ele, *v, *w;
    int *list, nConnec, i;
    if (!g || !n) {
        return NULL;
    }
    ele = element_ini();
    if (!ele) {
        return NULL;
    }
    s = stack_ini();
    if (!s) {
        goto Error_hand1;
    }

    node_setColor(graph_getNode(g, node_getId(n)), GREY);
    ele = element_setInfo(ele, (void *) n);
    stack_push(s, ele);

    element_destroy(ele);

    while (!(stack_isEmpty(s))) {

        v = stack_pop(s);

        if (node_getColor((Node*) element_getInfo(v)) == GREY) {

            list = graph_getConnectionsFrom(g, node_getId((Node*) element_getInfo(v)));

            nConnec = graph_getNumberOfConnectionsFrom(g, node_getId((Node*) element_getInfo(v)));

            node_setColor(graph_getNode(g, node_getId((Node*) element_getInfo(v))), BLACK);

            for (i = 0; i < nConnec; i++) {

                if (node_getColor(graph_getNode(g, list[i])) != WHITE) {
                    continue;
                }
                node_setColor(graph_getNode(g, list[i]), GREY);

                w = element_ini();

                if (!w) {
                    goto Error_hand2;
                }

                w = element_setInfo(w, (void*) graph_getNode(g, list[i]));
                stack_push(s, w);
                element_destroy(w);
            }

            free(list);


        }
        element_destroy(v);
    }

    stack_destroy(s);

    return g;

    /* error handling */
Error_hand2:

    free(list);
    element_destroy(v);
    stack_destroy(s);

Error_hand1:

    element_destroy(ele);

    return NULL;
}

Bool graph_pathExists(Graph *g, int fromId, int toId) {
    if (!g) {
        return FALSE;
    }
    g = graph_discoverFromNode(g, graph_getNode(g, fromId));
    if (!g) {
        printf("Error discovering nodes\n");
        return FALSE;
    }
    if (node_getColor(graph_getNode(g, toId)) == BLACK) {
        return TRUE;
    }
    return FALSE;
}

int find_fatherIndex(int **list, int id, int maxList) {
    int i;

    if ((!list) || maxList < 0) {
        return -1;
    }
    for (i = 0; i < maxList; i++) {
        if (list[NODE_ID][i] == id) {
            return i;
        }
    }
    return -1;
}

Stack* graph_path(Graph* g, int fromId, int toId) {
    int i, numNodes, column = 0, nConnec, *lNodeIds, **fatherIds, *listAdj;
    Element *eleU, *eleV;
    Stack *stcAux, *stcPath;
    Node* nodeU, *nodeV;

    if (!g) {
        return NULL;
    }

    if (!graph_pathExists(g, fromId, toId)) {
        return NULL;
    }

    lNodeIds = graph_getNodeIds(g);
    if (!lNodeIds) {
        return NULL;
    }
    numNodes = graph_getNnodes(g);

    for (i = 0; i < numNodes; i++) {
        node_setColor(graph_getNode(g, lNodeIds[i]), WHITE);
    }
    free(lNodeIds);

    fatherIds = (int**) malloc(ROWS * sizeof (int*));
    if (!fatherIds) {
        return NULL;
    }
    for (i = 0; i < ROWS; i++) {
        fatherIds[i] = (int*) malloc(numNodes * sizeof (int));
        if (!fatherIds[i]) {
            for (i = i - 1; i >= 0; i--) {
                free(fatherIds[i]);
            }
            free(fatherIds);
            return NULL;

        }
    }


    eleU = element_ini();
    if (!eleU) {
        for (i = 0; i < ROWS; i++) {
            free(fatherIds[i]);
        }
        free(fatherIds);
        return NULL;
    }

    nodeU = graph_getNode(g, fromId);
    node_setColor(nodeU, GREY);

    eleU = element_setInfo(eleU, nodeU);

    stcAux = stack_ini();
    if (!stcAux) {
        for (i = 0; i < ROWS; i++) {
            free(fatherIds[i]);
        }
        free(fatherIds);
        element_destroy(eleU);
        return NULL;
    }
    stcPath = stack_ini();
    if (!stcPath) {
        for (i = 0; i < ROWS; i++) {
            free(fatherIds[i]);
        }
        free(fatherIds);
        element_destroy(eleU);
        stack_destroy(stcAux);
        return NULL;
    }
    stcAux = stack_push(stcAux, eleU);
    element_destroy(eleU);

    fatherIds[NODE_ID][column] = node_getId(nodeU);
    fatherIds[FATHER_ID][column] = -2;
    column++;

    while (node_getColor(element_getInfo(stack_top(stcAux))) == GREY) {
        eleU = stack_pop(stcAux);
        nodeU = element_getInfo(eleU);
        listAdj = graph_getConnectionsFrom(g, node_getId(nodeU));
        nConnec = graph_getNumberOfConnectionsFrom(g, node_getId(nodeU));

        for (i = 0; i < nConnec; i++) {
            nodeV = graph_getNode(g, listAdj[i]);
            if (node_getColor(nodeV) == WHITE) {

                node_setColor(nodeV, GREY);

                eleV = element_ini();
                if (!eleV) {
                    for (i = 0; i < ROWS; i++) {
                        free(fatherIds[i]);
                    }
                    free(fatherIds);
                    free(listAdj);
                    element_destroy(eleU);
                    stack_destroy(stcAux);
                    stack_destroy(stcPath);
                    return NULL;
                }
                eleV = element_setInfo(eleV, nodeV);
                stcAux = stack_push(stcAux, eleV);
                element_destroy(eleV);

                fatherIds[NODE_ID][column] = node_getId(nodeV);
                fatherIds[FATHER_ID][column] = node_getId(nodeU);
                column++;

                if (node_getId(nodeV) == toId) {

                    column = find_fatherIndex(fatherIds, toId, numNodes);

                    while (fatherIds[FATHER_ID][column] != -2) {
                        eleV = element_ini();
                        if (!eleV) {
                            for (i = 0; i < ROWS; i++) {
                                free(fatherIds[i]);
                            }
                            free(fatherIds);
                            free(listAdj);
                            element_destroy(eleU);
                            stack_destroy(stcAux);
                            stack_destroy(stcPath);
                            return NULL;
                        }
                        nodeV = graph_getNode(g, fatherIds[NODE_ID][column]);
                        eleV = element_setInfo(eleV, nodeV);
                        stcPath = stack_push(stcPath, eleV);
                        element_destroy(eleV);

                        column = find_fatherIndex(fatherIds, fatherIds[FATHER_ID][column], numNodes);
                    }

                    eleV = element_ini();
                    if (!eleV) {
                        for (i = 0; i < ROWS; i++) {
                            free(fatherIds[i]);
                        }
                        free(fatherIds);
                        free(listAdj);
                        element_destroy(eleU);
                        stack_destroy(stcAux);
                        stack_destroy(stcPath);
                        return NULL;
                    }
                    nodeV = graph_getNode(g, fatherIds[NODE_ID][column]);
                    eleV = element_setInfo(eleV, nodeV);
                    stcPath = stack_push(stcPath, eleV);
                    element_destroy(eleV);

                    for (i = 0; i < ROWS; i++) {
                        free(fatherIds[i]);
                    }

                    element_destroy(eleU);
                    free(listAdj);
                    free(fatherIds);
                    stack_destroy(stcAux);
                    return stcPath;
                }

            }

        }
        free(listAdj);
        element_destroy(eleU);
    }

    column = find_fatherIndex(fatherIds, toId, numNodes);

    while (fatherIds[FATHER_ID][column] != -2) {
        eleU = element_ini();
        nodeU = graph_getNode(g, fatherIds[NODE_ID][column]);
        eleU = element_setInfo(eleU, nodeU);
        stcPath = stack_push(stcPath, eleU);
        element_destroy(eleU);

        column = find_fatherIndex(fatherIds, fatherIds[FATHER_ID][column], numNodes);
    }

    eleU = element_ini();
    if (!eleU) {
        for (i = 0; i < ROWS; i++) {
            free(fatherIds[i]);
        }
        free(fatherIds);
        stack_destroy(stcAux);
        stack_destroy(stcPath);
        return NULL;
    }
    nodeU = graph_getNode(g, fatherIds[NODE_ID][column]);
    eleU = element_setInfo(eleU, nodeU);
    stcPath = stack_push(stcPath, eleU);
    element_destroy(eleU);


    for (i = 0; i < ROWS; i++) {
        free(fatherIds[i]);
    }

    free(fatherIds);
    stack_destroy(stcAux);
    return stcPath;
}

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

int main(int argc, char** argv) {
    int fromId, toId;
    Graph* g;
    Bool pth;
    Stack* sPath;
    FILE* fp;
    fp = stdout;
    if (argc < 4) {
        printf("Wrong number of arguments\n");
        return EXIT_FAILURE;
    }

    fromId = atoi(argv[2]);
    toId = atoi(argv[3]);
    g = read_graph_from_file(argv[1]);
    if (!g) {
        printf("Error reading graph from file %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    pth = graph_pathExists(g, fromId, toId);

    if (pth) {
        printf("Es posible encontrar un camino\n");
    } else {
        printf("No es posible encontrar un camino\n");
    }

    sPath = graph_path(g, fromId, toId);
    stack_print(fp, sPath);

    stack_destroy(sPath);
    graph_destroy(g);
    return EXIT_SUCCESS;
}