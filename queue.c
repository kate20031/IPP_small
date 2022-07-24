#include <assert.h>
#include <malloc.h>
#include "queue.h"

struct queue {
    struct elt *head;
    struct elt *tail;
};

struct elt {
    struct elt *next;
    size_t index;
    size_t distance;
};

/** Function create a new empty queue.
 *
 * @return  return new queue
 */
struct queue *
queueCreate(void)
{
    struct queue *q;
    q = malloc(sizeof(struct queue));
    q->head = q->tail = 0;
    return q;
}


/**
 * Function add a new node to back of queue.
 * @param q - queue.
 * @param index – index of the cell in maze.
 * @param distance – maintains the length of the path from a source cell to a current cell.
 */
void addToQueue(struct queue *q, size_t index, size_t distance)
{
    struct elt *e;
    e = malloc(sizeof(struct elt));
    assert(e);

    e->index = index;
    e->distance = distance;
    e->next = 0;
    if(q->head == 0) {
        q->head = e;
    } else {
        q->tail->next = e;
    }

    q->tail = e;
}


/** Function checks if the queue is empty.
 *
 * @param q – a queue.
 * @return 1 - if it's empty,
 *         0 - otherwise.
 */
int queueEmpty(const struct queue *q)
{
    return (q->head == 0);
}


/**
 * Function returns index of element from front of queue
 * @param q
 * @return
 */
size_t getIndex(struct queue *q)
{
    size_t index = 0;;
    struct elt *e;

    assert(!queueEmpty(q));
    return q->head->index;
}


/**
 * Function returns distance of element from front of queue.
 * @param q - a queue.
 * @return  a distance from a source cell to a current cell.
 */
size_t getDistance(struct queue *q)
{
    struct elt *e;
    assert(!queueEmpty(q));

    return q->head->distance;
}


/**
 * Function removes element from front of queue.
 * @param q  - a queue.
 */
void removeFirst (struct queue *q)
{
    struct elt *e;
    assert(!queueEmpty(q));

    /* patch out first element */
    e = q->head;
    q->head = e->next;
    free(e);
}
