#include "graph.h"
#include <stdlib.h>

#define NOT_BELONG -1

struct _Graph {
List * nodes;
/* Lista de nodos */
List* out_connections;
/*
Lista de 
NodeConnections
*/
List* in_connections;
/* Lista de 
NodeConnections
*/
int num_nodes;
int num_edges;
};
typedef struct _NodeConnections {
int nodeid;
List* connections;
/*  Lista de enteros */
} NodeConnections;

Graph * graph_ini() {
    Graph* g;
    int i, j;
    g = (Graph*) malloc(sizeof (Graph));

    if (!g) { 
        /*if malloc fails return NULL*/
        return NULL;
    }

    g->num_nodes = 0; 
    /* zero nodes and edges at the beginning*/
    g->num_edges = 0;
    return g;
}



int graph_getNnodes(const Graph * g) {
    if (!g) { 
        /* if g point to NULL, return -1*/
        return -1;
    }
    /* return the current number of nodes */
    return g->num_nodes; 
}



int graph_getNedges(const Graph * g) {
    if (!g) { 
        /* if g point to NULL, return -1 */
        return -1;
    }
    /* return current number of edges */
    return g->num_edges; 
}

/* next function returns the index that the node of id <nId1> has.
 * in case an error ocurr, it will return -1, so this function will help with
 * nodes which doesn't belong to the graph as well */





Graph * graph_addEdge(Graph * g, const int nId1, const int nId2) {
    int index1, index2;
    /* error detection */
    if (!g) { 
        return NULL;
    }

    index1 = find_node_index(g, nId1); 
    index2 = find_node_index(g, nId2); 

    if ((index1 == NOT_BELONG) || (index2 == NOT_BELONG)) {
        /* if any of the two nodes doesn't belong to the graph,
         return NULL*/
        return NULL; 
    }

    if (g->adjacency[index1][index2] != 1) { 
        
        g->adjacency[index1][index2] = 1;
        g->num_edges++;
        /*if nodes aren't connected:
         write <1> in the matrix so they are connected and
         edge number increases by 1*/
    }
    return g;
}



Bool graph_areConnected(const Graph * g, const int nId1, const int nId2) {
    int index1, index2;

    index1 = find_node_index(g, nId1); 
    index2 = find_node_index(g, nId2);

    if (!g) { 
        /* error detection */
        return FALSE;
    }

    if ((index1 == NOT_BELONG) || (index2 == NOT_BELONG)) { 
        /*if nodes don't belong to the graph, return FALSE*/
        return FALSE;
    }

    if (g->adjacency[index1][index2] == 0) { 
        /* If nodes aren't connected, return FALSE*/
        return FALSE;
    }
       /* else return TRUE */
    return TRUE; 
}

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId) {
    int connections, toId, i, index;
    if (!g) { 
        /* error detection */
        return -1;
    }
    index = find_node_index(g, fromId);
    if (index == NOT_BELONG) { 
        /* if node does not belong to the graph, return -1 */
        return -1;
    }
    for (i = 0, connections = 0; i < g->num_nodes; i++) {
        
        /* changes destiny node in each iteration */
        toId = node_getId(g->nodes[i]); 

        if (graph_areConnected(g, fromId, toId) == TRUE) { 
            /* if they are conected sum 1 to the number of connections from node*/
            connections++;
        }
    }
    return connections;
}

int* graph_getConnectionsFrom(const Graph * g, const int fromId) {
    int *temp, connections, toId, i, j;
    if (!g) { 
        /* error detection */
        return NULL;
    }

    connections = graph_getNumberOfConnectionsFrom(g, fromId);
    if (connections == -1) { 
        /* if node is not connected, return NULL */
        return NULL;
    }

    temp = (int*) malloc(connections * (sizeof (int)));
    if (!temp) {
        /* if malloc fails, return NULL */
        return NULL; 
    }

    for (i = 0, j = 0; i < g->num_nodes; i++) {
        toId = node_getId(g->nodes[i]); 
        /* change destiny node in each iteration */
        if (graph_areConnected(g, fromId, toId) == TRUE) { 
            temp[j] = toId; 
            j++; 
            /* if they are connected, it writes the id in the array and
             array index increases*/
        }
    }
    return temp;
}

/* next two functions are analogous to the two previous ones respectively. 
 we just change source node with each iteration instead of changing destiny
 node.*/

int graph_getNumberOfConnectionsTo(const Graph * g, const int toId) {
    int connections, fromId, i, index;

    if (!g) {
        return -1;
    }

    index = find_node_index(g, toId);

    if (index == NOT_BELONG) {
        return -1;
    }

    for (i = 0, connections = 0; i < g->num_nodes; i++) {

        fromId = node_getId(g->nodes[i]);

        if (graph_areConnected(g, fromId, toId) == TRUE) {
            connections++;
        }
    }
    return connections;
}

int* graph_getConnectionsTo(const Graph * g, const int toId) {
    int *temp, connections, fromId, i, j;
    if (!g) {
        return NULL;
    }

    connections = graph_getNumberOfConnectionsTo(g, toId);
    if (connections == -1) {
        return NULL;
    }

    temp = (int*) malloc(connections * (sizeof (int)));
    if (!temp) {
        return NULL;
    }

    for (i = 0, j = 0; i < g->num_nodes; i++) {
        fromId = node_getId(g->nodes[i]);
        if (graph_areConnected(g, fromId, toId) == TRUE) {
            temp[j] = fromId;
            j++;
        }
    }

    if (j == 0) {
        free(temp);
        return NULL;
    }

    return temp;
}

int graph_print(FILE *pf, const Graph * g) {
    int nodeNumber, edgeNumber, i, j, chars = 0;
    if ((!pf) || (!g)) {
        return -1;
    }
    nodeNumber = g->num_nodes;
    edgeNumber = g->num_edges;
    /* prints number of nodes and number of edges */
    chars += fprintf(pf, "N=%d, E=%d :\n", nodeNumber, edgeNumber); 

    for (i = 0; i < nodeNumber; i++) {
        /* prints node 'i'*/
        chars += node_print(pf, g->nodes[i]); 
        chars += fprintf(pf, "->");

        for (j = 0; j < nodeNumber; j++) { 
            /* prints the node's matrix adjacency row */
            chars += fprintf(pf, " %d ", g->adjacency[i][j]);
        }

        chars += fprintf(pf, "\n");
    }
    /* prints chars, which is the value of all characters that have been printed */
    return chars; 
}