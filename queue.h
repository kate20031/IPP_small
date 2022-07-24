//
// Created by acer on 19.07.22.
//

#ifndef UNTITLED1_QUEUE_H
#define UNTITLED1_QUEUE_H

#include <assert.h>

struct queue;

struct elt;

struct queue* queueCreate(void);

void addToQueue(struct queue *q, size_t index, size_t distance);

int queueEmpty(const struct queue *q);

size_t getIndex(struct queue *q);

size_t getDistance(struct queue *q);

void removeFirst (struct queue *q);

#endif //UNTITLED1_QUEUE_H
