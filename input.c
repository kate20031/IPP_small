#define _POSIX_C_SOURCE 200809L#include <stddef.h>#include <stdio.h>#include <stdlib.h>#include <stdbool.h>#include <ctype.h>#include <errno.h>#include <stdint.h>#include "input.h"#include "errors.h"#include "simulation.h"static char intToHex(int x) {    if (x >= 0 && x <= 9) {        return (char)(x + '0');    }    else if (x >= 10 && x <= 15) {        return (char)(x - 'a' + 10);    }    return ' ';}int hexToInt(char c) {    if (c >= '0' && c <= '9') {        return c - '0';    }    else if (c >= 'a' && c <= 'f') {        return c - 'a' + 10;    }    else if (c >= 'A' && c <= 'F') {        return c - 'A' + 10;    }    return -1;}static char* getBinary(size_t number) {    char* temp = malloc(sizeof (char ) * 4);    int size = 0;    for (int bit = 1 << 3; bit != 0; bit >>= 1) {        temp[size++] = (number & bit) ? '1' : '0';    }    return temp;}static int power(int y) {    int product = 1;    for (int i = 0; i < y; i++) {        product *= 2;    }    return product;}char binToHex(size_t rest, size_t index, charArray* bitPositions) {    int number = 0;    char previousElem = getElementFromArrayChar(bitPositions, index);    char* currBinary = getBinary(hexToInt(previousElem));    currBinary[3-rest] = 1;    for (int i = 3; i >= 0; i--) {        if (currBinary[i] == 1) {            number += power(3 - i);        }    }    free(currBinary);    return intToHex(number);}static charArray * scanChar(charArray* array, const char* line, size_t index, int* err) {    char sign;    do {        sign = line[index];        if (isspace(sign) == 0) {            if (hexToInt(sign) == -1) {                *err = 1;                break;            }            pushBackChar(array, sign);        }        index++;    } while (sign != '\n');    return array;}static void scanLine(char** line, int *err) {    size_t bufferSize = 0;    size_t lineLength = getline(line, &bufferSize, stdin);    if (errno == ENOMEM){        handleError(0);    }    if (lineLength == (size_t)-1 ){        *err = 1;        free(*line);    }}static void scanToArrayAdd(Array *arr, int *err, bool afterR, char* line) {    size_t i = 0;    size_t number;    if (*err == 1) return;    while (line[i] != '\n' && line[i] != EOF) {        while (isspace(line[i]) && line[i] != '\n' && line[i] != EOF) {            i++;        }        if (isdigit(line[i])) {            number = strtoull(line + i, NULL, 10);            if (errno == ERANGE || (number == 0 && !afterR) || (afterR && (number > UINT32_MAX))) {                *err = 1;                break;            }            pushBack(arr, number);        } else if (line[i] == '\n' || line[i] == EOF) {            if (getLength(arr) == 0) {                *err = 1;            }            break;        } else {            *err = 1;            break;        }        while (isdigit(line[i])) i++;    }    if (getLength(arr) == 0) {        *err = 1;    }    if (!afterR) {        free(line);    }}static void scanToArray(Array *arr, int *err, bool afterR) {    char *line = NULL;    scanLine(&line, err);    scanToArrayAdd(arr, err, afterR, line);}static void convertRToBinary(Array* rests, size_t volume, charArray* bitPositions) {    long long difference;    for (size_t i = 0; i < volume; i++) {        pushBackChar(bitPositions, '0');    }    for (size_t i = 1; i < getLength(rests); i++) {        size_t element = getElementFromArray(rests, i);        difference = volume - element;        while (difference >= 0) {            setBit(bitPositions, element);            difference -= UINT32_MAX;            element += UINT32_MAX;        }    }}static void convertRNumber(Array* numbers, charArray* bitPositions, Array* dimensionArray, int* err) {    if (*err == 1) return;    size_t a, b, m, s_0, r;    size_t product;    a = getElementFromArray(numbers, 0);    b = getElementFromArray(numbers, 1);    m = getElementFromArray(numbers, 2);    r = getElementFromArray(numbers, 3);    s_0 = getElementFromArray(numbers, 4);     if (m == 0) {         *err = 1;         return;     }     Array*  s = createArray();     Array*  rests = createArray();     pushBack(s, s_0);     for (size_t i = 1; i <= r; i++) {         size_t result = (a * getElementFromArray(s, i-1) + b) % m;         pushBack(s, result);     }     pushBack(rests, 0);     product = findVolume(dimensionArray);     for (size_t i = 1; i <= r; i++) {         pushBack(rests, getElementFromArray(s, i) % product);     }     size_t volume = findVolume(dimensionArray);     convertRToBinary(rests, volume, bitPositions);     deleteArray(s);     deleteArray(rests);}static void scanAndConvert(charArray* bitPositions, Array* dimensionArray, int* err) {    char *line = NULL;    size_t i = 0;    bool hasZero = false;    scanLine(&line, err);    if (*err == 1) return;    while (line[i] != '\n' && line[i] != EOF) {        while (isspace(line[i]) || line[i] == '0') {            if (line[i] == '0') {                hasZero = true;            }            i++;        }        if (line[i] == 'R') {            Array* numbers = createArray();            bool afterR = true;            scanToArrayAdd(numbers, err, afterR, line + i + 1);            if (getLength(numbers) != 5) {                *err = 1;                deleteArray(numbers);                break;            }            convertRNumber(numbers, bitPositions, dimensionArray, err);            deleteArray(numbers);            break;        } else if (line[i] == 'x' && hasZero) {            i++;            scanChar(bitPositions, line, i, err);            checkNoOutOfBounds(bitPositions, findVolume(dimensionArray), err);            break;        } else if (line[i] == '\n') {            if (getLengthChar(bitPositions) == 0) {                *err = 1;            }            break;        } else {            *err = 1;            break;        }    }    free(line);}size_t convertIndex(Array* index, Array* dimensionArray) {    size_t newIndex = 0;    size_t product = 1;    for (size_t i = 0; i < getLength(dimensionArray); i++) {        newIndex += product * (getElementFromArray(index, i) - 1);        product *= getElementFromArray(dimensionArray, i);    }    return newIndex;}void convertIndexRev(size_t index, size_t* coordinatesArray, Array* dimensionArray) {    size_t rest;    if (getLength(dimensionArray) == 1) {        coordinatesArray[0] = index + 1;    }    else {        for (size_t i = 0; i < getLength(dimensionArray); i++) {            rest = index % getElementFromArray(dimensionArray, i);            coordinatesArray[i] = rest + 1;            index -= rest;            index /= getElementFromArray(dimensionArray, i);        }    }}bool readInput(Array *dimensionArray, Array *startArray, Array *endArray, charArray *bitPositions, int *err){    scanToArray(dimensionArray, err, false);    checkDimensions(dimensionArray);    if (*err == 1) {        handleError(1);        return false;    }    scanToArray(startArray, err, false);    if (*err == 1) {        handleError(2);        return false;    }    scanToArray(endArray, err, false);    if (*err == 1) {        handleError(3);        return false;    }    scanAndConvert(bitPositions, dimensionArray, err);    if (*err == 1) {        handleError(4);        return false;    }    return true;}