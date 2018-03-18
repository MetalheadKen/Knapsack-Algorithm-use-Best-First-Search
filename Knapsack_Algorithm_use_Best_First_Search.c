#include <stdio.h>
#include <stdlib.h>
#include "Priority_Queue.h"

#define PERF         1
#define LENGTH       50
#define MAX_WEIGHT   100
#define QUEUE_LENGTH 10000000

#if PERF
    #include <time.h>
    #define PERF_TIMES(X) clock_t X = clock()
    #define PRINT_PERF(X) \
                printf("The execution times is %f s.\n", (double) (X) / CLOCKS_PER_SEC)
#else
    #define PERF_TIMES(...)
    #define PRINT_PERF(...)
#endif

typedef struct _Item {
    int profit;
    int weight;
} Item;

int   Compare(const void *, const void *);
int   Knapsack(Item *);
float Bound(Node, Item *);

_Priority_Queue_Algo *algo = &Priority_Queue_Algo;

int main(void)
{
    int  max_profit;
    Item item[] = {{20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1},
                   {20, 2}, {30, 5}, {35, 7}, {12, 3}, {3, 1}};

    /* Arrange profit divided by weigth of Item in descending order */
    qsort(item, LENGTH, sizeof(item[0]), Compare);

    PERF_TIMES(start_time);
    max_profit = Knapsack(item);
    PERF_TIMES(end_time);

    printf("The maximum profit is %d.\n", max_profit);
    PRINT_PERF(end_time - start_time);
    
    return 0;
}

int Compare(const void *numberA, const void *numberB)
{
    Item *itemA = (Item *) numberA;
    Item *itemB = (Item *) numberB;

    return (itemB->profit / itemB->weight) - (itemA->profit / itemA->weight);
}

int Knapsack(Item *item)
{
    Queue queue;
    Node  u, v;

    algo->Create(&queue, QUEUE_LENGTH);
    
    /* Set v as the root node */
    v.level = -1; v.profit = 0; v.weight = 0;
    v.bound = Bound(v, item);

    int max_profit = 0;
    algo->Insert(&queue, v);

    while (!algo->Is_Empty(queue)) {
        algo->Remove(&queue, &v);

        /* Check is promising or not */
        if (v.bound > max_profit) {
            u.level = v.level + 1;

            /* Set u as the child node of containing the next item */
            u.weight = v.weight + item[u.level].weight;
            u.profit = v.profit + item[u.level].profit;

            if (u.weight <= MAX_WEIGHT && u.profit > max_profit) {
                max_profit = u.profit;
            }

            u.bound = Bound(u, item);
            
            if (u.bound > max_profit) {
                algo->Insert(&queue, u);
            }

            /* Set u as the child node of not containing the next item */
            u.weight = v.weight;
            u.profit = v.profit;
            u.bound  = Bound(u, item);

            if (u.bound > max_profit) {
                algo->Insert(&queue, u);
            }
        }
    }

    algo->Delete(queue);

    return max_profit;
}

float Bound(Node u, Item *item)
{
    int   j, totweight;
    float result;

    if (u.weight >= MAX_WEIGHT) {
        return 0.0;
    } else {
        /* Initializer the value */
        j = u.level + 1;
        result = u.profit;
        totweight = u.weight;

        /* Take item as much as possible */
        while ((j < LENGTH) && (totweight + item[j].weight <= MAX_WEIGHT)) {
            totweight = totweight + item[j].weight;
            result    = result + item[j].profit;
            j++;
        }

        int k = j;
        if (k < LENGTH) {
            result += (MAX_WEIGHT - totweight) * item[k].profit / item[k].weight;
        }

        return result;
    }
}
