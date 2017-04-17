/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p3_e1.c
 * Author: rafael, sergio
 *
 * Created on 21 de marzo de 2017, 12:36
 */

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "queue.h"
#include "functions.h"

#define MAX 255

/*
 * 
 */
Queue * read_queue_from_file(char * filename) {
    FILE * in;
    Queue * q;
    Node * n;
    char buff[MAX], name[MAX];
    int i, nnodes, id1;

    q = queue_ini(&destroy_node_function, &copy_node_function, &print_node_function);
    if (q == NULL) {
        return NULL;
    }
    in = (FILE*) fopen(filename, "r");
    if (in == NULL) {
        queue_destroy(q);
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
            queue_destroy(q);
            return NULL;
        }
        if (node_setName(n, name) == NULL) {
            fclose(in);
            node_destroy(n);
            queue_destroy(q);
            return NULL;
        }
        /* add node to queue */
        if (queue_insert(q, n) == NULL) {
            fclose(in);
            node_destroy(n);
            queue_destroy(q);
            return NULL;
        }
        /* destroy node */
        node_destroy(n);
    }

    fclose(in);

    return q;
}

void queue_print_status(FILE* f, Queue* q) {
    if (!q || !f) {
        return;
    }
    if (queue_isEmpty(q)) {
        fprintf(f, "Cola vacía.\n");
        return;
    }
    fprintf(f, "Cola con %d elementos:\n", queue_size(q));
    queue_print(f, q);
}

int main(int argc, char** argv) {
    Queue *qAux, *q1, *q2, *q3;
    void *eleAux;
    int qSize, i;
    FILE* f;
    f = stdout;
    if (argc < 2) {
        fprintf(stderr, "not enough parameters.\n");
        return EXIT_FAILURE;
    }
    q1 = queue_ini(&destroy_node_function, &copy_node_function, &print_node_function);
    if (!q1) {
        return EXIT_FAILURE;
    }
    q2 = queue_ini(&destroy_node_function, &copy_node_function, &print_node_function);
    if (!q2) {
        queue_destroy(q1);
        return EXIT_FAILURE;
    }
    q3 = queue_ini(&destroy_node_function, &copy_node_function, &print_node_function);
    if (!q3) {
        queue_destroy(q1);
        queue_destroy(q2);
        return EXIT_FAILURE;
    }
    fprintf(f, "Cola 1: ");
    queue_print_status(f, q1);
    fprintf(f, "Cola 2: ");
    queue_print_status(f, q2);
    fprintf(f, "Cola 3: ");
    queue_print_status(f, q3);
    fprintf(f, "\n");

    qAux = read_queue_from_file(argv[1]);
    if (!qAux) {
        queue_destroy(q1);
        queue_destroy(q2);
        queue_destroy(q3);
        return EXIT_FAILURE;
    }

    while (!queue_isEmpty(qAux)) {
        eleAux = queue_extract(qAux);
        q1 = queue_insert(q1, eleAux);
        if (!q1) {
            queue_destroy(q2);
            queue_destroy(q3);
            queue_destroy(qAux);
            return EXIT_FAILURE;
        }
        node_destroy((Node*) eleAux);

        fprintf(f, "Cola 1: ");
        queue_print_status(f, q1);
        fprintf(f, "Cola 2: ");
        queue_print_status(f, q2);
        fprintf(f, "Cola 3: ");
        queue_print_status(f, q3);
        fprintf(f, "\n");
    }

    fprintf(f, "<<<Pasando la primera mitad de Cola 1 a Cola 2\n\n");

    qSize = queue_size(q1);
    for (i = 0; i < (qSize / 2); i++) {
        eleAux = queue_extract(q1);
        q2 = queue_insert(q2, eleAux);

        if (!q2) {
            queue_destroy(q1);
            queue_destroy(q3);
            queue_destroy(qAux);
            return EXIT_FAILURE;
        }

        node_destroy((Node*) eleAux);
        fprintf(f, "Cola 1: ");
        queue_print_status(f, q1);
        fprintf(f, "Cola 2: ");
        queue_print_status(f, q2);
        fprintf(f, "Cola 3: ");
        queue_print_status(f, q3);
        fprintf(f, "\n");
    }



    fprintf(f, "<<<Pasando la segunda mitad de Cola 1 a Cola 3\n\n");
    while (!queue_isEmpty(q1)) {
        eleAux = queue_extract(q1);
        q3 = queue_insert(q3, eleAux);

        if (!q3) {
            queue_destroy(q1);
            queue_destroy(q2);
            queue_destroy(qAux);
            return EXIT_FAILURE;
        }

        node_destroy((Node*) eleAux);

        fprintf(f, "Cola 1: ");
        queue_print_status(f, q1);
        fprintf(f, "Cola 2: ");
        queue_print_status(f, q2);
        fprintf(f, "Cola 3: ");
        queue_print_status(f, q3);
        fprintf(f, "\n");
    }

    queue_destroy(q1);
    queue_destroy(q2);
    queue_destroy(q3);
    queue_destroy(qAux);
    return (EXIT_SUCCESS);
}

