#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct _Node {
    int   level;      /* The level of tree */
    int   profit;
    int   weight;
    float bound;
} Node;

typedef struct _Queue {
    int  front, rear;
    int  length;
    Node *data;
} Queue;

typedef struct _Priority_Queue_Algo {
    void (*Create)(Queue *, int);
    void (*Delete)(Queue);

    bool (*Is_Empty)(Queue);
    bool (*Is_Full)(Queue);

    void (*Insert)(Queue *, Node);
    void (*Remove)(Queue *, Node *);
} _Priority_Queue_Algo;

extern _Priority_Queue_Algo Priority_Queue_Algo;

#endif /* PRIORITY_QUEUE_H_ */
