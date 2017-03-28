/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p3_e2.c
 * Author: rafael
 *
 * Created on 28 de marzo de 2017, 12:04
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"

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

int main(int argc, char** argv) {
    int  fromId, toId;
    Graph* g;
    Bool pth;
    Queue* qPath;
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
    
    
    
    qPath = graph_path(g, fromId, toId);
    
    if (qPath) {
        fprintf(fp, "Es posible encontrar un camino\n");
    } else {
        fprintf(fp, "No es posible encontrar un camino\n");
        return (EXIT_SUCCESS);
    }
    
    queue_print(fp, qPath);

    queue_destroy(qPath);
    graph_destroy(g);
    return (EXIT_SUCCESS);
}

