#include "charArray.h"
#include "errors.h"
#include <malloc.h>
#include <stddef.h>
#include "input.h"


struct charArray {
    size_t length;
    size_t memory;
    char *v;
};
typedef struct charArray charArray;


charArray *createArrayChar() {
    charArray *array = malloc(sizeof(charArray));
    if (array == NULL) {
        return array;
    }
    array->v = malloc(sizeof(char));
    if (array->v == NULL) {
        free(array);
        return NULL;
    }

    array->length = 0;
    array->memory = 1;
    return array;
}


void pushBackChar(charArray *array, char element) {
    if (array->memory == array->length) {
        array->v = realloc(array->v, sizeof(char) * array->memory * 2);
        if (array->v == NULL) {
            handleError(0);
        }
        array->memory *= 2;
    }
    array->v[array->length] = element;
    array->length += 1;
}


void deleteArrayChar(charArray *array) {
    free(array->v);
    free(array);
}


char getElementFromArrayChar(charArray *array, size_t index) {
    if (index >= getLengthChar(array)) return ' ';
    return (array->v)[index];
}


size_t getLengthChar(charArray *array) {
    return array->length;
}


int getBit(charArray *array, size_t index) {
    char number;

    if (index / 4 < getLengthChar(array)) {
        number = getElementFromArrayChar(array, getLengthChar(array) - 1 - index / 4);
    } else {
        return 0;
    }
    int numberDex = hexToInt(number);
    return ((1 << (index % 4) & numberDex) >> (index % 4));
}


static char *getBinary(size_t number) {
    char *temp = malloc(sizeof(char) * 4);
    int size = 0;

    for (int bit = 1 << 3; bit != 0; bit >>= 1) {
        temp[size++] = (number & bit) ? '1' : '0';
    }
    return temp;
}


static char intToHex(int x) {
    if (x >= 0 && x <= 9) {
        return (char) (x + '0');
    } else if (x >= 10 && x <= 15) {
        return (char) (x - '0' + 135);
    }
    return ' ';
}


/**
 * Function convert index of cell from decimal to hex.
 * Function convert decimal index to hex number,
 * so that one hex char in "bitPositions" array tells
 * about 4 cells.
 * @param rest - rest of division index by 4.
 * @param index - decimal index of cell.
 * @param bitPositions - an array(binary) with stores info if cells are empty.
 * @return  hex index of cell(char).
 */
char indexToHex(size_t rest, size_t index, charArray *bitPositions) {
    int number = 0;
    char previousElem = getElementFromArrayChar(bitPositions, getLengthChar(bitPositions) - 1 - index);
    char *prevBinary = getBinary(hexToInt(previousElem));
    char *currBinary = getBinary( 1 << rest);

    for (int i = 3; i >= 0; i--) {
        if ((prevBinary[i] == '1') || (currBinary[i]  == '1')) {
              number+= 1 << (3 - i);
        }
    }
    free(prevBinary);
    free(currBinary);
    return intToHex(number);
}


void setBit(charArray *array, size_t index) {
    size_t newIndex = (index / 4);
    char hex = indexToHex(index % 4, newIndex, array);
    if (newIndex < getLengthChar(array)) {
        array->v[getLengthChar(array) - 1 - newIndex] = hex;
    }
}