#ifndef UNTITLED1_SIMULATION_H
#define UNTITLED1_SIMULATION_H

#include <glob.h>
#include "array.h"
#include "charArray.h"
#include "queue.h"
#include "input.h"

size_t findVolume(Array *dimensionArray);

size_t findPath(charArray *bitPositions, Array *dimensionsArray, Array *startArray, Array *endArray);

size_t convertIndex(Array *coordinates, Array *dimensionArray);

void convertIndexRev(size_t index, size_t *coordinatesArray, Array *dimensionArray);

#endif //UNTITLED1_SIMULATION_H
