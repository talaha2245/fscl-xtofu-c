/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#include "fossil/xtofu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// =======================
// CREATE/ERASE FUNCTIONS
// =======================
ctofu* fscl_tofu_create(ctofu_type type, ctofu_data* value) {
    ctofu* result = (ctofu*)malloc(sizeof(ctofu));
    if (result == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    result->type = type;

    switch (type) {
        case TOFU_INT_TYPE:
            result->data.int_type = value->int_type;
            break;
        case TOFU_UINT_TYPE:
            result->data.uint_type = value->uint_type;
            break;
        case TOFU_FLOAT_TYPE:
            result->data.float_type = value->float_type;
            break;
        case TOFU_DOUBLE_TYPE:
            result->data.double_type = value->double_type;
            break;
        case TOFU_OCTAL_TYPE:
            result->data.octal_type = value->octal_type;
            break;
        case TOFU_BITWISE_TYPE:
            result->data.bitwise_type = value->bitwise_type;
        case TOFU_HEX_TYPE:
            result->data.hex_type = value->hex_type;
            break;
        case TOFU_FIXED_TYPE:
            result->data.fixed_type = value->fixed_type;
            break;
        case TOFU_NULLPTR_TYPE:
            result->data.nullptr_type = value->nullptr_type;
            break;
        case TOFU_CHAR_TYPE:
            result->data.char_type = value->char_type;
            break;
        case TOFU_BOOLEAN_TYPE:
            result->data.boolean_type = value->boolean_type;
            break;
        case TOFU_ARRAY_TYPE:
            result->data.array_type = value->array_type;
            break;
        case TOFU_QBIT_TYPE:
            result->data.qbit_type = value->qbit_type;
            break;
        case TOFU_STRING_TYPE:
            result->data.string_type = fscl_tofu_strdup(value->string_type);
            if (result->data.string_type == NULL) {
                // Handle memory allocation failure
                free(result);
                return NULL;
            }
            break;
        default:
            // Handle other cases if needed
            free(result);
            return NULL;
    }

    return result;
}

bool fscl_tofu_is_homogeneous(ctofu_type type, size_t size, ctofu_data* elements) {
    for (size_t i = 0; i < size; ++i) {
        if (elements[i].array_type.elements->type != type) {
            return false;
        }
    }
    return true;
}

ctofu* fscl_tofu_create_array(ctofu_type type, size_t size, ...) {
    ctofu* tofu_array = (ctofu*)malloc(sizeof(ctofu));
    if (tofu_array == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    tofu_array->type = TOFU_ARRAY_TYPE;
    tofu_array->data.array_type.size = size;
    tofu_array->data.array_type.elements = (ctofu*)malloc(size * sizeof(ctofu));
    if (tofu_array->data.array_type.elements == NULL) {
        // Handle memory allocation failure
        free(tofu_array);
        return NULL;
    }

    va_list args;
    va_start(args, size);

    for (size_t i = 0; i < size; ++i) {
        tofu_array->data.array_type.elements[i].type = type;

        switch (type) {
            case TOFU_INT_TYPE:
                tofu_array->data.array_type.elements[i].data.int_type = va_arg(args, int);
                break;
            case TOFU_UINT_TYPE:
                tofu_array->data.array_type.elements[i].data.uint_type = va_arg(args, unsigned int);
                break;
            case TOFU_OCTAL_TYPE:
                tofu_array->data.array_type.elements[i].data.octal_type = va_arg(args, uint64_t);
                break;
            case TOFU_BITWISE_TYPE:
                tofu_array->data.array_type.elements[i].data.bitwise_type = va_arg(args, uint64_t);
                break;
            case TOFU_HEX_TYPE:
                tofu_array->data.array_type.elements[i].data.hex_type = va_arg(args, uint64_t);
                break;
            case TOFU_FIXED_TYPE:
                tofu_array->data.array_type.elements[i].data.fixed_type = va_arg(args, int64_t);
                break;
            case TOFU_FLOAT_TYPE:
                tofu_array->data.array_type.elements[i].data.float_type = va_arg(args, double);
                break;
            case TOFU_DOUBLE_TYPE:
                tofu_array->data.array_type.elements[i].data.double_type = va_arg(args, double);
                break;
            case TOFU_STRING_TYPE:
                tofu_array->data.array_type.elements[i].data.string_type = va_arg(args, char*);
                break;
            case TOFU_CHAR_TYPE:
                tofu_array->data.array_type.elements[i].data.char_type = va_arg(args, int);
                break;
            case TOFU_BOOLEAN_TYPE:
                tofu_array->data.array_type.elements[i].data.boolean_type = va_arg(args, int);
                break;
            case TOFU_QBIT_TYPE:
                tofu_array->data.array_type.elements[i].data.qbit_type = va_arg(args, uint64_t);
                break;
            case TOFU_NULLPTR_TYPE:
            case TOFU_UNKNOWN_TYPE:
            case TOFU_INVALID_TYPE:
            case TOFU_MAP_TYPE:
            case TOFU_ARRAY_TYPE:
                // Nested array or map not supported in this function
                free(tofu_array->data.array_type.elements);
                free(tofu_array);
                va_end(args);
                return NULL;
        }
    }

    va_end(args);

    // Perform type checking to ensure homogeneity
    if (!fscl_tofu_is_homogeneous(type, size, &tofu_array->data)) {
        // Handle mixed types, free allocated memory and return NULL
        free(tofu_array->data.array_type.elements);
        free(tofu_array);
        return NULL;
    }

    return tofu_array;
}

ctofu_error fscl_tofu_erase_array(ctofu* array) {
    if (!array || array->type != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INDEX_OUT_OF_BOUNDS); // Not an array
    }

    free(array->data.array_type.elements);
    array->data.array_type.elements = NULL;
    array->data.array_type.size = 0;
    array->type = TOFU_INVALID_TYPE;

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_erase(ctofu* value) {
    if (!value) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    free(value);
    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}


// =======================
// CLASSIC ALGORITHM FUNCTIONS
// =======================
ctofu_error fscl_tofu_accumulate(ctofu* objects) {
    if (objects == NULL) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (objects->type != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
    }

    size_t size = objects->data.array_type.size;

    if (size == 0) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (objects->data.array_type.elements == NULL) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    ctofu_data result;
    result.int_type = 0;

    for (size_t i = 0; i < size; ++i) {
        if (objects->data.array_type.elements[i].type != TOFU_INT_TYPE) {
            return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
        }

        ctofu_data currentData = fscl_tofu_value_getter(&objects->data.array_type.elements[i]);

        // Accumulate the values
        result.int_type += currentData.int_type;
    }

    // Create a new ctofu with the accumulated value
    ctofu* resultObject = fscl_tofu_create(TOFU_INT_TYPE, &result);
    
    if (resultObject == NULL) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_MEMORY_CORRUPTION);
    }

    // Erase the existing array and set the result object as its only element
    fscl_tofu_erase_array(objects);
    objects->data.array_type.size = 1;
    objects->data.array_type.elements = resultObject;

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_transform(ctofu* objects, int (*transformFunc)(int)) {
    if (!fscl_tofu_not_cnullptr(objects)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (fscl_tofu_type_getter(objects) != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
    }

    size_t size = objects->data.array_type.size;

    if (size == 0) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (objects->data.array_type.elements == NULL || transformFunc == NULL) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    for (size_t i = 0; i < size; ++i) {
        if (objects->data.array_type.elements[i].type != TOFU_INT_TYPE) {
            return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
        }

        // Get the current ctofu element
        ctofu currentData = objects->data.array_type.elements[i];

        // Apply the transformation function to the int_type
        currentData.data.int_type = transformFunc(currentData.data.int_type);

        // Set the updated ctofu element back to the array
        fscl_tofu_value_setter(&objects->data.array_type.elements[i], &currentData);
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_sort(ctofu* objects) {
    if (!fscl_tofu_not_cnullptr(objects)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (fscl_tofu_type_getter(objects) != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
    }

    // Ensure that array elements have compatible types for sorting
    for (size_t i = 0; i < objects->data.array_type.size; ++i) {
        if (fscl_tofu_type_getter(&objects->data.array_type.elements[i]) != TOFU_INT_TYPE) {
            return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
        }
    }

    // Implement a simple bubble sort algorithm
    for (size_t i = 0; i < objects->data.array_type.size - 1; ++i) {
        for (size_t j = 0; j < objects->data.array_type.size - i - 1; ++j) {
            ctofu_data current = fscl_tofu_value_getter(&objects->data.array_type.elements[j]);
            ctofu_data next = fscl_tofu_value_getter(&objects->data.array_type.elements[j + 1]);

            if (current.int_type > next.int_type) {
                // Swap elements if they are in the wrong order
                ctofu_data temp = objects->data.array_type.elements[j].data;
                objects->data.array_type.elements[j].data = objects->data.array_type.elements[j + 1].data;
                objects->data.array_type.elements[j + 1].data = temp;
            }
        }
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_search(ctofu* objects, ctofu* key) {
    if (!fscl_tofu_not_cnullptr(objects) || !fscl_tofu_not_cnullptr(key)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (fscl_tofu_type_getter(objects) != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
    }

    ctofu_type keyType = fscl_tofu_type_getter(key);

    // Ensure that array elements have compatible types for searching
    for (size_t i = 0; i < objects->data.array_type.size; ++i) {
        if (fscl_tofu_type_getter(&objects->data.array_type.elements[i]) != keyType) {
            return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
        }
    }

    // Implement a simple linear search algorithm
    for (size_t i = 0; i < objects->data.array_type.size; ++i) {
        if (fscl_tofu_compare(&objects->data.array_type.elements[i], key) == FSCL_TOFU_ERROR_OK) {
            return fscl_tofu_error(FSCL_TOFU_ERROR_OK);  // Key found
        }
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_TYPE_MISMATCH);  // Key not found
}

ctofu_error fscl_tofu_filter(ctofu* objects, bool (*filterFunc)(const ctofu_data*)) {
    if (!fscl_tofu_not_cnullptr(objects)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (fscl_tofu_type_getter(objects) != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
    }

    // Declare an array of ctofu_data to store the filtered elements
    ctofu_data filteredArray[objects->data.array_type.size];
    size_t filteredSize = 0;

    // Filter elements based on the provided function
    for (size_t i = 0; i < objects->data.array_type.size; ++i) {
        if (filterFunc(&objects->data.array_type.elements[i].data)) {
            // Copy the entire ctofu_data element into the filteredArray
            filteredArray[filteredSize] = objects->data.array_type.elements[i].data;
            ++filteredSize;
        }
    }

    // Clear existing data and store the filtered result
    fscl_tofu_erase(objects);
    // Create a new TOFU array and set its data
    objects = fscl_tofu_create(TOFU_ARRAY_TYPE, filteredArray);
    objects->data.array_type.size = filteredSize;

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_reverse(ctofu* objects) {
    if (!fscl_tofu_not_cnullptr(objects)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (fscl_tofu_type_getter(objects) != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_UNKNOWN);
    }

    // Reverse the array elements
    size_t i = 0;
    size_t j = objects->data.array_type.size - 1;

    while (i < j) {
        // Swap elements at positions i and j
        ctofu_data temp = objects->data.array_type.elements[i].data;
        objects->data.array_type.elements[i].data = objects->data.array_type.elements[j].data;
        objects->data.array_type.elements[j].data = temp;

        ++i;
        --j;
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_swap(ctofu* right, ctofu* left) {
    if (!right || !left) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    ctofu temp = *right;
    *right = *left;
    *left = temp;

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_compare(ctofu* right, ctofu* left) {
    if (!fscl_tofu_not_cnullptr(right) || !fscl_tofu_not_cnullptr(left)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (fscl_tofu_type_getter(right) != fscl_tofu_type_getter(left)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
    }

    // Compare the data based on their types
    switch (fscl_tofu_type_getter(right)) {
        case TOFU_INT_TYPE:
            return (right->data.int_type == left->data.int_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_UINT_TYPE:
            return (right->data.uint_type == left->data.uint_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_OCTAL_TYPE:
            return (right->data.octal_type == left->data.octal_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_BITWISE_TYPE:
            return (right->data.bitwise_type == left->data.bitwise_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_HEX_TYPE:
            return (right->data.hex_type == left->data.hex_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_FIXED_TYPE:
            return (right->data.fixed_type == left->data.fixed_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_FLOAT_TYPE:
            return (right->data.float_type == left->data.float_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_DOUBLE_TYPE:
            return (right->data.double_type == left->data.double_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_STRING_TYPE:
            return (strcmp(right->data.string_type, left->data.string_type) == 0) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_CHAR_TYPE:
            return (right->data.char_type == left->data.char_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_BOOLEAN_TYPE:
            return (right->data.boolean_type == left->data.boolean_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        case TOFU_NULLPTR_TYPE:
            // Comparison for null pointers (always equal)
            return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
        case TOFU_ARRAY_TYPE:
            // Handle array type
            // You might want to implement specific logic for comparing array elements
            // For simplicity, I'll return TOFU_UNKNOWN_TYPE indicating unsupported comparison
            printf("Unsupported type (array) for value comparison\n");
            return fscl_tofu_error(FSCL_TOFU_ERROR_UNKNOWN);

        case TOFU_MAP_TYPE:
            // Handle map type
            // You might want to implement specific logic for comparing map elements
            // For simplicity, I'll return TOFU_UNKNOWN_TYPE indicating unsupported comparison
            printf("Unsupported type (map) for value comparison\n");
            return fscl_tofu_error(FSCL_TOFU_ERROR_UNKNOWN);
        case TOFU_QBIT_TYPE:
            return (right->data.qbit_type == left->data.qbit_type) ? FSCL_TOFU_ERROR_OK : FSCL_TOFU_ERROR_INVALID_OPERATION;
        default:
            return fscl_tofu_error(FSCL_TOFU_ERROR_UNKNOWN);  // Unsupported data type for comparison
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_reduce(ctofu* objects, ctofu (*reduceFunc)(const ctofu*, const ctofu*)) {
    if (!fscl_tofu_not_cnullptr(objects)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (fscl_tofu_type_getter(objects) != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_UNKNOWN);
    }

    if (objects->data.array_type.size < 2) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_OK);  // No reduction needed for less than two elements
    }

    // Apply the reduce function iteratively
    for (size_t i = 1; i < objects->data.array_type.size; ++i) {
        ctofu reducedValue = reduceFunc(&objects->data.array_type.elements[i - 1], &objects->data.array_type.elements[i]);
        fscl_tofu_value_setter(&reducedValue, &objects->data.array_type.elements[i]);
    }

    // Update the size after reduction
    objects->data.array_type.size = 1;

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_shuffle(ctofu* objects) {
    if (!fscl_tofu_not_cnullptr(objects)) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    if (fscl_tofu_type_getter(objects) != TOFU_ARRAY_TYPE) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_UNKNOWN);
    }

    size_t size = objects->data.array_type.size;

    // Use Fisher-Yates shuffle algorithm to randomize the array elements
    for (size_t i = size - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);

        // Swap elements at positions i and j
        ctofu_data temp = objects->data.array_type.elements[i].data;
        objects->data.array_type.elements[i].data = objects->data.array_type.elements[j].data;
        objects->data.array_type.elements[j].data = temp;
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_for_each(ctofu* objects, void (*forEachFunc)(ctofu*)) {
    if (objects == NULL || forEachFunc == NULL) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
    }

    size_t size = objects->data.array_type.size;
    for (size_t i = 0; i < size; ++i) {
        forEachFunc(&objects->data.array_type.elements[i]);
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

ctofu_error fscl_tofu_partition(ctofu* objects, bool (*partitionFunc)(const ctofu*), ctofu* partitionedResults[2]) {
    if (objects == NULL || partitionFunc == NULL || partitionedResults == NULL) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_INVALID_OPERATION);
    }

    size_t size = objects->data.array_type.size;
    size_t partition1Count = 0;
    
    // Count the elements satisfying the predicate
    for (size_t i = 0; i < size; ++i) {
        if (partitionFunc(&objects->data.array_type.elements[i])) {
            ++partition1Count;
        }
    }

    // Allocate memory for partitioned results
    partitionedResults[0] = fscl_tofu_create_array(objects->type, partition1Count);
    partitionedResults[1] = fscl_tofu_create_array(objects->type, size - partition1Count);

    if (partitionedResults[0] == NULL || partitionedResults[1] == NULL) {
        // Handle memory allocation failure
        return fscl_tofu_error(FSCL_TOFU_ERROR_BUFFER_OVERFLOW);
    }

    size_t indexPartition1 = 0;
    size_t indexPartition2 = 0;

    // Partition the elements based on the predicate
    for (size_t i = 0; i < size; ++i) {
        ctofu* currentElement = &objects->data.array_type.elements[i];
        if (partitionFunc(currentElement)) {
            fscl_tofu_value_setter(currentElement, &partitionedResults[0]->data.array_type.elements[indexPartition1++]);
        } else {
            fscl_tofu_value_setter(currentElement, &partitionedResults[1]->data.array_type.elements[indexPartition2++]);
        }
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

// =======================
// UTILITY FUNCTIONS
// =======================

void fscl_tofu_out(const ctofu value) {
    switch (value.type) {
        case TOFU_INT_TYPE:
            printf("%d", value.data.int_type);
            break;
        case TOFU_UINT_TYPE:
            printf("%llu", (uint64_t)value.data.uint_type);
            break;
        case TOFU_OCTAL_TYPE:
            printf("0%llo", (uint64_t)value.data.octal_type);
            break;
        case TOFU_BITWISE_TYPE:
            printf("0x%llx", (uint64_t)value.data.bitwise_type);
            break;
        case TOFU_HEX_TYPE:
            printf("0x%llx", (uint64_t)value.data.hex_type);
            break;
        case TOFU_FIXED_TYPE:
            printf("%d.%d", value.data.fixed_type, (value.data.fixed_type - (int)value.data.fixed_type) * 100);
            break;
        case TOFU_FLOAT_TYPE:
            printf("%f", value.data.float_type);
            break;
        case TOFU_DOUBLE_TYPE:
            printf("%f", value.data.double_type);
            break;
        case TOFU_STRING_TYPE:
            printf("%s", value.data.string_type);
            break;
        case TOFU_CHAR_TYPE:
            printf("%c", value.data.char_type);
            break;
        case TOFU_BOOLEAN_TYPE:
            printf("%s", value.data.boolean_type ? "true" : "false");
            break;
        case TOFU_NULLPTR_TYPE:
            printf("cnullptr");
            break;
        case TOFU_QBIT_TYPE:
            // Assuming that qbit_type is an unsigned integer type
            printf("0b");
            for (int i = sizeof(value.data.qbit_type) * 8 - 1; i >= 0; --i) {
                printf("%llu", (long long unsigned int)((value.data.qbit_type >> i) & 1));
            }
            break;
        case TOFU_ARRAY_TYPE:
            printf("[ ");
            for (size_t i = 0; i < value.data.array_type.size; ++i) {
                fscl_tofu_out(value.data.array_type.elements[i]);
                if (i < value.data.array_type.size - 1) {
                    printf(", ");
                }
            }
            printf(" ]");
            break;
        case TOFU_MAP_TYPE:
            printf("< ");
            for (size_t i = 0; i < value.data.map_type.size; ++i) {
                fscl_tofu_out(value.data.map_type.key[i]);
                printf(": ");
                fscl_tofu_out(value.data.map_type.value[i]);
                if (i < value.data.map_type.size - 1) {
                    printf(", ");
                }
            }
            printf(" >");
            break;
        case TOFU_INVALID_TYPE:
        case TOFU_UNKNOWN_TYPE:
            printf("[Invalid or Unknown Type]");
            break;
    }
}

char* fscl_tofu_strdup(const char* source) {
    if (source == NULL) {
        return NULL;
    }

    size_t length = strlen(source) + 1;  // +1 for the null terminator
    char* destination = (char*)malloc(length);

    if (destination != NULL) {
        memcpy(destination, source, length);
    }

    return destination;
}

ctofu_error fscl_tofu_error(ctofu_error error) {
    fscl_tofu_error_message(error);
    return error;
}

ctofu_error fscl_tofu_value_copy(const ctofu* source, ctofu* dest) {
    if (source == NULL || dest == NULL) {
        return fscl_tofu_error(FSCL_TOFU_ERROR_NULL_POINTER);
    }

    dest->type = source->type;

    switch (source->type) {
        case TOFU_INT_TYPE:
            dest->data.int_type = source->data.int_type;
            break;

        case TOFU_UINT_TYPE:
            dest->data.uint_type = source->data.uint_type;
            break;

        case TOFU_OCTAL_TYPE:
            dest->data.octal_type = source->data.octal_type;
            break;

        case TOFU_BITWISE_TYPE:
            dest->data.bitwise_type = source->data.bitwise_type;
            break;

        case TOFU_HEX_TYPE:
            dest->data.hex_type = source->data.hex_type;
            break;
        
        case TOFU_FIXED_TYPE:
            dest->data.fixed_type = source->data.fixed_type;
            break;

        case TOFU_FLOAT_TYPE:
            dest->data.float_type = source->data.float_type;
            break;

        case TOFU_DOUBLE_TYPE:
            dest->data.double_type = source->data.double_type;
            break;

        case TOFU_STRING_TYPE:
            dest->data.string_type = fscl_tofu_strdup(source->data.string_type);
            break;

        case TOFU_CHAR_TYPE:
            dest->data.char_type = source->data.char_type;
            break;

        case TOFU_BOOLEAN_TYPE:
            dest->data.boolean_type = source->data.boolean_type;
            break;

        case TOFU_ARRAY_TYPE:
            // Implement array copying logic here
            if (source->data.array_type.size > 0 && source->data.array_type.elements != NULL) {
                dest->data.array_type.size = source->data.array_type.size;
                dest->data.array_type.elements = malloc(dest->data.array_type.size * sizeof(ctofu));
                
                if (dest->data.array_type.elements == NULL) {
                    return fscl_tofu_error(FSCL_TOFU_ERROR_MEMORY_CORRUPTION); // Handle memory allocation failure
                }

                // Copy each element
                for (size_t i = 0; i < dest->data.array_type.size; ++i) {
                    ctofu_error copyResult = fscl_tofu_value_copy(&source->data.array_type.elements[i], &dest->data.array_type.elements[i]);
                    if (copyResult != FSCL_TOFU_ERROR_OK) {
                        // Handle copy error
                        // Clean up allocated memory
                        for (size_t j = 0; j < i; ++j) {
                            free(dest->data.array_type.elements[j].data.string_type);
                        }
                        free(dest->data.array_type.elements);
                        return copyResult;
                    }
                }
            } else {
                return fscl_tofu_error(FSCL_TOFU_ERROR_INDEX_OUT_OF_BOUNDS); // Array is empty or null
            }
            break;
        case TOFU_MAP_TYPE:
            dest->data.map_type.size = source->data.map_type.size;

            // Allocate memory for keys and values
            dest->data.map_type.key = (ctofu*)malloc(sizeof(ctofu) * dest->data.map_type.size);
            dest->data.map_type.value = (ctofu*)malloc(sizeof(ctofu) * dest->data.map_type.size);

            if (dest->data.map_type.key == NULL || dest->data.map_type.value == NULL) {
                // Handle memory allocation failure
                free(dest->data.map_type.key);
                free(dest->data.map_type.value);
                return fscl_tofu_error(FSCL_TOFU_ERROR_MEMORY_CORRUPTION);
            }

            // Copy keys and values
            for (size_t i = 0; i < dest->data.map_type.size; ++i) {
                ctofu_error copyResult = fscl_tofu_value_copy(&source->data.map_type.key[i], &dest->data.map_type.key[i]);
                if (copyResult != FSCL_TOFU_ERROR_OK) {
                    // Handle copy error
                    // Clean up allocated memory
                    for (size_t j = 0; j < i; ++j) {
                        free(dest->data.map_type.key[j].data.string_type);
                        free(dest->data.map_type.value[j].data.string_type);
                    }
                    free(dest->data.map_type.key);
                    free(dest->data.map_type.value);
                    return copyResult;
                }

                copyResult = fscl_tofu_value_copy(&source->data.map_type.value[i], &dest->data.map_type.value[i]);
                if (copyResult != FSCL_TOFU_ERROR_OK) {
                    // Handle copy error
                    // Clean up allocated memory
                    for (size_t j = 0; j <= i; ++j) {
                        free(dest->data.map_type.key[j].data.string_type);
                        free(dest->data.map_type.value[j].data.string_type);
                    }
                    free(dest->data.map_type.key);
                    free(dest->data.map_type.value);
                    return copyResult;
                }
            }
            break;

        case TOFU_QBIT_TYPE:
            dest->data.qbit_type = source->data.qbit_type;
            break;

        case TOFU_NULLPTR_TYPE:
            dest->data.nullptr_type = source->data.nullptr_type;
            break;

        default:
            // Handle unsupported types
            printf("Unsupported type for value copy\n");
            return fscl_tofu_error(FSCL_TOFU_ERROR_UNKNOWN);
    }

    return fscl_tofu_error(FSCL_TOFU_ERROR_OK);
}

void fscl_tofu_value_erase(ctofu* value) {
    if (value == NULL) {
        return;
    }

    switch (value->type) {
        case TOFU_STRING_TYPE:
            free(value->data.string_type);
            break;

        case TOFU_ARRAY_TYPE:
            for (size_t i = 0; i < value->data.array_type.size; ++i) {
                fscl_tofu_value_erase(&value->data.array_type.elements[i]);
            }
            free(value->data.array_type.elements);
            break;

        default:
            // No specific cleanup needed for other types
            break;
    }
}

void fscl_tofu_value_setter(const ctofu* source, ctofu* dest) {
    if (source == NULL || dest == NULL) {
        return;
    }

    dest->type = source->type;

    switch (source->type) {
        case TOFU_INT_TYPE:
            dest->data.int_type = source->data.int_type;
            break;

        case TOFU_UINT_TYPE:
            dest->data.uint_type = source->data.uint_type;
            break;

        case TOFU_OCTAL_TYPE:
            dest->data.octal_type = source->data.octal_type;
            break;

        case TOFU_BITWISE_TYPE:
            dest->data.bitwise_type = source->data.bitwise_type;
            break;

        case TOFU_HEX_TYPE:
            dest->data.hex_type = source->data.hex_type;
            break;

        case TOFU_FIXED_TYPE:
            dest->data.fixed_type = source->data.fixed_type;
            break;

        case TOFU_FLOAT_TYPE:
            dest->data.float_type = source->data.float_type;
            break;

        case TOFU_DOUBLE_TYPE:
            dest->data.double_type = source->data.double_type;
            break;

        case TOFU_STRING_TYPE:
            dest->data.string_type = fscl_tofu_strdup(source->data.string_type);
            break;

        case TOFU_CHAR_TYPE:
            dest->data.char_type = source->data.char_type;
            break;

        case TOFU_BOOLEAN_TYPE:
            dest->data.boolean_type = source->data.boolean_type;
            break;

        case TOFU_ARRAY_TYPE:
            // Check if both arrays have the same type
            if (source->data.array_type.size != dest->data.array_type.size ||
                source->data.array_type.elements[0].type != dest->data.array_type.elements[0].type) {
                printf("Incompatible array types for value setter\n");
                break;  // or return an error code
            }
        
            // Set array B to array A
            dest->data.array_type.size = source->data.array_type.size;
        
            // Cleanup existing array elements in B
            for (size_t i = 0; i < dest->data.array_type.size; ++i) {
                fscl_tofu_value_erase(&dest->data.array_type.elements[i]);
            }
        
            // Allocate memory for new array elements in B
            dest->data.array_type.elements = (ctofu*)malloc(dest->data.array_type.size * sizeof(ctofu));
            if (dest->data.array_type.elements == NULL) {
                // Handle memory allocation failure
                printf("Memory allocation failed for array elements\n");
                break;  // or return an error code
            }
        
            // Copy elements from A to B
            for (size_t i = 0; i < dest->data.array_type.size; ++i) {
                fscl_tofu_value_setter(&source->data.array_type.elements[i], &dest->data.array_type.elements[i]);
            }
            break;

        case TOFU_MAP_TYPE:
            dest->data.map_type.size = source->data.map_type.size;

            // Allocate memory for keys and values
            dest->data.map_type.key = (ctofu*)malloc(sizeof(ctofu) * dest->data.map_type.size);
            dest->data.map_type.value = (ctofu*)malloc(sizeof(ctofu) * dest->data.map_type.size);

            if (dest->data.map_type.key == NULL || dest->data.map_type.value == NULL) {
                // Handle memory allocation failure
                free(dest->data.map_type.key);
                free(dest->data.map_type.value);
                printf("Memory allocation failed for map keys or values\n");
                break;
            }

            // Copy keys and values
            for (size_t i = 0; i < dest->data.map_type.size; ++i) {
                fscl_tofu_value_setter(&source->data.map_type.key[i], &dest->data.map_type.key[i]);
                fscl_tofu_value_setter(&source->data.map_type.value[i], &dest->data.map_type.value[i]);
            }
            break;

        case TOFU_QBIT_TYPE:
            dest->data.qbit_type = source->data.qbit_type;
            break;

        case TOFU_NULLPTR_TYPE:
            dest->data.nullptr_type = source->data.nullptr_type;
            break;

        default:
            // Handle unsupported types
            printf("Unsupported type for value setter\n");
    }
}

ctofu_data fscl_tofu_value_getter(ctofu* current) {
    ctofu_data result;

    if (current == NULL) {
        // You might want to handle this case differently based on your requirements
        result.int_type = 0;
        return result;
    }

    switch (current->type) {
        case TOFU_INT_TYPE:
            result.int_type = current->data.int_type;
            break;

        case TOFU_UINT_TYPE:
            result.uint_type = current->data.uint_type;
            break;

        case TOFU_OCTAL_TYPE:
            result.octal_type = current->data.octal_type;
            break;

        case TOFU_BITWISE_TYPE:
            result.bitwise_type = current->data.bitwise_type;
            break;

        case TOFU_HEX_TYPE:
            result.hex_type = current->data.hex_type;
            break;

        case TOFU_FIXED_TYPE:
            result.fixed_type = current->data.fixed_type;
            break;

        case TOFU_FLOAT_TYPE:
            result.float_type = current->data.float_type;
            break;

        case TOFU_DOUBLE_TYPE:
            result.double_type = current->data.double_type;
            break;

        case TOFU_STRING_TYPE:
            result.string_type = current->data.string_type;
            break;

        case TOFU_CHAR_TYPE:
            result.char_type = current->data.char_type;
            break;

        case TOFU_BOOLEAN_TYPE:
            result.boolean_type = current->data.boolean_type;
            break;

        case TOFU_QBIT_TYPE:
            result.qbit_type = current->data.qbit_type;
            break;

        case TOFU_NULLPTR_TYPE:
            result.nullptr_type = current->data.nullptr_type;
            break;

        case TOFU_ARRAY_TYPE:
            // Handle array type
            printf("Unsupported type (array) for value getter\n");
            // You might want to set a default value or handle this case differently
            result.int_type = 0;
            break;

        case TOFU_MAP_TYPE:
            // Handle map type
            printf("Unsupported type (map) for value getter\n");
            // You might want to set a default value or handle this case differently
            result.int_type = 0;
            break;

        default:
            // Handle unsupported types
            printf("Unsupported type for value getter\n");
            // You might want to set a default value or handle this case differently
            result.int_type = 0;
    }

    return result;
}

ctofu_type fscl_tofu_type_getter(ctofu* current) {
    if (current == NULL) {
        // You might want to handle this case differently based on your requirements
        return TOFU_UNKNOWN_TYPE;
    }

    return current->type;
}

bool fscl_tofu_not_cnullptr(const ctofu* value) {
    return value != NULL;
}

bool fscl_tofu_its_cnullptr(const ctofu* value) {
    return value == NULL;
}

// =======================
// ITERATOR FUNCTIONS
// =======================
ctofu_iterator fscl_tofu_iterator_at(ctofu* array, size_t num, size_t at) {
    ctofu_iterator iterator;

    if (array == NULL || num == 0 || at >= num) {
        iterator.current_value = NULL;
        iterator.index = num;
        return iterator;
    }

    iterator.current_value = &array[at];
    iterator.index = at;

    return iterator;
}

ctofu_iterator fscl_tofu_iterator_start(ctofu* array, size_t num) {
    return fscl_tofu_iterator_at(array, num, 0);
}

ctofu_iterator fscl_tofu_iterator_end(ctofu* array, size_t num) {
    return fscl_tofu_iterator_at(array, num, num);
}
