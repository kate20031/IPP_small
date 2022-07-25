#include <stdio.h>
#include <stdbool.h>
#include "input.h"
#include "simulation.h"
#include "errors.h"


int main(){

    int err = 0;
    Array* dimensionArray = createArray();
    Array* startArray = createArray();
    Array* endArray = createArray();
    charArray* bitPositions = createArrayChar();
    size_t volume;
    size_t start;
    size_t end;

    bool ok = readInput(dimensionArray, startArray, endArray, bitPositions, &err) &&
    checkErrors(dimensionArray, startArray, endArray, bitPositions);

    if (ok) {
        volume = findVolume(dimensionArray);
        start = convertIndex(startArray, dimensionArray);
        end = convertIndex(endArray, dimensionArray);


        ok =  checkStartEnd(start, end, bitPositions, volume);
        if (ok) {
            size_t result = findPath(bitPositions, dimensionArray, start, end);

            if (result == (size_t)-1) {
                printf("NO WAY\n");
            } else if (result != (size_t)-2) {
                printf("%ld\n", result);
            }
        }
    }

    deleteArray(dimensionArray);
    deleteArray(startArray);
    deleteArray(endArray);
    deleteArrayChar(bitPositions);

    return 0;
}