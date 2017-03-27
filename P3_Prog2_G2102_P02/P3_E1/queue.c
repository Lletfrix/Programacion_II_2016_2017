#include "queue.h"

struct _Queue {
    void** front;
    void** rear;
    void* item[MAXQUEUE];
    destroy_elementqueue_function_type destroy_element_function;
    copy_elementqueue_function_type copy_element_function;
    print_elementqueue_function_type print_element_function;
};

Queue* queue_ini(destroy_elementqueue_function_type f1, copy_elementqueue_function_type f2, print_elementqueue_function_type f3) {
    Queue* q;

    if (!f1 || !f2 || !f3) {
        fprintf(stderr, "queue_ini: invalid arguments.");
        return NULL;
    }

    q = (Queue*) calloc(1, sizeof (Queue));

    if (!q) {
        fprintf(stderr, "queue_ini: fail allocating memory.");
        return NULL;
    }

    q->destroy_element_function = f1;
    q->copy_element_function = f2;
    q->print_element_function = f3;

    q->front = q->item;
    q->rear = q->item;
    
    return q;

}

void queue_destroy(Queue *q) {
    if (q == NULL) {
        fprintf(stderr, "queue_destroy: queue already NULL.");
        return;
    }
    while ((q->front) != (q->rear)) {
        q->destroy_element_function(*(q->front));
        if (q->front != q->item[MAXQUEUE - 1]) {
            (q->front)++;
        } else {
            (q->front) = (q->item);
        }
    }
    free (q);
}

Bool queue_isEmpty(const Queue *q) {
    if (!q) {
        fprintf(stderr, "queue_isEmpty: invalid argument.");
        return FALSE;
    }
    if (q->front != q->rear) {
        return FALSE;
    }
    return TRUE;
}

Bool queue_isFull(const Queue *q) {
    if (!q) {
        fprintf(stderr, "queue_isFull: invalid argument.");
        return FALSE;
    }
    if (q->rear == q->item[MAXQUEUE - 1]) {
        if (q->front == q->item) {
            return TRUE;
        }
        return FALSE;
    }
    if (q->front == q->rear + 1) {
        return TRUE;
    }
    return FALSE;
}

Queue* queue_insert(Queue *q, const void* pElem) {
    if (!q || !pElem) {
        fprintf(stderr, "queue_insert: invalid arguments.");
        return NULL;
    }
    if (queue_isFull(q)) {
        fprintf(stderr, "queue_insert: queue is already full");
        return NULL;
    }
    *(q->rear) = q->copy_element_function(pElem);
    if (!(*(q->rear))) {
        fprintf(stderr, "queue_insert: error copying element");
        return NULL;
    }
    if (q->rear != q->item[MAXQUEUE - 1]) {
        q->rear++;
    } else {
        q->rear = q->item;
    }
    return q;
}

void * queue_extract(Queue *q){
    
  void** ele;
  
  if (!q){
    fprintf(stderr, "queue_extract: invalid arguments.");
    return NULL;
  }
  if (queue_isEmpty(q)){
    fprintf(stderr, "queue_extract: queue is already empty");
    return NULL;
  }
  ele = q->front;
  if(q->front==q->item[MAXQUEUE-1]){
      q->front = q->item;
      return *ele;
  }
  
  q->front++;
  return *ele;
}

int queue_size(const Queue *q) {
    int i = 0;
    if (!q) {
        fprintf(stderr, "queue_size: invalid argument.");
        return -1;
    }
    if (q->front <= q->rear) {
        i = (q->rear - q->front);
    } else {
        i = (q->front - q->rear + MAXQUEUE);
    }
    return i;
}

int queue_print(FILE *pf, const Queue *q){
    int chars=0;
    void **front;
    if (!pf || !q){
        fprintf(stderr, "queue_print: invalid arguments");
        return -1;
    }
    front=q->front;
    while (front != (q->rear)) {
        chars+=q->print_element_function(pf, *(front));
        chars+=fprintf(pf,"\n");
        if (front != q->item[MAXQUEUE - 1]) {
            front++;
        } else {
            front = q->item;
        }
    }
    return chars;
}