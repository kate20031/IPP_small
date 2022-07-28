#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "charArray.h"
#include "simulation.h"
#include <stddef.h>
#include <stdint.h>



void handleError(int index) {
    FILE *fileError;
    fileError  = fopen ("file.err", "w");
    fprintf(fileError, "ERROR %d\n", index);
    fclose(fileError);
    if (index == 0) {
        exit(1);
    }
}


bool checkArraysLength(Array *startArray, Array *endArray, Array *dimensionArray) {
    if (getLength(startArray) != getLength(dimensionArray)) {
        handleError(2);
        return false;
    }
    if (getLength(endArray) != getLength(dimensionArray)) {
        handleError(3);
        return false;
    }
    return true;
}


void checkDimensions(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions, int *err, FILE *fptr) {
    size_t max = SIZE_MAX;

    for (size_t i = 0; i < getLength(dimensionArray); i++) {
        max /= getElementFromArray(dimensionArray, i);
        if (max < 1) {
            deleteArray(dimensionArray);
            deleteArray(startArray);
            deleteArray(endArray);
            deleteArrayChar(bitPositions);
            fclose(fptr);
            handleError(0);
            *err = 1;
            return;
        }
    }
}


static bool checkNumberOfWalls(charArray *bitPositions, Array *dimensionArray) {
    size_t lastBit = 0;
    size_t bitPosSize = getLengthChar(bitPositions);
    size_t dimSize = getLength(dimensionArray);
    size_t size;
    for (size_t i = 0; i < bitPosSize; i++) {
        if (getBit(bitPositions, i) == 1) {
            lastBit = bitPosSize - i;
            break;
        }
    }
    size = (dimSize == 0) ? 0 : 1;

    for (size_t i = 0; i < dimSize; i++) {
        size *= getElementFromArray(dimensionArray, i);
    }
    if (size < lastBit) {
        handleError(4);
        return false;
    }
    return true;
}


void checkVolume(charArray *bitPositions, size_t volume, int *err) {
    for (size_t i = getLengthChar(bitPositions) * 4 - 1; i >= volume; i--) {
        if (getBit(bitPositions, i) == 1) {
            *err = 1;
            break;
        }
    }
}


static bool checkNumberOfLines(FILE *fptr) {
    char *extraLine = NULL;
    size_t bufferSize = 0;
    size_t lineLength = getline(&extraLine, &bufferSize, fptr);

    if (lineLength != (size_t) -1) {
        handleError(5);
        free(extraLine);
        return false;
    }
    free(extraLine);
    return true;
}


static bool checkStartEnd(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions) {

    size_t volume = findVolume(dimensionArray);
    size_t start = convertIndex(startArray, dimensionArray);
    size_t end = convertIndex(endArray, dimensionArray);

    if (start >= volume) {
        handleError(2);
        return false;
    }
    if (end >= volume) {
        handleError(3);
        return false;
    }
    if (getBit(bitPositions, start) == 1) {
        handleError(2);
        return false;
    }
    if (getBit(bitPositions, end) == 1) {
        handleError(3);
        return false;
    }
    return true;
}


bool checkRInput(Array *numbers, int *err) {
    for (size_t i = 0; i < getLength(numbers); i++) {
        if (getElementFromArray(numbers, i) > UINT32_MAX) {
            *err = 1;
            return false;
        }
    }

    if (getElementFromArray(numbers, 2) == 0) {
        *err = 1;
        return false;
    }
    return true;
}


void checkInput(Array *array, int *err) {
    for (size_t i = 0; i < getLength(array); i++) {
        if (getElementFromArray(array, i) == 0) {
            *err = 1;
            return;
        }
    }
}


bool checkErrors(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions, FILE *fptr) {

    bool ok = checkArraysLength(startArray, endArray, dimensionArray);

    if (ok) {
        ok = checkNumberOfWalls(bitPositions, dimensionArray);
    }
    if (ok) {
        ok = checkNumberOfLines(fptr);
    }
    if (ok) {
        ok = checkStartEnd(dimensionArray, startArray, endArray, bitPositions);
    }
    return ok;
}