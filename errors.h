#ifndef UNTITLED1_ERRORS_H
#define UNTITLED1_ERRORS_H

#include "array.h"
#include "charArray.h"
#include "input.h"

void handleError(int index);

bool checkArraysLength(Array* startArray, Array* endArray, Array* dimensionArray);

bool checkDimensions(Array* dimensionArray);

//bool checkNumberofWalls(charArray* bitPositions, Array* dimensionArray);

bool checkStartEnd(size_t start, size_t end, charArray* bitPositions, size_t volume);

void checkNoOutOfBounds(charArray* bitPositions, size_t volume, int* err);

bool checkErrors(Array* dimensionArray, Array* startArray, Array* endArray, charArray* bitPositions);


#endif //UNTITLED1_ERRORS_H
