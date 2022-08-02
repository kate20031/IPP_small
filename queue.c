#include <assert.h>
#include <malloc.h>
#include "queue.h"


struct queue {
    struct elt *head;
    struct elt *tail;
};
typedef struct queue queue;


struct elt {
    struct elt *next;
    size_t index;
    size_t distance;
};
typedef struct elt elt;


queue *queueCreate(void) {
    queue *q;
    q = malloc(sizeof(queue));
    q->head = q->tail = 0;
    return q;
}


void addToQueue(queue *q, size_t index, size_t distance) {
    elt *e;
    e = malloc(sizeof(elt));
    assert(e);

    e->index = index;
    e->distance = distance;
    e->next = 0;
    if (q->head == 0) {
        q->head = e;
    } else {
        q->tail->next = e;
    }

    q->tail = e;
}


int queueEmpty(const queue *q) {
    return (q->head == 0);
}


/**
 * Function returns index of element from front of queue
 * @param q
 * @return
 */
size_t getIndex(queue *q) {
    assert(!queueEmpty(q));
    return q->head->index;
}


/**
 * Function returns distance of element from front of queue.
 * @param q - a queue.
 * @return  a distance from a source cell to a current cell.
 */
size_t getDistance(queue *q) {
    assert(!queueEmpty(q));

    return q->head->distance;
}


void removeFirst(queue *q) {
    elt *e;
    assert(!queueEmpty(q));

    e = q->head;
    q->head = e->next;
    free(e);
}


void deleteQueue(queue *q) {
    while (!queueEmpty(q)) {
        removeFirst(q);
    }
    free(q);
}