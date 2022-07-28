#ifndef _INPUT_H
#define _INPUT_H

#include <stddef.h>
#include "array.h"
#include "charArray.h"
#include <stdbool.h>
#include <stdio.h>


void readInput(Array *dimensionsArray, Array *startArray, Array *endArray, charArray *bitPositions, int *err, FILE *fptr);

void convertIndexRev(size_t index, size_t *coordinatesArray, Array *dimensionArray);

int hexToInt(char c);

#endif //_INPUT_H
