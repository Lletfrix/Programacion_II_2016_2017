#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include "types.h"

typedef struct _Node Node;


/* Color del nodo, blanco implica no descubierto, gris descubierto y negro cerrado o explorado */
typedef enum {
    WHITE, GREY, BLACK
} Color;

/* Inicializa un nodo, reservando memoria y devolviendo el nodo inicializado si lo ha hecho correctamente, NULL en
otro caso */
Node * node_ini();
/* Libera la memoria dinámica reservada para un nodo */
void node_destroy(Node * n);

/* Devuelve el id de un nodo dado, o -1 si se produce algún error */
int node_getId(const Node * n);
/* Devuelve un puntero al nombre de un nodo dado, o NULL si se produce algún error */
char* node_getName(const Node * n);
/* Devuelve el color de un nodo dado, WHITE si se produce algun error */
Color node_getColor (const Node *n);

/* Modifica el id de un nodo dado, devuelve NULL si se produce algún error */
Node * node_setId(Node * n, const int id);
/* Modifica el nombre de un nodo dado, devuelve NULL si se produce algún error */
Node * node_setName(Node * n, const char* name);
/* Modifica el color de un nodo dado, devuelve NULL si se produce algún error */
Node * node_setColor(Node * n, const Color color);

/* Devuelve TRUE si los dos nodos pasados como argumento son iguales (revisando todos sus campos).
 Devuelve FALSE en otro caso. */
Bool node_equals(const Node * n1, const Node * n2);
/* Copia los datos de un nodo a otro devolviendo el nodo copiado (incluyendo la reserva de la memoria necesaria)
si todo ha ido bien, o NULL en otro caso */
Node * node_copy(const Node * src);

/* Imprime en pf los datos de un nodo con el siguiente formato: [id, name]. Por ejemplo, un nodo con nombre “aaa”
e id 123 se imprimirá como [123, aaa]. Además devolverá el número de caracteres que se han escrito con éxito
(mirar documentación de fprintf) */
int node_print(FILE *pf, const Node * n);
#endif /* NODE_H */