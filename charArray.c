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


charArray* createArrayChar() {
    charArray* array = malloc(sizeof(charArray));
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


void pushBackChar(charArray* array, char element) {
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


void deleteArrayChar(charArray* array) {
    free(array->v);
    free(array);
}


char getElementFromArrayChar(charArray* array, size_t index) {
    return array->v[index];
}


size_t getLengthChar(charArray *array){
    return array->length;
}


size_t getBit(charArray* array, size_t index) {
    char number;

    if (index/4 < getLengthChar(array)) {
        number = getElementFromArrayChar(array, getLengthChar(array)-1-index / 4);
    }
    else {
        return 0;
    }
    int numberDex = hexToInt(number);
    return ((1<<(index % 4) & numberDex)>>(index % 4));
}


void setBit(charArray* array, size_t index) {
    size_t newIndex = (index / 4);
    char hex = binToHex(index % 4, newIndex, array);
    array->v[getLengthChar(array)-1-newIndex] = hex;
}

//void printArray(charArray* array) {
//    for (int i = 0; i < array->length; ++i) {
//        printf("%c ", array->v[i]);
//    }
//    printf("\n");
//}
