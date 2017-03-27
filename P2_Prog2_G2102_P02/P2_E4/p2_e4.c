/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p2_e4.c
 * Author: rafael
 *
 * Created on 14 de marzo de 2017, 12:35
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


#define MAX 255

/*
 * 
 */
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
    Stack* s_id, *s_node;
    void* item;
    int i, j, index, *g_idList, *n_idFrom, *n_idTo;
    
    if(argc<2){
        fprintf(stderr, "Invalid number of arguments.\n");
        return EXIT_FAILURE;
    }
    
    
    s_id = stack_ini(&destroy_intp_function, &copy_intp_function, &print_intp_function);
    
    if(!s_id){
        return EXIT_FAILURE;
    }
    
    s_node = stack_ini(&destroy_node_function, &copy_node_function, &print_node_function);
    
    if (!s_node){
        stack_destroy(s_id);
        return EXIT_FAILURE;
    }
    
    g = read_graph_from_file(argv[1]);
    
    if (!g){
        stack_destroy(s_id);
        stack_destroy(s_node);
        return EXIT_FAILURE;
    }
    
    g_idList = graph_getNodeIds(g);
    
    if(!g_idList){
        stack_destroy(s_id);
        stack_destroy(s_node);
        graph_destroy(g);
        return EXIT_FAILURE;
    }

    for (i = 0; i < graph_getNnodes(g); i++) {

        index = g_idList[i];
        n_idTo = graph_getConnectionsTo(g, index);
        n_idFrom = graph_getConnectionsFrom(g, index);

        for (j = 0; j < graph_getNumberOfConnectionsTo(g, index); j++) {
            item = (void *) &n_idTo[j];
            s_id = stack_push(s_id, item);
            item = (void*) graph_getNode(g, n_idTo[j]);
            s_node = stack_push(s_node, item);
        }

        for (j = 0; j < graph_getNumberOfConnectionsFrom(g, index); j++) {
            item = (void *) &n_idFrom[j];
            s_id = stack_push(s_id, item);
            item = (void*) graph_getNode(g, n_idFrom[j]);
            s_node = stack_push(s_node, item);
        }
        free(n_idTo);
        free(n_idFrom);
    }

    free(g_idList);
    fprintf(stdout, "> %s %s \n", argv[0], argv[1]);
    fprintf(stdout, "Pila de enteros:\n");
    stack_print(stdout, s_id);
    fprintf(stdout, "Pila de nodos:\n");
    stack_print(stdout, s_node);
    stack_destroy(s_id);
    stack_destroy(s_node);
    graph_destroy(g);

    return (EXIT_SUCCESS);
}