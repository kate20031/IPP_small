#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include "simulation.h"
#include "charArray.h"
#include "errors.h"


/**
 * Function which finds volume of maze.
 * @param dimensions - array of maze dimensions
 * @param dimSize – size of "dimensions" array.
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


size_t convertIndex(Array *index, Array *dimensionArray) {
    size_t newIndex = 0;
    size_t product = 1;

    for (size_t i = 0; i < getLength(dimensionArray); i++) {
        newIndex += product * (getElementFromArray(index, i) - 1);
        product *= getElementFromArray(dimensionArray, i);
    }
    return newIndex;
}


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
 * @param maze - maze in binary representation
 * @param visited -  an array of (0/1) to keep track of visited cells.
 * @param aim - a cell, which will be checked.
 * @return - true, if it's safe to go to the "aim" cell,
 * false - otherwise,
 */
static bool isSafe(size_t mazeDimension, charArray *bitPositions, charArray *visited, size_t aim) {
    return (aim < mazeDimension) && (getBit(bitPositions, aim) == 0) && (getBit(visited, aim) == 0);
}


/**
 * Checking if the cell isn't out of maze border.
 * @param dimensionsArray – an array of dimensions.
 * @param dimSize - size of "dimensionsArray".
 * @param cell - a source cell.
 * @param neighbor - a destination cell.
 * @param index - index of bit of the source cell.
 * @return - true, if the cell is out of border,
 * false - otherwise.
 */
static bool outMazeBorder(Array *dimensionsArray, size_t cell, long long neighbor, size_t index) {
    size_t *coordinates = malloc(sizeof(size_t) * getLength(dimensionsArray));
    convertIndexRev(cell, coordinates, dimensionsArray);

    if ((coordinates[index] == getElementFromArray(dimensionsArray, index)) && neighbor > 0) {
        free(coordinates);
        return true;
    }
    if (coordinates[index] == 1 && neighbor < 0) {
        free(coordinates);
        return true;
    }
    free(coordinates);
    return false;
}


/**
 * Function which search the shortest path in maze
 * @param bitPositions - an array(binary) with stores info if cells are empty.
 * @param bitPosSize - size of "bitPositions" array.
 * @param mazeDimension – dimension of maze.
 * @param dimensionsArray – an array of dimensions.
 * @param dimSize - size of "dimensionsArray".
 * @param start - source cell in maze.
 * @param end - destination cell in maze.
 * @return the length of shortest path, if exists,
 *          -1 – otherwise.
 */
size_t findPath(charArray *bitPositions, Array *dimensionsArray, size_t start, size_t end) {
    size_t dimSize = getLength(dimensionsArray);
    size_t volume = findVolume(dimensionsArray);
    charArray *visited = createArrayChar();

    if (visited == NULL) {
        handleError(0);
        return -2;
    }
    size_t minDistance = INT64_MAX;

    for (size_t i = 0; i < volume / 4; i++) {
        pushBackChar(visited, '0');
    }

    queue *q;
    q = queueCreate();
    setBit(visited, end);
    addToQueue(q, start, 0);

    while (!queueEmpty(q)) {

        size_t index = getIndex(q);
        size_t distance = getDistance(q);

        removeFirst(q);

        if (index == end) {
            minDistance = distance;
            break;
        }
        long long neighbor = 1;
        for (size_t i = 0; i < dimSize; i++) {

            if (isSafe(volume, bitPositions, visited, index + neighbor) &&
                !outMazeBorder(dimensionsArray, index, neighbor, i)) {
                setBit(visited, index + neighbor);
                addToQueue(q, index + neighbor, distance + 1);
            }
            if (isSafe(volume, bitPositions, visited, index - neighbor) &&
                !outMazeBorder(dimensionsArray, index, -1 * neighbor, i)) {
                setBit(visited, index - neighbor);
                addToQueue(q, index - neighbor, distance + 1);
            }
            neighbor *= getElementFromArray(dimensionsArray, i);
        }
    }
    deleteQueue(q);
    free(visited);
    if (minDistance != INT64_MAX) {
        return minDistance;
    }
    return -1;
}
