//
// Created by acer on 21.07.22.
//

#ifndef UNTITLED1_SIMULATION_H
#define UNTITLED1_SIMULATION_H

#include <glob.h>
#include "array.h"
#include "charArray.h"
#include "queue.h"
#include "input.h"

size_t findVolume(Array* dimensionArray);

size_t findPath (charArray* bitPositions, Array* dimensionsArray, size_t start, size_t end);

#endif //UNTITLED1_SIMULATION_H
