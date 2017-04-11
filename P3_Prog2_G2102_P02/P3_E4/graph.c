#include "graph.h"
#include "functions.h"
#include "list.h"
#include <stdlib.h>

#define NOT_BELONG -1

struct _Graph {
    List * nodes; /* Lista de nodos */
    List* out_connections; /* Lista de NodeConnections */
    List* in_connections; /* Lista de NodeConnections */
    int num_nodes;
    int num_edges;
};

typedef struct _NodeConnections {
    int nodeid;
    List* connections; /* Lista de enteros */
} NodeConnections;

NodeConnections* nc_ini(Node* n){
    NodeConnections* nc;
    if(!n) return NULL;
    nc = (NodeConnections*) calloc(1, sizeof (NodeConnections));
    if(!nc){
        return NULL;
    }
    nc->connections=list_ini(&destroy_intp_function,&copy_intp_function,&print_intp_function,&cmp_intp_function);
    if(!nc){
        return NULL;
    }
    nc->nodeid=node_getId(n);
    return nc;
}

void nc_destroy(NodeConnections *nc){
    if(!nc){
        return NULL;
    }
    list_destroy(nc->connections);
    free(nc);
}
/* TODO: graph_addEgde, graph_areConnected, graph_getConnectionsTo/From, graph_print*/


Graph * graph_ini() {
    Graph* g;
    int i, j;
    g = (Graph*) malloc(sizeof (Graph));

    if (!g) {
        fprintf(stderr, "graph_ini: error allocating memory.\n");
        return NULL;
    }

    g->nodes=list_ini(&destroy_node_function,&copy_node_function,&print_node_function,&cmp_node_function);
    g->out_connections=list_ini(&destroy_nodeConnections_function,&copy_nodeConnections_function,
    &print_nodeConnections_function,&cmp_nodeConnections_function);
    g->in_connections=list_ini(&destroy_nodeConnections_function,&copy_nodeConnections_function,
    &print_nodeConnections_function,&cmp_nodeConnections_function);
    
    
    g->num_nodes = 0; 
    /* zero nodes and edges at the beginning*/
    g->num_edges = 0;
    return g;
}

void graph_destroy(Graph* g) {
    if (!g) {
        /* if g points to NULL, it does nothing  */
        return;
    }
    list_destroy(g->in_connections);
    list_destroy(g->out_connections);
    list_destroy(g->nodes);
    
    /* free the memory allocated by the graph. */
    free(g); 
}

int graph_getNnodes(const Graph * g) {
    if (!g) { 
        /* if g point to NULL, return -1*/
        return -1;
    }
    /* return the current number of nodes */
    return g->num_nodes; 
}

int* graph_getNodeIds(const Graph * g) {
    int *temp;
    int i;
    if (!g) { 
        /* if g point to NULL, return NULL */
        return NULL;
    }

    temp = (int*) malloc(g->num_nodes * (sizeof (int)));

    if (!temp) { 
        /* if malloc fails return NULL.*/
        return NULL;
    }

    for (i = 0; i < g->num_nodes; i++) { 
        /* write into the array */
        temp[i] = node_getId(list_get(g->nodes, i+1));
    }
    /* return adress from the array's first element */
    return temp; 
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

int find_node_index(const Graph * g, int nId1) {
    int i;

    if (!g) { 
        /* if g point to NULL, return -1 */
        return -1;
    }

    for (i = 1; i <= g->num_nodes; i++) { 
        /* Look for the index which node of id <nId1> has.*/
        if (node_getId(list_get(g->nodes, i)) == nId1) { 
            /* if there's a coincidence, returns the index */
            return i;
        }
    }
    /* if there's no coincidence return NOT_BELONG (= -1) */
    return NOT_BELONG; 
}

Graph * graph_addNode(Graph * g, const Node* n) {
    /* error detection */
    Node* nodeAux;
    NodeConnections* nc;
    if ((!g) || (!n) || (g->num_nodes == MAX_NODES)) { 
        /* if g or n is NULL, either g is full, return NULL*/
        return NULL; 
    }

    if (find_node_index(g, node_getId(n)) == NOT_BELONG) {
        nodeAux=node_copy(n);
        nc = nc_ini(nodeAux);
        list_insertFirst (g->nodes,nodeAux);
        list_insertFirst (g->out_connections,nc);
        list_insertFirst (g->in_connections, nc);
        nc_destroy(nc);
        node_destroy(nodeAux);
        g->num_nodes++;
        
        /* if the node isn't in the graph, it is added to the graph
         and the number of nodes increases in 1*/
    }
    return g;
}

Graph * graph_addEdge(Graph * g, const int nId1, const int nId2) {
    int index1, index2, i, lisTam, exist = 0;
    NodeConnections* nc1, *nc2;
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
    nc1 =  list_get(g->out_connections, index1);
    nc2 =  list_get(g->in_connections, index2);
    lisTam = list_size(nc1->connections);
    for (i = 1; i<=lisTam; i++){
        if (list_get(nc1->connections, i)==index2){
            exist = 1;
        }
    }
    if (exist == 0){
        nc1->connections=list_insertFirst(nc1->connections, &nId2);
        if (!nc1->connections){
            fprintf(stderr,"");
            graph_destroy(g);
        }
        list_insertFirst(nc2->connections, &nId1);
        if (!nc2->connections){
            fprintf(stderr,"");
            graph_destroy(g);
        }
    }
    g->num_edges++;
    return g;
}

Node * graph_getNode(const Graph * g, int nId) {
    int index;
    index = find_node_index(g, nId);

    if (!g) { 
        /* error detection */
        return NULL;
    }

    if (index == NOT_BELONG) { 
        /* if the node does not belong, return NULL*/
        return NULL;
    }
    return (Node*)list_get(g->nodes, index);
}

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2) {
    int index1, index2, size, i, cmp;
    NodeConnections* nc;

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
    
    
    nc=list_get(g->out_connections, index1);
    size = list_size(nc->connections);
    for(i=1;i<=size;i++){
        cmp = *((int*)list_get(nc->connections, i));
        if(nId2==cmp){
            return TRUE;
        }
    }
    
    return FALSE;
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
        toId = node_getId(list_get(g->nodes, i+1)); /*SE ARREGLA DE MOMENTO*/

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
        toId = node_getId(list_get(g->nodes, i+1)); 
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

        fromId = node_getId(list_get(g->nodes, i));

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
        fromId = node_getId(list_get(g->nodes, i));
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
        /* prints list of nodes*/
        chars += list_print(pf, g->nodes); 
        
        /* print list of out connections */
        chars += list_print(pf, g->out_connections);
        
        /* print list of in connections */
        chars += list_print(pf, g->in_connections);

        chars += fprintf(pf, "\n");
    }
    /* prints chars, which is the value of all characters that have been printed */
    return chars; 
}