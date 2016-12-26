#ifndef __QUEUE_H__
#define __QUEUE_H__
typedef struct tagNode{
    void *data;
    struct tagNode *next;
}Node;

typedef struct tagQueue{

    Node *head, *last, *curr;
}Queue;

Queue *queue_create(int size);
void   queue_delete(Queue *q);
int    queue_push(Queue *q, void *data);
void*  queue_pop(Queue *q);

void   queue_test();

#endif
