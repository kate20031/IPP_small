#ifndef UNTITLED1_ERRORS_H
#define UNTITLED1_ERRORS_H

#include "array.h"
#include "charArray.h"
#include "input.h"


void handleError(int index);

bool checkArraysLength(Array *startArray, Array *endArray, Array *dimensionArray);

void checkDimensions(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions, int *err, FILE *fptr);

void checkVolume(charArray *bitPositions, size_t volume, int *err);

bool checkRInput(Array *numbers, int *err);

void checkInput(Array *array, int *err);

bool checkErrors(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions, FILE *fptr);


#endif //UNTITLED1_ERRORS_H
