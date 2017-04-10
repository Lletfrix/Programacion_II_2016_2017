/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p3_e4.c
 * Author: rafael, sergio
 *
 * Created on 28 de marzo de 2017, 12:04
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "functions.h"

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

Queue* graph_path (Graph*g, int fromId, int toId ){
    int i, *idList, *idAdj, nConnec;
    Queue* qAux, *qPath;
    Node* nodeU, *nodeV, *nodeAux;
    
    if(!g || fromId==-1 || toId==-1){
        return NULL;
    }
    
    idList=graph_getNodeIds(g);
    if(!idList){
        return NULL;
    }
    for(i=0;i<graph_getNnodes(g);i++){
        nodeU=graph_getNode(g,idList[i]);
        node_setColor(nodeU,WHITE);
        node_setFatherId(nodeU,0);
        node_destroy(nodeU);
    }
    free(idList);
    
    nodeU=graph_getNode(g, fromId);
    node_setColor(nodeU,GREY);
    qAux=queue_ini(&destroy_node_function,&copy_node_function,&print_node_function);
    
    if(!qAux){
        return NULL;
    }
    
    qAux=queue_insert(qAux,nodeU);
    if(!qAux){
        fprintf(stderr, "graph_path: error adding first node to queue.\n");
        return NULL;
    }
    
    node_destroy(nodeU);
    
    while(!queue_isEmpty(qAux)){
        nodeU=queue_extract(qAux);
        idAdj=graph_getConnectionsFrom(g, node_getId(nodeU));
        if(!idAdj){
            queue_destroy(qAux);
            return NULL;
        }
        nConnec=graph_getNumberOfConnectionsFrom(g, node_getId(nodeU));
        for(i=0; i<nConnec; i++){
            nodeV=graph_getNode(g, idAdj[i]);
            if(node_getColor(nodeV)==WHITE){
                node_setColor(nodeV,GREY);
                node_setFatherId(nodeV, node_getId(nodeU));
                qAux=queue_insert(qAux, nodeV);
                if(!qAux){
                    free(idAdj);
                    return NULL;
                }
            }
        }
        node_setColor(nodeU,BLACK);
        nodeAux=graph_getNode(g, node_getId(nodeU));
        node_setColor(nodeAux, BLACK);
        node_destroy(nodeAux);
        free(idAdj);
        node_destroy(nodeU);
    }
    
    queue_destroy(qAux);
    nodeAux=graph_getNode(g, toId);
    if (node_getColor(nodeAux)!=BLACK){
        node_destroy(nodeAux);
        return NULL;
    }
    node_destroy(nodeAux);
    
    /* Backtracking */
    qPath=queue_ini(&destroy_node_function,&copy_node_function,&print_node_function);
    if(!qPath){
        fprintf(stderr, "graph_path: error allocating qPath memory.\n");
        return NULL;
    }
    
    nodeU=graph_getNode(g, toId);
    qPath=queue_insert(qPath, nodeU);
    
    if(!qPath){
        return NULL;
    }
    
    while(node_getFatherId(nodeU)!=0){
        nodeU=graph_getNode(g, node_getFatherId(nodeU));
        qPath = queue_insert(qPath, nodeU);
        if (!qPath) {
            return NULL;
        }
    }
    
    return qPath;
}

int main(int argc, char** argv) {
    int  fromId, toId;
    Graph* g;
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
        graph_destroy(g);
        return (EXIT_SUCCESS);
    }
    
    queue_print(fp, qPath);
    queue_destroy(qPath);
    graph_destroy(g);
    return (EXIT_SUCCESS);
}

