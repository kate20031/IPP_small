#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include "simulation.h"
#include "charArray.h"
#include "errors.h"



/**
 * Function which finds volume of maze.
 * @param dimensionArray – an array of dimensions.
 * @return volume of maze.
 */
size_t findVolume(Array *dimensionArray) {
    size_t dimSize = getLength(dimensionArray);
    size_t volume = (dimSize == 0) ? 0 : 1;
    for (size_t i = 0; i < dimSize; i++) {
        volume *= getElementFromArray(dimensionArray, i);
    }
    return volume;
}


/**
 * Function converts coordinates to index.
 * Function converts coordinates of cell to index(decimal) of position in maze.
 * @param coordinates - coordinates of the cell.
 * @param dimensionArray - array of maze dimensions.
 * @return index
 */
size_t convertIndex(Array *coordinates, Array *dimensionArray) {
    size_t index = 0;
    size_t product = 1;

    for (size_t i = 0; i < getLength(dimensionArray); i++) {
        index += product * (getElementFromArray(coordinates, i) - 1);
        product *= getElementFromArray(dimensionArray, i);
    }
    return index;
}


/**
 * Convert index of cell to the array of coordinates.
 * Reverse function of "convertIndex".
 * @param index – index of cell.
 * @param coordinatesArray  - array of coordinates.
 * @param dimensionArray - array of maze dimensions.
 */
void convertIndexRev(size_t index, size_t *coordinatesArray, Array *dimensionArray) {
    size_t rest;

    if (getLength(dimensionArray) == 1) {
        coordinatesArray[0] = index + 1;
    } else {
        for (size_t i = 0; i < getLength(dimensionArray); i++) {
            rest = index % getElementFromArray(dimensionArray, i);
            coordinatesArray[i] = rest + 1;
            index -= rest;
            index /= getElementFromArray(dimensionArray, i);
        }
    }
}


/**
 * Checking if it's possible to go to the neighbouring field from the current position.
 * @param mazeDimension - dimension of maze.
 * @param bitPositions  – the array(hex) with stores info if cells are empty.
 * @param visited -  an array of (0/1) to keep track of visited cells.
 * @param aim - a cell, which will be checked.
 * @return - true, if it's safe to go to the "aim" cell,
 *  * false - otherwise.
 */
static bool isSafe(size_t mazeDimension, charArray *bitPositions, charArray *visited, size_t aim) {
    return (aim < mazeDimension) && (getBit(bitPositions, aim) == 0) && (getBit(visited, aim) == 0);
}


/**
 * Checking if the cell isn't out of maze border.
 * @param dimensionsArray – an array of dimensions.
 * @param cell - a source cell.
 * @param moveToLeft – true if move is to left, false - to right.
 * @param index - index of bit of the source cell.
 * @return - true, if the cell is out of border,
 * false - otherwise.
 */
static bool outMazeBorder(Array *dimensionsArray, size_t cell, bool moveToLeft, size_t index) {
    size_t *coordinates = malloc(sizeof(size_t) * getLength(dimensionsArray));
    convertIndexRev(cell, coordinates, dimensionsArray);

    if (((coordinates[index] == getElementFromArray(dimensionsArray, index)) && !moveToLeft)
        || (coordinates[index] == 1 && moveToLeft)) {
        free(coordinates);
        return true;
    }
    free(coordinates);
    return false;
}


/**
 *
 * @param bitPositions – the array(hex) with stores info if cells are empty.
 * @param dimensionsArray – the dimensions array of maze.
 * @param startArray – the coordinates array of source cell.
 * @param endArray – the coordinates array of destination cell.
 * @return the length of shortest path, if exists,
 *          (-1) – otherwise.
 */
size_t findPath(charArray *bitPositions, Array *dimensionsArray, Array *startArray, Array *endArray) {
    size_t dimSize = getLength(dimensionsArray);
    size_t volume = findVolume(dimensionsArray);
    size_t start = convertIndex(startArray, dimensionsArray);
    size_t end = convertIndex(endArray, dimensionsArray);
    char *testAllocation = malloc(sizeof(char) * volume / 4);
    if (testAllocation == NULL) {
        safeExit(dimensionsArray, startArray, endArray, bitPositions, 0);
        return -2;
    }
    free(testAllocation);

    charArray *visited = createArrayChar();

    for (size_t i = 0; i < volume / 4; i++) {
        pushBackChar(visited, '0');
    }

    if (visited == NULL) {
        safeExit(dimensionsArray, startArray, endArray, bitPositions, 0);
        return -2;
    }
    size_t minDistance = INT64_MAX;

    struct queue *q;
    q = queueCreate();
    setBit(visited, start);
    addToQueue(q, start, 0);

    while (!queueEmpty(q)) {

        size_t index = getIndex(q);
        size_t distance = getDistance(q);

        removeFirst(q);

        if (index == end) {
            minDistance = distance;
            break;
        }
        size_t neighbor = 1;
        for (size_t i = 0; i < dimSize; i++) {

            if (isSafe(volume, bitPositions, visited, index + neighbor) &&
                !outMazeBorder(dimensionsArray, index, false, i)) {
                setBit(visited, index + neighbor);
                addToQueue(q, index + neighbor, distance + 1);
            }
            if (isSafe(volume, bitPositions, visited, index - neighbor) &&
                !outMazeBorder(dimensionsArray, index, true, i)) {
                setBit(visited, index - neighbor);
                addToQueue(q, index - neighbor, distance + 1);
            }
            neighbor *= getElementFromArray(dimensionsArray, i);
        }
    }
    deleteQueue(q);
    deleteArrayChar(visited);
    if (minDistance != INT64_MAX) {
        return minDistance;
    }
    return -1;
}