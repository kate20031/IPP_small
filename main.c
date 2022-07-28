#include <stdio.h>
#include <stdbool.h>
#include "input.h"
#include "simulation.h"
#include "errors.h"


int main(__attribute__((unused)) int argc, char* argv[]) {

    int err = 0;
    Array *dimensionArray = createArray();
    Array *startArray = createArray();
    Array *endArray = createArray();
    charArray *bitPositions = createArrayChar();
    bool ok = false;
    FILE *fptr = fopen(argv[1],"r");
    FILE *fileOut;
    readInput(dimensionArray, startArray, endArray, bitPositions, &err, fptr);
    if (err == 0) {
        ok = checkErrors(dimensionArray, startArray, endArray, bitPositions, fptr);
    }

    if (ok) {
        FILE *fileErr;
        fileErr  = fopen ("file.err", "w");
        fclose(fileErr);
        size_t result = findPath(bitPositions, dimensionArray, startArray, endArray, fptr);

        fileOut = fopen ("file.out", "w");
        if (result == (size_t) (-1)) {
            fprintf(fileOut, "NO WAY\n");
        } else if (result != (size_t) (-2)) {
            fprintf(fileOut, "%ld\n", result);
        }
        fclose(fileOut);
    }

    fclose(fptr);
    deleteArray(dimensionArray);
    deleteArray(startArray);
    deleteArray(endArray);
    deleteArrayChar(bitPositions);

    return 0;
}