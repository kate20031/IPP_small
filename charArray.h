#ifndef UNTITLED1_CHARARRAY_H
#define UNTITLED1_CHARARRAY_H

#include <glob.h>
#include <stdbool.h>

struct charArray;
typedef struct charArray charArray;

charArray* createArrayChar();

charArray* createArrayCharR();

void pushBackChar(charArray* array, char element);

void deleteArrayChar(charArray* array);

char getElementFromArrayChar(charArray* array, size_t index);

size_t getLengthChar(charArray* array);

size_t getBit(charArray* array, size_t index);

void setBit(charArray* array, size_t index);

void printArray(charArray* array);

//bool isAfterR(charArray* array);

#endif //UNTITLED1_CHARARRAY_H
