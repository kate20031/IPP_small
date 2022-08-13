#ifndef _INPUT_H
#define _INPUT_H

#include <stddef.h>
#include "array.h"
#include "charArray.h"
#include <stdbool.h>
#include <stdio.h>
#define _POSIX_C_SOURCE 200809L

void readInput(Array *dimensionsArray, Array *startArray, Array *endArray, charArray *bitPositions, int *err);

int hexToInt(char c);

#endif //_INPUT_H
