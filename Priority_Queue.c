#include <stdio.h>
#include <stdlib.h>
#include "Priority_Queue.h"

static void Create(Queue *queue, int length)
{
    queue->front  = -1;
    queue->rear   = -1;
    queue->length = length;
    queue->data   = (Node *) calloc(length, sizeof(Node));
}

static void Delete(Queue queue)
{
    free(queue.data);
}

static bool Is_Empty(Queue q)
{
    return (q.front == -1 && q.rear == -1);
}

static bool Is_Full(Queue q)
{
    return (q.rear == q.length - 1);
}

static void Insert(Queue *q, Node node)
{
    if (Is_Full(*q)) {
        printf("Queue is full!\n");
    } else if (Is_Empty(*q)) {
        q->front         = 0;
        q->rear          = 0;
        q->data[q->rear] = node;
    } else {
        for (int i = 0; i <= q->rear; i++) {
            if (node.bound > q->data[i].bound) {
                for (int j = q->rear + 1; j > i; j--) {
                    q->data[j] = q->data[j - 1];
                }

                q->rear++;
                q->data[i] = node;
                return;
            }
        }

        q->rear++;
        q->data[q->rear] = node;
    }
}

static void Remove(Queue *q, Node *node)
{
    if (Is_Empty(*q)) {
        printf("Queue is empty!\n");
        return;
    }

    *node = q->data[q->front];

    for (int i = q->front; i < q->rear; i++) {
        q->data[i] = q->data[i + 1];
    }

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->rear--;
    }
}

_Priority_Queue_Algo Priority_Queue_Algo = {
    .Create   = Create,
    .Delete   = Delete,

    .Is_Empty = Is_Empty,
    .Is_Full  = Is_Full,
    .Insert   = Insert,
    .Remove   = Remove,
};
