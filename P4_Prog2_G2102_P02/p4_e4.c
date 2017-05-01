/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p4_e4.c
 * Author: rafael
 *
 * Created on 25 de abril de 2017, 13:26
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "functions.h"
#define MAXSIZE 255

/*
 * 
 */

Tree* read_tree_from_file (char* name){
    FILE *f;
    Tree *t;
    char buff[MAXSIZE];
    if(!name){
        fprintf(stderr, "No file specified.\n");
        return NULL;
    }
    f=fopen(name,"r");
    if(!f){
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }
    t=tree_ini(destroy_string_function,copy_string_function,print_string_function,cmp_string_function);
    if(!t){
        fclose(f);
        return NULL;
    }
    while (!feof(f)) {
        fscanf(f, "%s\n", buff);
        /* OPTIONAL */
        if(tree_insert(t, buff)==ERROR){
            fclose(f);
            tree_destroy(t);
            return NULL;
        }
    }
    fclose(f);
    return t;
}


int main(int argc, char** argv) {
    Tree *t;
    FILE *fout;
    char s[MAXSIZE];
    int x;
    fout=stdout;
    if (argc < 2){
        fprintf(stderr,"main: invalid number of arguments.\n\tusage is: ./p4_e4 nameoffile.txt\n");
        return EXIT_FAILURE;
    }
    t=read_tree_from_file(argv[1]);
    if(!t){
        fprintf(stderr, "main: error reading tree from file.\n");
        tree_destroy(t);
        return EXIT_FAILURE;
    }
    
    x=tree_numNodes(t);
    if(x==-1){
        fprintf(stderr, "main: error getting number of nodes from tree");
        tree_destroy(t);
        return EXIT_FAILURE;
    }
    fprintf(fout, "Numero de nodos: %d\n", x);
    
    x=tree_depth(t);
    if(x==-1){
        fprintf(stderr, "main: error getting depth from tree");
        tree_destroy(t);
        return EXIT_FAILURE;
    }
    fprintf(fout, "Profundidad: %d\n", x);
    
    tree_inOrder(fout, t);
    fprintf(fout, "\n");
    fprintf(fout, "Introduzca una cadena para buscar en el árbol (siguiendo el mismo formato que en el fichero de entrada): ");
    gets(s);
    
    switch(tree_find(t, s)){
        case TRUE :
            fprintf(fout, "Elemento encontrado!\n");
            break;
            
        case FALSE :
            fprintf(fout, "Elemento no encontrado!\n");
            break;
            
        default:
            fprintf(fout, "main: switch error has ocurred.\n");
            tree_destroy(t);
            return EXIT_FAILURE;
    }
    
    tree_destroy(t);
    return EXIT_SUCCESS;
}

