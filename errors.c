
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "errors.h"
#include "charArray.h"

void handleError(int index) {
    fprintf(stderr, "ERROR %d\n", index);
    if (index == 0) exit(1);
}


bool checkArraysLength(Array* startArray, Array* endArray, Array* dimensionArray) {
    if (getLength(startArray) != getLength(dimensionArray)) {
        handleError( 2);
        return false;
    }
    if (getLength(endArray) != getLength(dimensionArray)) {
        handleError( 3);
        return false;
    }
    return true;
}


bool checkDimensions(Array* dimensionArray) {
    size_t difference = ULLONG_MAX;
    for (size_t i = 0; i < getLength(dimensionArray); i++) {
        difference /= getElementFromArray(dimensionArray, i);
        if (difference < 1) {
            handleError( 0);
            return false;
        }
    }
    return true;
}


static bool checkNumberofWalls(charArray* bitPositions, Array* dimensionArray) {
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
    size = (dimSize == 0)? 0 : 1;

    for (size_t i = 0; i < dimSize; i++) {
        size *= getElementFromArray(dimensionArray, i);
    }
    if (size < lastBit) {
        handleError(4);
        return false;
    }
    return true;
}


bool checkStartEnd(size_t start, size_t end, charArray* bitPositions, size_t volume) {
    if (start < 0) {
        handleError(2);
        return false;
    }
    if (end >= volume) {
        handleError(3);
        return false;
    }

    if (getBit(bitPositions, start) == 1)    {
        handleError(2);
        return false;
    }
    else if (getBit(bitPositions, end) == 1) {
        handleError(3);
        return false;
    }
    return true;
}

void checkNoOutOfBounds(charArray* bitPositions, size_t volume, int* err) {
    for (size_t i = getLengthChar(bitPositions)*4 - 1; i >= volume ; i--) {
        if (getBit(bitPositions, i) == 1) {
            *err = 1;
            break;
        }
    }
}


static bool checkNumberOfLines() {
    char* extraLine = NULL;
    size_t bufferSize = 0;
    ssize_t lineLength = getline(&extraLine, &bufferSize, stdin);
    if (lineLength != -1) {
        handleError(5);
        free(extraLine);
        return false;
    }
    free(extraLine);
    return true;
}


bool checkErrors(Array* dimensionArray, Array* startArray, Array* endArray,
                 charArray* bitPositions, size_t start, size_t end) {

    bool ok =  checkArraysLength(startArray, endArray, dimensionArray);

    if (ok) {
        ok = checkNumberofWalls(bitPositions, dimensionArray);
    }
    if (ok) {
        ok = checkNumberOfLines();
    }
    return ok;
}