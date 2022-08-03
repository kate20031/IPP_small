#include <stdio.h>
#include <stdbool.h>
#include "input.h"
#include "simulation.h"
#include "errors.h"


int main() {

    int err = 0;
    Array *dimensionArray = createArray();
    Array *startArray = createArray();
    Array *endArray = createArray();
    charArray *bitPositions = createArrayChar();
    bool ok = false;

    readInput(dimensionArray, startArray, endArray, bitPositions, &err);
    if (err == 0) {
        ok = checkErrors(dimensionArray, startArray, endArray, bitPositions);
    }

    if (ok) {
        size_t result = findPath(bitPositions, dimensionArray, startArray, endArray);

        if (result == (size_t) (-1)) {
            fprintf(stdout, "NO WAY\n");
        } else if (result != (size_t) (-2)) {
            fprintf(stdout, "%ld\n", result);
        }
    }

    deleteArray(dimensionArray);
    deleteArray(startArray);
    deleteArray(endArray);
    deleteArrayChar(bitPositions);

    return 0;
}