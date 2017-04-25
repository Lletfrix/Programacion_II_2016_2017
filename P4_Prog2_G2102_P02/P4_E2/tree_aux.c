#include "tree.h"

typedef struct _NodeBT {
void* info;
struct _NodeBT* left;
struct _NodeBT* right;
} NodeBT;
struct _Tree {
NodeBT *root;
destroy_elementtree_function_type destroy_element_function;
copy_elementtree_function_type copy_element_function;
print_elementtree_function_type print_element_function;
cmp_elementtree_function_type cmp_element_function;
};

/* Inicializa el árbol reservando memoria */
Tree* tree_ini( destroy_elementtree_function_type f1,
copy_elementtree_function_type f2,
print_elementtree_function_type f3,
cmp_elementtree_function_type f4);
/* Libera el árbol y todos sus elementos */
void tree_destroy(Tree* pa);
/* Inserta en el árbol pa una copia del puntero po, devolviendo ERROR si el elemento ya existía en el árbol */
Status tree_insert(Tree* pa, const void* po);
/* Devuelve TRUE si se puede encontrar po en el árbol pa */
Bool tree_find(Tree* pa, const void* po);
/* Comprueba si un árbol está vacío */
Bool tree_isEmpty( const Tree* pa){
    if (!pa){
        fprintf(stderr, "Invalid arguments in tree_isEmpty");
        return TRUE;
    }
    if(!pa->root){
        return TRUE;
    }
    return FALSE;
}
/* Devuelve la profundidad del árbol pa, considerando que un árbol vacío tiene profundidad -1 */
int nodeBT_depth_recursive(NodeBT *n){
    int depthLeft, depthRight;
    if (!n){
        return 0;
    }
    depthLeft = nodeBT_depth_recursive(n->left);
    depthRight = nodeBT_depth_recursive(n->right);
    if (depthLeft > depthRight){
        return depthLeft + 1;
    }
    return depthRight + 1;
}

int tree_depth(const Tree* pa) {
    int depth;
    if (!pa) {
        fprintf(stderr, "Invalid arguments in tree_depth");
        return -1;
    }
    if (!pa->root) {
        return 0;
    }
    depth = nodeBT_depth_recursive(pa->root);
    return depth;
}
/* Devuelve el número de nodos del árbol pa, considerando que un árbol vacío tiene 0 nodos */
int nodeBT_numNodes_recursive(NodeBT* n){
    if(!n){
        return 0;
    }
    int res;
    res = nodeBT_numNodes_recursive(n->left) + nodeBT_numNodes_recursive(n->right) + 1;
    return res;
}
int tree_numNodes(const Tree* pa){
    int res = 0;
    if (!pa){
        fprintf(stderr,"Invalid arguments in tree_numNodes\n");
        return -1;
    }
    if (pa->root==NULL){
        return 0;
    }
    res = nodeBT_numNodes_recursive(pa->root);
    return res;
}
/******* Funciones de recorrido del árbol (P4_E3) ********/
/* Muestra el recorrido de un árbol en orden previo */
Status tree_preOrder(FILE* f, const Tree* pa);
/* Muestra el recorrido de un árbol en orden medio */
Status tree_inOrder(FILE* f, const Tree* pa);
/* Muestra el recorrido de un árbol en orden posterior */
Status tree_postOrder(FILE* f, const Tree* pa);
/****** Para el ejercicio opcional de P4_E3 *******/
/* Inserta en la lista l el recorrido de un árbol en orden previo */
Status tree_preOrderToList(List* l, const Tree* pa);
/* Inserta en la lista l el recorrido de un árbol en orden medio */
Status tree_inOrderToList(List* l, const Tree* pa);
/* Inserta en la lista l el recorrido de un árbol en orden posterior */
Status tree_postOrderToList(List* l, const Tree* pa);

