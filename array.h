//
// Created by acer on 19.07.22.
//

#ifndef UNTITLED1_ARRAY_H
#define UNTITLED1_ARRAY_H

struct Array;
typedef struct Array Array;

Array* createArray();

void pushBack(Array* array, size_t element);

void deleteArray(Array* array);

size_t getElementFromArray(Array* array, size_t index);

size_t getLength(Array *array);

void printArrayS(Array* array);


#endif //UNTITLED1_ARRAY_H