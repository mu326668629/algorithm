#include <stdlib.h>
#include "common.h"
#include "queue.h"
/*
 * cycle queue
 *
 *
 *
 */

#define QUEUE_SIZE 3

static int queue_expend(Queue *q, int size)
{
    Node *curr, *last;
    int i;

    curr = last = (Node *)calloc(1,sizeof(Node));
    if(!last){
        return 0;
    }
    for(i = 1; i < size; ++i){
        curr->next = (Node*)calloc(1, sizeof(Node));
        if(!curr->next){
            break;
        }
        curr = curr->next;
    }
    if(q->last){
        q->last->next = last;
    } else {
        q->head = last;
    }
    q->last = curr;
    q->last->next = q->head;
    return i;
}

Queue *queue_create(int size)
{
    Queue *q;

    q = (Queue*)calloc(1, sizeof(Queue));
    if(!q){
        return NULL;
    }
    if(queue_expend(q, size) != size){
        queue_delete(q);
        return NULL;
    }
    return q;
}

void queue_delete(Queue *q)
{

}

int queue_push(Queue *q, void *data)
{
    if(!q || !q->head){
        return -1;
    }
    if(!q->curr){//空队列
        q->curr = q->head;
    } else if(q->last == q->head){//满队列
        if(queue_expend(q, QUEUE_SIZE) <= 0){
            return -1;
        }

    }
    q->head->data = data;
    q->head = q->head->next;
    return 0;
}

void* queue_pop(Queue *q)
{
    void *data = NULL;

    if(!q || !q->curr){
        return NULL;
    }
    if(q->curr == q->last){
        return NULL;
    }
    data = q->curr->data;
    q->curr = q->curr->next;
    return data;
}
/*
 * Example
 */
void queue_test()
{
    int list[1024];
    int i, err;
    int size = 45;
    int *ptr;
    Queue *q = queue_create(QUEUE_SIZE);


    for(i = 0; i < size; ++i){
      list[i] = i;
    }

    for(i = 0; i < size; ++i){
        err = queue_push(q, list+i);
        if(err){
            LOG_INFO("push fail i=%d", i);
            break;
        }
    }
    for(i = 0; i < size; ++i){
        ptr = (int*)queue_pop(q);

        if(!ptr || *ptr != i){
            LOG_INFO("push fail i=%d, ptr=%p", i, ptr);
        }
    }
    ptr = (int*)queue_pop(q);
    if(ptr){
        LOG_INFO("fail %d", *ptr);
    }
}
