/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   p4_e3.c
 * Author: rafael
 *
 * Created on 25 de abril de 2017, 12:21
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
    int x;
    if(!name){
        fprintf(stderr, "No file specified.\n");
        return NULL;
    }
    f=fopen(name,"r");
    if(!f){
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }
    t=tree_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    if(!t){
        fclose(f);
        return NULL;
    }
    while (!feof(f)) {
        fgets(buff, MAXSIZE, f);
        sscanf(buff, "%d", &x);
        /* OPTIONAL */
        if(tree_insert(t, &x)==ERROR){
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
    List *lpre, *lin, *lpost;
    FILE *fout;
    int x;
    fout=stdout;
    if (argc < 2){
        fprintf(stderr,"main: invalid number of arguments.\n\tusage is: ./p4_e3 nameoffile.txt\n");
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

    fprintf(fout, "Orden previo: ");
    tree_preOrder(fout, t);
    fprintf(fout, "\nOrden medio: ");
    tree_inOrder(fout, t);
    fprintf(fout, "\nOrden posterior: ");
    tree_postOrder(fout, t);

    fprintf(fout, "\n*** Creando lista preOrder ***:\n");
    lpre=list_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    if(!lpre){
        tree_destroy(t);
        return EXIT_FAILURE;
    }
    if(tree_preOrderToList(lpre, t)==ERROR){
        tree_destroy(t);
        list_destroy(lpre);
        return EXIT_FAILURE;
    }
    list_print(fout,lpre);
    list_destroy(lpre);

    fprintf(fout, "*** Creando lista inOrder ***:\n");
    lin=list_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    if(!lin){
        tree_destroy(t);
        return EXIT_FAILURE;
    }
    if(tree_inOrderToList(lin, t)==ERROR){
        tree_destroy(t);
        list_destroy(lin);
        return EXIT_FAILURE;
    }
    list_print(fout,lin);
    list_destroy(lin);

    fprintf(fout, "*** Creando lista postOrder ***:\n");
    lpost=list_ini(destroy_intp_function,copy_intp_function,print_intp_function,cmp_intp_function);
    if(!lpost){
        tree_destroy(t);
        return EXIT_FAILURE;
    }
    if(tree_postOrderToList(lpost, t)==ERROR){
        tree_destroy(t);
        list_destroy(lpost);
        return EXIT_FAILURE;
    }
    list_print(fout,lpost);
    list_destroy(lpost);


    fprintf(fout, "\nIntroduzca un número: ");
    scanf("%d", &x);
    fprintf(fout, "Número introducido: %d\n", x);

    switch(tree_find(t, &x)){
        case TRUE :
            fprintf(fout, "El dato %d se encuentra dentro del Arbol\n",x);
            break;

        case FALSE :
            fprintf(fout, "El dato %d NO se encuentra dentro del Arbol\n",x);
            break;

        default:
            fprintf(fout, "main: switch error has ocurred.\n");
            tree_destroy(t);
            return EXIT_FAILURE;
    }

    tree_destroy(t);
    return EXIT_SUCCESS;
}
