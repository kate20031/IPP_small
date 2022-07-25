#include <stddef.h>
#include "array.h"
#include "errors.h"
#include <malloc.h>

struct Array {
    size_t length;
    size_t memory;
    size_t *v;
};
//typedef struct Array Array;

Array* createArray() {
    Array* array = malloc(sizeof (Array));
    if (array == NULL) {
        return array;
    }
    array->v = malloc(sizeof(size_t));
    if (array->v == NULL) {
        free(array);
        return NULL;
    }

    array->length = 0;
    array->memory = 1;
    return array;
}

void pushBack(Array* array, size_t element) {
    if (array->memory == array->length) {
        array->v = realloc(array->v, sizeof(size_t) * array->memory * 2);
        if (array->v == NULL) {
            handleError(0);
        }
        array->memory *= 2;
    }
    array->v[array->length] = element;
    array->length += 1;
}


void deleteArray(Array* array) {
    free(array->v);
    free(array);
}

size_t getElementFromArray(Array* array, size_t index) {
    return array->v[index];
}

size_t getLength(Array *array){
    return array->length;
}