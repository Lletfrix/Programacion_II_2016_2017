/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tree.c
 * Author: rafael
 * 
 * Created on 18 de abril de 2017, 12:17
 */

#include "tree.h"
#include "list.h"

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

NodeBT* nodeBT_ini(){
    NodeBT* n = NULL;
    n = (NodeBT*) calloc (1, sizeof(NodeBT));
    if(!n){
        fprintf(stderr, "nodeBT_ini: error allocating memory.\n");
        return NULL;
    }
    return n;
}

void nodeBT_destroy(NodeBT* n, destroy_elementtree_function_type f1){
    if(!n){
        fprintf(stderr, "nodeBT_destroy: node already pointing NULL.\n");
        return;
    }
    if(!f1){
        fprintf(stderr, "nodeBT_destroy: invalid destroy function.\n");
        return;
    }
    f1(n->info);
    free(n);
}

/*
 * Recursive functions
 */

void nodeBT_destroy_recursive (NodeBT* n, destroy_elementtree_function_type f1){
    if(!n){
        return;
    }
    nodeBT_destroy_recursive(n->left, f1);
    nodeBT_destroy_recursive(n->right, f1);
    nodeBT_destroy(n, f1);
}

Status nodeBT_insert_recursive(NodeBT* n, cmp_elementtree_function_type pf1, void* pElem) {
    int value;
    if (!pf1) {
        fprintf(stderr, "nodeBT_insert_recursive: cmp function pointing NULL.\n");
        return ERROR;
    }
    value = pf1(n->info, pElem);
    if(value==0){
        /*fprintf(stderr, "nodeBT_insert_recursive: element already exists.\n");*/
        return ERROR;
    }
    if (value > 0) {
        if (!n->left) {
            n->left=nodeBT_ini();
            if(!n->left){
                fprintf(stderr, "nodeBT_insert_recursive: error allocating memory.\n");
                return ERROR;
            }
            n->left->info = pElem;
            return OK;
        }
        nodeBT_insert_recursive(n->left, pf1, pElem);
    }
    if (value < 0){
        if (!n->right) {
            n->right=nodeBT_ini();
            if(!n->right){
                fprintf(stderr, "nodeBT_insert_recursive: error allocating memory.\n");
                return ERROR;
            }
            n->right->info = pElem;
            return OK;
        }
        nodeBT_insert_recursive(n->right, pf1, pElem);
    }
}


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


int nodeBT_numNodes_recursive(NodeBT* n){
    int res;
    if(!n){
        return 0;
    }
    res = nodeBT_numNodes_recursive(n->left) + nodeBT_numNodes_recursive(n->right) + 1;
    return res;
}

Bool nodeBT_find_recursive (NodeBT* n, const void* pElem, cmp_elementtree_function_type f){
    int value;
    if (!n || !pElem || !f){
        /*fprintf(stderr, "nodeBT_find_recursive: invalid arguments.\n");*/
        return FALSE;
    }
    value=f(n->info,pElem);
    
    if (value==0){
        return TRUE;
    }
    if (value < 0){
        nodeBT_find_recursive(n->right,pElem,f);
    }
    if (value > 0){
        nodeBT_find_recursive(n->left,pElem,f);
    }
}

void nodeBT_preOrder_recursive(FILE* f, NodeBT* n, print_elementtree_function_type func){
    if(!n){
        return;
    }
    func(f,n->info);
    nodeBT_preOrder_recursive(f,n->left,func);
    nodeBT_preOrder_recursive(f,n->right,func);
}

void nodeBT_inOrder_recursive(FILE* f, NodeBT* n, print_elementtree_function_type func){
    if(!n){
        return;
    }
    nodeBT_inOrder_recursive(f,n->left,func);
    func(f,n->info);
    nodeBT_inOrder_recursive(f,n->right,func);
}

void nodeBT_postOrder_recursive(FILE* f, NodeBT* n, print_elementtree_function_type func){
    if(!n){
        return;
    }
    nodeBT_postOrder_recursive(f,n->left,func);
    nodeBT_postOrder_recursive(f,n->right,func);
    func(f,n->info);
}

void nodeBT_preOrderToList_recursive(List* l, NodeBT* n){
    if(!n){
        return;
    }
    nodeBT_preOrderToList_recursive(l, n->right);
    nodeBT_preOrderToList_recursive(l, n->left);
    list_insertFirst(l, n->info);
}

void nodeBT_inOrderToList_recursive(List* l, NodeBT* n){
    if(!n){
        return;
    }
    nodeBT_inOrderToList_recursive(l, n->right);
    list_insertFirst(l, n->info);
    nodeBT_inOrderToList_recursive(l, n->left);
}

void nodeBT_postOrderToList_recursive(List* l, NodeBT* n){
    if(!n){
        return;
    }
    list_insertFirst(l, n->info);
    nodeBT_postOrderToList_recursive(l, n->right);
    nodeBT_postOrderToList_recursive(l, n->left);
}
/*******************************************************************************/

Tree* tree_ini(destroy_elementtree_function_type f1,
        copy_elementtree_function_type f2,
        print_elementtree_function_type f3,
        cmp_elementtree_function_type f4){

    Tree* t=NULL;
    
    if (!f1 || !f2 || !f3 || !f4){
        fprintf(stderr, "tree_ini: invalid arguments.\n");
        return NULL;
    }
    
    t=(Tree*) calloc (1,sizeof(Tree));
    
    if (!t){
        fprintf(stderr, "tree_ini: error allocating memory.\n");
        return NULL;
    }
    
    t->destroy_element_function=f1;
    t->copy_element_function=f2;
    t->print_element_function=f3;
    t->cmp_element_function=f4;
    
    return t;
}

void tree_destroy(Tree* t){
    if(!t){
        fprintf(stderr, "tree_destroy: tree already pointing NULL.\n");
        return;
    }
    if (!t->root){
        free(t);
        return;
    }
    nodeBT_destroy_recursive(t->root, t->destroy_element_function);
    free(t);
}

Status tree_insert(Tree* t , const void* pElem){
    void* elem;
    if(!t || !pElem){
        fprintf(stderr, "tree_insert: invalid arguments.\n");
        return ERROR;
    }
    if(!t->root){
        t->root=nodeBT_ini();
        if(!t->root){
            fprintf(stderr, "tree_insert: error allocating memory.\n");
            return ERROR;
        }
        t->root->info=t->copy_element_function(pElem);
        if(!t->root->info){
            fprintf(stderr, "tree_insert: error copying element.\n");
            return ERROR;
        }
        return OK;
    }
    elem=t->copy_element_function(pElem);
    if(nodeBT_insert_recursive(t->root, t->cmp_element_function, elem)==ERROR){
        t->destroy_element_function(elem);
        return ERROR;
    }
    return OK;
}

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
    return depth-1;
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

Bool tree_find(Tree* t, const void* pElem){
    if (!t || !pElem){
        fprintf(stderr,"tree_find: invalid arguments.\n");
        return FALSE;
    }
    if (tree_isEmpty(t)){
        return FALSE;
    }
    if(t->cmp_element_function(t->root->info, pElem)==0){
        return TRUE;
    }
    return nodeBT_find_recursive(t->root, pElem, t->cmp_element_function);
}

Status tree_preOrder(FILE* f, const Tree* pa){
    if(!f || !pa){
        fprintf(stderr, "tree_preOrder: invalid arguments.\n");
        return ERROR;
    }
    nodeBT_preOrder_recursive(f, pa->root, pa->print_element_function);
    return OK;
}

Status tree_inOrder(FILE* f, const Tree* pa){
    if(!f || !pa){
        fprintf(stderr, "tree_inOrder: invalid arguments.\n");
        return ERROR;
    }
    nodeBT_inOrder_recursive(f, pa->root, pa->print_element_function);
    return OK;
}

Status tree_postOrder(FILE* f, const Tree* pa){
    if(!f || !pa){
        fprintf(stderr, "tree_postOrder: invalid arguments.\n");
        return ERROR;
    }
    nodeBT_postOrder_recursive(f, pa->root, pa->print_element_function);
    return OK;
}

Status tree_preOrderToList(List* l, const Tree* pa) {
    if (!l || !pa) {
        fprintf(stderr, "tree_preOrderToList: invalid arguments.\n");
        return ERROR;
    }
    nodeBT_preOrderToList_recursive(l, pa->root);
    return OK;
}

Status tree_inOrderToList(List* l, const Tree* pa){
    if (!l || !pa) {
        fprintf(stderr, "tree_inOrderToList: invalid arguments.\n");
        return ERROR;
    }
    nodeBT_inOrderToList_recursive(l, pa->root);
    return OK;
}

Status tree_postOrderToList(List* l, const Tree* pa){
    if (!l || !pa) {
        fprintf(stderr, "tree_postOrderToList: invalid arguments.\n");
        return ERROR;
    }
    nodeBT_postOrderToList_recursive(l, pa->root);
    return OK;
}
