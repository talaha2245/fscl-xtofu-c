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
#include "fossil/xtofu/core.h"
#include <stdlib.h>
#include <string.h>

static char* tofu_strdup(const char* source) {
    if (source == NULL) {
        return NULL;
    }

    size_t length = strlen(source) + 1; // +1 for the null terminator
    char* duplicate = (char*)malloc(length);

    if (duplicate != NULL) {
        strcpy(duplicate, source);
    }

    return duplicate;
}

// Function to create a new ctofu instance
ctofu fscl_tofu_create(ctofu_type type) {
    ctofu new_tofu;
    new_tofu.type = type;
    memset(&new_tofu.data, 0, sizeof(ctofu_data));
    memset(&new_tofu.time, 0, sizeof(ctofu_time));
    return new_tofu;
}

// Function to create a new ctofu instance with default values
// Function to create a new ctofu instance with default values
ctofu fscl_tofu_create_default(ctofu_type type) {
    ctofu new_tofu = fscl_tofu_create(type);

    switch (type) {
        case TOFU_INT_TYPE:
            new_tofu.data.int_type = 0;
            break;
        case TOFU_INT8_TYPE:
        case TOFU_INT16_TYPE:
        case TOFU_INT32_TYPE:
        case TOFU_INT64_TYPE:
        case TOFU_UINT_TYPE:
        case TOFU_UINT8_TYPE:
        case TOFU_UINT16_TYPE:
        case TOFU_UINT32_TYPE:
        case TOFU_UINT64_TYPE:
        case TOFU_OCTAL8_TYPE:
        case TOFU_OCTAL16_TYPE:
        case TOFU_OCTAL32_TYPE:
        case TOFU_OCTAL64_TYPE:
        case TOFU_BITWISE8_TYPE:
        case TOFU_BITWISE16_TYPE:
        case TOFU_BITWISE32_TYPE:
        case TOFU_BITWISE64_TYPE:
        case TOFU_HEX8_TYPE:
        case TOFU_HEX16_TYPE:
        case TOFU_HEX32_TYPE:
            new_tofu.data.hex32_type = 0;
        case TOFU_HEX64_TYPE:
            // For integer types, default to 0
            new_tofu.data.int_type = 0;
            break;
        case TOFU_FLOAT_TYPE:
            new_tofu.data.float_type = 0.0f;
            break;
        case TOFU_DOUBLE_TYPE:
            new_tofu.data.double_type = 0.0;
            break;
        case TOFU_STRING_TYPE:
            new_tofu.data.string_type = NULL;
            break;
        case TOFU_CHAR_TYPE:
            new_tofu.data.char_type = '\0';
            break;
        case TOFU_BOOLEAN_TYPE:
            new_tofu.data.boolean_type = false;
            break;
        case TOFU_ARRAY_TYPE:
            new_tofu.data.array_type.elements = NULL;
            new_tofu.data.array_type.size = 0;
            break;
        case TOFU_QBIT_TYPE:
            new_tofu.data.qbit_type = 0;
            break;
        // Add default values for other types as necessary
        default:
            // Unsupported type; set to an invalid state or handle accordingly
            new_tofu.type = TOFU_INVALID_TYPE;
            break;
    }

    return new_tofu;
}

// Function to create a new ctofu instance as a copy of an existing one
ctofu fscl_tofu_create_copy(ctofu_type type, const ctofu* source) {
    ctofu new_tofu = fscl_tofu_create(type);
    fscl_tofu_value_copy(source, &new_tofu);
    return new_tofu;
}

// Function to create a new ctofu instance by moving the content from another instance
ctofu fscl_tofu_create_move(ctofu_type type, ctofu* source) {
    ctofu new_tofu = fscl_tofu_create(type);
    fscl_tofu_value_setter(source, &new_tofu);
    // Erase the content from the source
    fscl_tofu_erase_move(source);
    return new_tofu;
}

// Function to erase the content of a ctofu instance
ctofu_error fscl_tofu_erase(ctofu* value) {
    if (value == NULL) {
        return TOFU_ERROR_NULLPTR;
    }

    // Additional cleanup based on the type
    switch (value->type) {
        case TOFU_STRING_TYPE:
            free(value->data.string_type);
            break;
        case TOFU_ARRAY_TYPE:
            free(value->data.array_type.elements);
            break;
        // Add specific cleanup for other types as needed
        default:
            break;
    }

    // Reset data and time
    memset(&value->data, 0, sizeof(ctofu_data));
    memset(&value->time, 0, sizeof(ctofu_time));
    return TOFU_OK;
}

// Function to erase the content of a ctofu instance and move its resources
ctofu_error fscl_tofu_erase_move(ctofu* value) {
    if (value == NULL) {
        return TOFU_ERROR_NULLPTR;
    }

    // Additional cleanup based on the type
    switch (value->type) {
        case TOFU_STRING_TYPE:
            // Move ownership of the string
            value->data.string_type = realloc(value->data.string_type, 0);
            break;
        case TOFU_ARRAY_TYPE:
            // Move ownership of the array
            value->data.array_type.elements = realloc(value->data.array_type.elements, 0);
            break;
        // Add specific cleanup for other types as needed
        default:
            break;
    }

    // Reset data and time
    memset(&value->data, 0, sizeof(ctofu_data));
    memset(&value->time, 0, sizeof(ctofu_time));
    return TOFU_OK;
}

// Function to erase the content of a ctofu instance and copy its resources
ctofu_error fscl_tofu_erase_copy(ctofu* value) {
    if (value == NULL) {
        return TOFU_ERROR_NULLPTR;
    }

    // Additional cleanup based on the type
    switch (value->type) {
        case TOFU_STRING_TYPE:
            // Allocate new memory and copy the string using tofu_strdup
            value->data.string_type = tofu_strdup(value->data.string_type);
            break;
        case TOFU_ARRAY_TYPE:
            // Allocate new memory and copy the array
            value->data.array_type.elements = malloc(value->data.array_type.size * sizeof(ctofu));
            memcpy(value->data.array_type.elements, value->data.array_type.elements, value->data.array_type.size * sizeof(ctofu));
            break;
        // Add specific cleanup for other types as needed
        default:
            break;
    }

    // Reset data and time
    memset(&value->data, 0, sizeof(ctofu_data));
    memset(&value->time, 0, sizeof(ctofu_time));
    return TOFU_OK;
}
