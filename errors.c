#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "charArray.h"
#include "simulation.h"
#include <stddef.h>
#include <stdint.h>



/**
 * Function writes the error to output "file.err".
 * Function writes the error to output "file.err" and
 * exits.
 * @param index – index of the error.
 */
void handleError(int index) {
    fprintf(stderr, "ERROR %d\n", index);
    if (index == 0) {
        exit(1);
    }
}


void safeExit(Array *dimensionsArray, Array *startArray, Array *endArray,
              charArray *bitPositions, int error) {
    deleteArray(dimensionsArray);
    deleteArray(startArray);
    deleteArray(endArray);
    deleteArrayChar(bitPositions);
    handleError(error);
    exit(1);
}


/**
 * unction checks if length of coordinates array is the same dimensions'.
 * @param array – array to check.
 * @param dimensionArray – the dimensions array of maze.
 * @param err – pointer to variable of error.
 */
void checkArraysLength(Array *array, Array *dimensionArray, int *err) {
    if (getLength(array) != getLength(dimensionArray)) {
        *err = 1;
    }
}


/**
 * Checks if dimension of maze is smaller than SIZE_MAX.
 * @param dimensionArray – an array of dimensions.
 * @param startArray – the coordinates array of source cell.
 * @param endArray – the coordinates array of destination cell.
 * @param bitPositions – the array(hex) with stores info if cells are empty.
 * @param err - the pointer to an error variable.
 */
void checkDimensions(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions, int *err) {
    size_t max = SIZE_MAX;

    for (size_t i = 0; i < getLength(dimensionArray); i++) {
        max /= getElementFromArray(dimensionArray, i);
        if (max < 1) {
            safeExit(dimensionArray, startArray, endArray, bitPositions, 0);
            *err = 1;
            return;
        }
    }
}


/**
 * Function checks if there is no full cell out of bounds.
 * @param bitPositions – the array(hex) with stores info if cells are empty.
 * @param dimensionArray – the dimensions array of maze.
 * @return false - if full cell out of bounds was found.
 *          true – otherwise.
 */
static bool checkFullCells(charArray *bitPositions, Array *dimensionArray) {
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


/**
 * Function checks if there is no full cell out of bounds.
 * Function checks if there is no full cell out of bounds
 * in array, which stores info about maze's cells (bitPositions).
 * @param bitPositions – the array(hex) with stores info if cells are empty.
 * @param volume – volume of maze.
 * @param err - the pointer to an error variable.
 */
void checkVolume(charArray *bitPositions, size_t volume, int *err) {
    for (size_t i = getLengthChar(bitPositions) * 4 - 1; i >= volume; i--) {
        if (getBit(bitPositions, i) == 1) {
            *err = 1;
            break;
        }
    }
}


/**
 * Function checks if input contains only 4 lines.
 * @return false if there is more than 4 lines.
 *          true – otherwise.
 */
static bool checkNumberOfLines() {
    char *extraLine = NULL;
    size_t bufferSize = 0;
    size_t lineLength = getline(&extraLine, &bufferSize, stdin);

    if (lineLength != (size_t) -1) {
        handleError(5);
        free(extraLine);
        return false;
    }
    free(extraLine);
    return true;
}

/**
 * Function checks if start end end (2nd and 3rd lines) cell are no out of bounds.
 * @param dimensionArray – the dimensions array of maze.
 * @param startArray – the coordinates array of source cell.
 * @param endArray – the coordinates array of destination cell.
 * @param bitPositions – the array(hex) with stores info if cells are empty.
 *
 */
void checkStartEndBounds(Array *dimensionArray, Array *startArray, Array *endArray,
                         charArray *bitPositions) {
    size_t volume = findVolume(dimensionArray);
    size_t start = convertIndex(startArray, dimensionArray);
    size_t end = convertIndex(endArray, dimensionArray);

    for (size_t i = 0; i < getLength(dimensionArray); i++) {
        if (getElementFromArray(startArray, i) > getElementFromArray(dimensionArray, i)) {
            safeExit(dimensionArray, startArray, endArray, bitPositions, 2);
        }
        if (getElementFromArray(endArray, i) > getElementFromArray(dimensionArray, i)) {
            safeExit(dimensionArray, startArray, endArray, bitPositions, 3);
        }
    }
    if (start >= volume) {
        safeExit(dimensionArray, startArray, endArray, bitPositions, 2);
        return;
    }
    if (end >= volume) {
        safeExit(dimensionArray, startArray, endArray, bitPositions, 3);
        return;
    }
}


/**
 * Function checks if start end end (2nd and 3rd lines) cell arent full
 * @param dimensionArray – the dimensions array of maze.
 * @param startArray – the coordinates array of source cell.
 * @param endArray – the coordinates array of destination cell.
 * @param bitPositions – the array(hex) with stores info if cells are empty.
 * @return false – if start/end is out of maze's bounds or its cell is full.
 *         true – otherwise.
 */
static bool checkStartEndFull(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions) {

    size_t start = convertIndex(startArray, dimensionArray);
    size_t end = convertIndex(endArray, dimensionArray);

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


/**
 * Function checks correctness of input of 4 line (if starts with R)
 * @param numbers - array of numbers read after R.
 * @param err - the pointer to an error variable.
 * @return - true, false, if number out of range was found or
 * if m is 0.
 * false – otherwise.
 */
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

/**
 * Function that checks correctness of 3 first lines input.
 * Function set pointer to 1 and returns
 * , if 0 was found in array.
 * @param array - array of signs.
 * @param err - pointer to error variable.
 */
void checkInput(Array *array, int *err) {
    for (size_t i = 0; i < getLength(array); i++) {
        if (getElementFromArray(array, i) == 0) {
            *err = 1;
            return;
        }
    }
}


/**
 * Function checks all possible errors.
 * @param dimensionArray – the dimensions array of maze.
 * @param startArray – the coordinates array of source cell.
 * @param endArray – the coordinates array of destination cell.
 * @param bitPositions – the array(hex) with stores info if cells are empty.
 * @return false – if error was found,
 *          true – otherwise.
 */
bool checkErrors(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions) {

    bool ok = checkFullCells(bitPositions, dimensionArray);
    if (ok) {
        ok = checkNumberOfLines();
    }
    if (ok) {
        ok = checkStartEndFull(dimensionArray, startArray, endArray, bitPositions);
    }
    return ok;
}