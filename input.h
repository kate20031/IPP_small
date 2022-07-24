#ifndef _INPUT_H
#define _INPUT_H

#include <stddef.h>
#include "array.h"
#include "charArray.h"
#include <stdbool.h>

bool readInput(Array *dimensionsArray, Array *startArray, Array *endArray, charArray *bitPositions, int *err);

size_t convertIndex(Array* index, Array* dimensionArray);

void convertIndexRev(size_t index, size_t* coordinatsArray, Array* dimensionArray);

//void convertRToBinary(Array* rests, size_t volume, charArray* bitPositions);
//
//void scanLine(char** line, int *err);

int hexToInt(char c);

char binToHex(size_t rest, size_t index, charArray* bitPositions);

#endif //_INPUT_H
