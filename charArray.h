#ifndef UNTITLED1_CHARARRAY_H
#define UNTITLED1_CHARARRAY_H

#include <glob.h>
#include <stdbool.h>
#include <stddef.h>

struct charArray;
typedef struct charArray charArray;


charArray* createArrayChar();

void pushBackChar(charArray* array, char element);

void deleteArrayChar(charArray* array);

char getElementFromArrayChar(charArray* array, size_t index);

size_t getLengthChar(charArray* array);

size_t getBit(charArray* array, size_t index);

void setBit(charArray* array, size_t index);

char indexToHex(size_t rest, size_t index, charArray* bitPositions);


#endif //UNTITLED1_CHARARRAY_H
