#include <stdlib.h>
#include "graph.h"

int main() {
    Node *n1, *n2;
    Graph *g;

    n1 = node_ini();
    n2 = node_ini();

    n1 = node_setName(n1, "first");
    n1 = node_setId(n1, 111);
    n2 = node_setName(n2, "second");
    n2 = node_setId(n2, 222);

    g = graph_ini();

    graph_print(stdout, g);
    fprintf(stdout, "Insertando nodo 1...\n");
    g = graph_addNode(g, n1);
    graph_print(stdout, g);
    fprintf(stdout, "\nInsertando nodo 2...\n");
    g = graph_addNode(g, n2);
    graph_print(stdout, g);

    if (graph_areConnected(g, node_getId(n1), node_getId(n2)) == FALSE) fprintf(stdout, "Conectados nodo 1 y nodo 2? No\n");
    else fprintf(stdout, "Conectados nodo 1 y nodo 2? Si\n");

    if (graph_areConnected(g, node_getId(n2), node_getId(n1)) == FALSE) fprintf(stdout, "Conectados nodo 2 y nodo 1? No\n");
    else fprintf(stdout, "Conectados nodo 2 y nodo 1? Si\n");

    fprintf(stdout, "\nInsertando nodo 2 -> nodo 1\n");
    g = graph_addEdge(g, node_getId(n2), node_getId(n1));
    graph_print(stdout, g);


    if (graph_areConnected(g, node_getId(n1), node_getId(n2)) == FALSE) fprintf(stdout, "Conectados nodo 1 y nodo 2? No\n");
    else fprintf(stdout, "Conectados nodo 1 y nodo 2? Si\n");

    if (graph_areConnected(g, node_getId(n2), node_getId(n1)) == FALSE) fprintf(stdout, "Conectados nodo 2 y nodo 1? No\n");
    else fprintf(stdout, "Conectados nodo 2 y nodo 1? Si\n");

    fprintf(stdout, "\nInsertando nodo 1 -> nodo 2\n");
    g = graph_addEdge(g, node_getId(n1), node_getId(n2));
    graph_print(stdout, g);

    if (graph_areConnected(g, node_getId(n1), node_getId(n2)) == FALSE) fprintf(stdout, "Conectados nodo 1 y nodo 2? No\n");
    else fprintf(stdout, "Conectados nodo 1 y nodo 2? Si\n");

    if (graph_areConnected(g, node_getId(n2), node_getId(n1)) == FALSE) fprintf(stdout, "Conectados nodo 2 y nodo 1? No\n");
    else fprintf(stdout, "Conectados nodo 2 y nodo 1? Si\n");

    fprintf(stdout, "\nInsertando nodo 2 -> nodo 1\n");
    g = graph_addEdge(g, node_getId(n2), node_getId(n1));
    graph_print(stdout, g);

    if (graph_areConnected(g, node_getId(n1), node_getId(n2)) == FALSE) fprintf(stdout, "Conectados nodo 1 y nodo 2? No\n");
    else fprintf(stdout, "Conectados nodo 1 y nodo 2? Si\n");

    if (graph_areConnected(g, node_getId(n2), node_getId(n1)) == FALSE) fprintf(stdout, "Conectados nodo 2 y nodo 1? No\n");
    else fprintf(stdout, "Conectados nodo 2 y nodo 1? Si\n");


    node_destroy(n1);
    node_destroy(n2);
    graph_destroy(g);
    
    return EXIT_SUCCESS;
}