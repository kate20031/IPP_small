#ifndef UNTITLED1_QUEUE_H
#define UNTITLED1_QUEUE_H

#include <assert.h>

struct queue;
typedef struct queue queue;

struct elt;
typedef struct elt elt;

queue* queueCreate(void);

void addToQueue(queue *q, size_t index, size_t distance);

int queueEmpty(const queue *q);

size_t getIndex(queue *q);

size_t getDistance(queue *q);

void removeFirst (queue *q);

void deleteQueue(queue *q);

#endif //UNTITLED1_QUEUE_H
