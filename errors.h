#ifndef UNTITLED1_ERRORS_H
#define UNTITLED1_ERRORS_H

#include "array.h"
#include "charArray.h"
#include "input.h"


void handleError(int index);

void checkArraysLength(Array *array, Array *dimensionArray, int* err);

void checkDimensions(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions, int *err);

void checkVolume(charArray *bitPositions, size_t volume, int *err);

bool checkRInput(Array *numbers, int *err);

void checkInput(Array *array, int *err);

void checkStartEndBounds(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions);

bool checkErrors(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions);

void safeExit(Array *dimensionsArray, Array *startArray, Array *endArray,
              charArray* bitPositions, int index);

#endif //UNTITLED1_ERRORS_H
