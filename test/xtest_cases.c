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
#include "fossil/xtofu.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassume.h> // extra asserts

// Helper functions for algorithms
int square_transform_function(int value) {
    return value * value;
}

bool even_filter_function(const ctofu_data* element) {
    return (element->int_type % 2) == 0;
}

// Function to calculate the sum of elements in an array
ctofu sum_reduce_function(const ctofu* element, const ctofu* accumulator) {
    // Ensure both elements are integers
    if (element->type != TOFU_INT_TYPE || accumulator->type != TOFU_INT_TYPE) {
        ctofu error_result;
        error_result.type = TOFU_UNKNOWN_TYPE;
        return error_result;
    }

    // Calculate the sum
    int sum = accumulator->data.int_type + element->data.int_type;

    // Create a ctofu with the sum and return it
    ctofu result;
    result.type = TOFU_INT_TYPE;
    result.data.int_type = sum;
    return result;
}

// Function to check if an element meets criteria for partitioning
bool even_partition_function(const ctofu* element) {
    // Implement your logic here to determine if the element meets the partitioning criteria
    // For example, you could check if the element is even

    if (element == NULL) {
        // Handle NULL pointer
        return false;
    }

    // Example logic: Check if the value of the element is even
    if (element->type == TOFU_INT_TYPE && element->data.int_type % 2 == 0) {
        return true; // Element meets the criteria for partitioning
    }

    return false; // Element does not meet the criteria
}


// Function to print each element of an array
void out_element_function(ctofu* element) {
    // Ensure the element is an integer
    if (element->type != TOFU_INT_TYPE) {
        return;
    }

    // Print the element
    printf("%lld ", (long long)element->data.int_type);
}

//
// XUNIT TEST CASES
//

XTEST(test_create_and_erase) {
    // Test creating and erasing "tofu" structures for each supported type

    // Integer types
    ctofu* int_tofu = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 42});
    TEST_ASSUME_NOT_CNULLPTR(int_tofu);
    fscl_tofu_erase(int_tofu);

    ctofu* int8_tofu = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 8});
    TEST_ASSUME_NOT_CNULLPTR(int8_tofu);
    fscl_tofu_erase(int8_tofu);

    ctofu* int16_tofu = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 16});
    TEST_ASSUME_NOT_CNULLPTR(int16_tofu);
    fscl_tofu_erase(int16_tofu);

    ctofu* int32_tofu = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 32});
    TEST_ASSUME_NOT_CNULLPTR(int32_tofu);
    fscl_tofu_erase(int32_tofu);

    ctofu* int64_tofu = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 64});
    TEST_ASSUME_NOT_CNULLPTR(int64_tofu);
    fscl_tofu_erase(int64_tofu);

    // Unsigned integer types
    ctofu* uint_tofu = fscl_tofu_create(TOFU_UINT_TYPE, &(ctofu_data){.uint_type = 42});
    TEST_ASSUME_NOT_CNULLPTR(uint_tofu);
    fscl_tofu_erase(uint_tofu);

    ctofu* uint8_tofu = fscl_tofu_create(TOFU_UINT_TYPE, &(ctofu_data){.uint_type = 8});
    TEST_ASSUME_NOT_CNULLPTR(uint8_tofu);
    fscl_tofu_erase(uint8_tofu);

    ctofu* uint16_tofu = fscl_tofu_create(TOFU_UINT_TYPE, &(ctofu_data){.uint_type = 16});
    TEST_ASSUME_NOT_CNULLPTR(uint16_tofu);
    fscl_tofu_erase(uint16_tofu);

    ctofu* uint32_tofu = fscl_tofu_create(TOFU_UINT_TYPE, &(ctofu_data){.uint_type = 32});
    TEST_ASSUME_NOT_CNULLPTR(uint32_tofu);
    fscl_tofu_erase(uint32_tofu);

    ctofu* uint64_tofu = fscl_tofu_create(TOFU_UINT_TYPE, &(ctofu_data){.uint_type = 64});
    TEST_ASSUME_NOT_CNULLPTR(uint64_tofu);
    fscl_tofu_erase(uint64_tofu);

    // Octal types
    ctofu* octal8_tofu = fscl_tofu_create(TOFU_OCTAL_TYPE, &(ctofu_data){.octal_type = 075});
    TEST_ASSUME_NOT_CNULLPTR(octal8_tofu);
    fscl_tofu_erase(octal8_tofu);

    ctofu* octal16_tofu = fscl_tofu_create(TOFU_OCTAL_TYPE, &(ctofu_data){.octal_type = 017});
    TEST_ASSUME_NOT_CNULLPTR(octal16_tofu);
    fscl_tofu_erase(octal16_tofu);

    ctofu* octal32_tofu = fscl_tofu_create(TOFU_OCTAL_TYPE, &(ctofu_data){.octal_type = 033});
    TEST_ASSUME_NOT_CNULLPTR(octal32_tofu);
    fscl_tofu_erase(octal32_tofu);

    ctofu* octal64_tofu = fscl_tofu_create(TOFU_OCTAL_TYPE, &(ctofu_data){.octal_type = 070});
    TEST_ASSUME_NOT_CNULLPTR(octal64_tofu);
    fscl_tofu_erase(octal64_tofu);

    // Bitwise types
    ctofu* bitwise8_tofu = fscl_tofu_create(TOFU_BITWISE_TYPE, &(ctofu_data){.bitwise_type = 0b1010});
    TEST_ASSUME_NOT_CNULLPTR(bitwise8_tofu);
    fscl_tofu_erase(bitwise8_tofu);

    ctofu* bitwise16_tofu = fscl_tofu_create(TOFU_BITWISE_TYPE, &(ctofu_data){.bitwise_type = 0b11001100});
    TEST_ASSUME_NOT_CNULLPTR(bitwise16_tofu);
    fscl_tofu_erase(bitwise16_tofu);

    ctofu* bitwise32_tofu = fscl_tofu_create(TOFU_BITWISE_TYPE, &(ctofu_data){.bitwise_type = 0b111100001111});
    TEST_ASSUME_NOT_CNULLPTR(bitwise32_tofu);
    fscl_tofu_erase(bitwise32_tofu);

    ctofu* bitwise64_tofu = fscl_tofu_create(TOFU_BITWISE_TYPE, &(ctofu_data){.bitwise_type = 0b11110000111100001111000011110000});
    TEST_ASSUME_NOT_CNULLPTR(bitwise64_tofu);
    fscl_tofu_erase(bitwise64_tofu);

    // Hexadecimal types
    ctofu* hex8_tofu = fscl_tofu_create(TOFU_HEX_TYPE, &(ctofu_data){.hex_type = 0xA});
    TEST_ASSUME_NOT_CNULLPTR(hex8_tofu);
    fscl_tofu_erase(hex8_tofu);

    ctofu* hex16_tofu = fscl_tofu_create(TOFU_HEX_TYPE, &(ctofu_data){.hex_type = 0xABCD});
    TEST_ASSUME_NOT_CNULLPTR(hex16_tofu);
    fscl_tofu_erase(hex16_tofu);

    ctofu* hex32_tofu = fscl_tofu_create(TOFU_HEX_TYPE, &(ctofu_data){.hex_type = 0x12345678});
    TEST_ASSUME_NOT_CNULLPTR(hex32_tofu);
    fscl_tofu_erase(hex32_tofu);

    ctofu* hex64_tofu = fscl_tofu_create(TOFU_HEX_TYPE, &(ctofu_data){.hex_type = 0x123456789ABCDEF0});
    TEST_ASSUME_NOT_CNULLPTR(hex64_tofu);
    fscl_tofu_erase(hex64_tofu);

    // Floating-point types
    ctofu* float_tofu = fscl_tofu_create(TOFU_FLOAT_TYPE, &(ctofu_data){.float_type = 3.14f});
    TEST_ASSUME_NOT_CNULLPTR(float_tofu);
    fscl_tofu_erase(float_tofu);

    ctofu* double_tofu = fscl_tofu_create(TOFU_DOUBLE_TYPE, &(ctofu_data){.double_type = 2.71828});
    TEST_ASSUME_NOT_CNULLPTR(double_tofu);
    fscl_tofu_erase(double_tofu);

    // Character type
    ctofu* char_tofu = fscl_tofu_create(TOFU_CHAR_TYPE, &(ctofu_data){.char_type = 'A'});
    TEST_ASSUME_NOT_CNULLPTR(char_tofu);
    fscl_tofu_erase(char_tofu);

    // Boolean type
    ctofu* bool_tofu = fscl_tofu_create(TOFU_BOOLEAN_TYPE, &(ctofu_data){.boolean_type = true});
    TEST_ASSUME_NOT_CNULLPTR(bool_tofu);
    fscl_tofu_erase(bool_tofu);

    // String type
    ctofu* string_tofu = fscl_tofu_create(TOFU_STRING_TYPE, &(ctofu_data){.string_type = "Hello"});
    TEST_ASSUME_NOT_CNULLPTR(string_tofu);
    fscl_tofu_erase(string_tofu);

    // Null pointer type
    ctofu* nullptr_tofu = fscl_tofu_create(TOFU_NULLPTR_TYPE, &(ctofu_data){.nullptr_type = NULL});
    TEST_ASSUME_NOT_CNULLPTR(nullptr_tofu);
    fscl_tofu_erase(nullptr_tofu);

    // Array type
    ctofu* array_tofu = fscl_tofu_create_array(TOFU_ARRAY_TYPE, 3, int_tofu, char_tofu, bool_tofu);
    TEST_ASSUME_NOT_CNULLPTR(array_tofu);
    fscl_tofu_erase_array(array_tofu);

    // Map type
    ctofu* map_tofu = fscl_tofu_create(TOFU_MAP_TYPE, &(ctofu_data){.map_type = {
        .key = int_tofu,
        .value = bool_tofu,
        .size = 1
    }});
    TEST_ASSUME_NOT_CNULLPTR(map_tofu);
    fscl_tofu_erase(map_tofu);

    // Quantum bit type
    ctofu* qbit_tofu = fscl_tofu_create(TOFU_QBIT_TYPE, &(ctofu_data){.qbit_type = 0b1101});
    TEST_ASSUME_NOT_CNULLPTR(qbit_tofu);
    fscl_tofu_erase(qbit_tofu);
}

XTEST(test_create_array_all_types) {
    // Test creating and erasing for each supported type

    // Integer array type
    ctofu* int_array_tofu = fscl_tofu_create_array(TOFU_INT_TYPE, 3, 1, 2, 3);
    TEST_ASSUME_NOT_CNULLPTR(int_array_tofu);
    fscl_tofu_erase(int_array_tofu);

    // 8-bit Integer array type
    ctofu* int8_array_tofu = fscl_tofu_create_array(TOFU_INT_TYPE, 3, 8, 16, 32);
    TEST_ASSUME_NOT_CNULLPTR(int8_array_tofu);
    fscl_tofu_erase(int8_array_tofu);

    // 16-bit Integer array type
    ctofu* int16_array_tofu = fscl_tofu_create_array(TOFU_INT_TYPE, 3, 16, 32, 64);
    TEST_ASSUME_NOT_CNULLPTR(int16_array_tofu);
    fscl_tofu_erase(int16_array_tofu);

    // 32-bit Integer array type
    ctofu* int32_array_tofu = fscl_tofu_create_array(TOFU_INT_TYPE, 3, 32, 64, 128);
    TEST_ASSUME_NOT_CNULLPTR(int32_array_tofu);
    fscl_tofu_erase(int32_array_tofu);

    // 64-bit Integer array type
    ctofu* int64_array_tofu = fscl_tofu_create_array(TOFU_INT_TYPE, 3, 64, 128, 256);
    TEST_ASSUME_NOT_CNULLPTR(int64_array_tofu);
    fscl_tofu_erase(int64_array_tofu);

    // Unsigned Integer array type
    ctofu* uint_array_tofu = fscl_tofu_create_array(TOFU_UINT_TYPE, 3, 42, 84, 168);
    TEST_ASSUME_NOT_CNULLPTR(uint_array_tofu);
    fscl_tofu_erase(uint_array_tofu);

    // 8-bit Unsigned Integer array type
    ctofu* uint8_array_tofu = fscl_tofu_create_array(TOFU_UINT_TYPE, 3, 8, 16, 32);
    TEST_ASSUME_NOT_CNULLPTR(uint8_array_tofu);
    fscl_tofu_erase(uint8_array_tofu);

    // 16-bit Unsigned Integer array type
    ctofu* uint16_array_tofu = fscl_tofu_create_array(TOFU_UINT_TYPE, 3, 16, 32, 64);
    TEST_ASSUME_NOT_CNULLPTR(uint16_array_tofu);
    fscl_tofu_erase(uint16_array_tofu);

    // 32-bit Unsigned Integer array type
    ctofu* uint32_array_tofu = fscl_tofu_create_array(TOFU_UINT_TYPE, 3, 32, 64, 128);
    TEST_ASSUME_NOT_CNULLPTR(uint32_array_tofu);
    fscl_tofu_erase(uint32_array_tofu);

    // 64-bit Unsigned Integer array type
    ctofu* uint64_array_tofu = fscl_tofu_create_array(TOFU_UINT_TYPE, 3, 64, 128, 256);
    TEST_ASSUME_NOT_CNULLPTR(uint64_array_tofu);
    fscl_tofu_erase(uint64_array_tofu);

    // Octal 8-bit array type
    ctofu* octal8_array_tofu = fscl_tofu_create_array(TOFU_OCTAL_TYPE, 3, 075, 064, 055);
    TEST_ASSUME_NOT_CNULLPTR(octal8_array_tofu);
    fscl_tofu_erase(octal8_array_tofu);

    // Octal 16-bit array type
    ctofu* octal16_array_tofu = fscl_tofu_create_array(TOFU_OCTAL_TYPE, 3, 0755, 0755, 0755);
    TEST_ASSUME_NOT_CNULLPTR(octal16_array_tofu);
    fscl_tofu_erase(octal16_array_tofu);

    // Octal 32-bit array type
    ctofu* octal32_array_tofu = fscl_tofu_create_array(TOFU_OCTAL_TYPE, 3, 0755, 0755, 0755);
    TEST_ASSUME_NOT_CNULLPTR(octal32_array_tofu);
    fscl_tofu_erase(octal32_array_tofu);

    // Octal 64-bit array type
    ctofu* octal64_array_tofu = fscl_tofu_create_array(TOFU_OCTAL_TYPE, 3, 0755, 0755, 0755);
    TEST_ASSUME_NOT_CNULLPTR(octal64_array_tofu);
    fscl_tofu_erase(octal64_array_tofu);

    // Bitwise 8-bit array type
    ctofu* bitwise8_array_tofu = fscl_tofu_create_array(TOFU_BITWISE_TYPE, 3, 0b1010, 0b0101, 0b1100);
    TEST_ASSUME_NOT_CNULLPTR(bitwise8_array_tofu);
    fscl_tofu_erase(bitwise8_array_tofu);

    // Bitwise 16-bit array type
    ctofu* bitwise16_array_tofu = fscl_tofu_create_array(TOFU_BITWISE_TYPE, 3, 0b10101010, 0b01010101, 0b11110000);
    TEST_ASSUME_NOT_CNULLPTR(bitwise16_array_tofu);
    fscl_tofu_erase(bitwise16_array_tofu);

    // Bitwise 32-bit array type
    ctofu* bitwise32_array_tofu = fscl_tofu_create_array(TOFU_BITWISE_TYPE, 3, 0b1010101010101010, 0b0101010101010101, 0b1111000011110000);
    TEST_ASSUME_NOT_CNULLPTR(bitwise32_array_tofu);
    fscl_tofu_erase(bitwise32_array_tofu);

    // Bitwise 64-bit array type
    ctofu* bitwise64_array_tofu = fscl_tofu_create_array(TOFU_BITWISE_TYPE, 3, 0b10101010101010101010101010101010, 0b01010101010101010101010101010101, 0b11110000111100001111000011110000);
    TEST_ASSUME_NOT_CNULLPTR(bitwise64_array_tofu);
    fscl_tofu_erase(bitwise64_array_tofu);

    // Hexadecimal 8-bit array type
    ctofu* hex8_array_tofu = fscl_tofu_create_array(TOFU_HEX_TYPE, 3, 0x1F, 0x2A, 0x3C);
    TEST_ASSUME_NOT_CNULLPTR(hex8_array_tofu);
    fscl_tofu_erase(hex8_array_tofu);

    // Hexadecimal 16-bit array type
    ctofu* hex16_array_tofu = fscl_tofu_create_array(TOFU_HEX_TYPE, 3, 0x1F2A, 0x2A3C, 0x3C1F);
    TEST_ASSUME_NOT_CNULLPTR(hex16_array_tofu);
    fscl_tofu_erase(hex16_array_tofu);

    // Hexadecimal 32-bit array type
    ctofu* hex32_array_tofu = fscl_tofu_create_array(TOFU_HEX_TYPE, 3, 0x1F2A3C4D, 0x2A3C4D5E, 0x3C4D5E6F);
    TEST_ASSUME_NOT_CNULLPTR(hex32_array_tofu);
    fscl_tofu_erase(hex32_array_tofu);

    // Hexadecimal 64-bit array type
    ctofu* hex64_array_tofu = fscl_tofu_create_array(TOFU_HEX_TYPE, 3, 0x1F2A3C4D5E6F7A8B, 0x2A3C4D5E6F7A8B9C, 0x3C4D5E6F7A8B9C0D);
    TEST_ASSUME_NOT_CNULLPTR(hex64_array_tofu);
    fscl_tofu_erase(hex64_array_tofu);

    // Floating-point array type (double)
    ctofu* double_array_tofu = fscl_tofu_create_array(TOFU_DOUBLE_TYPE, 3, 3.14, 2.71, 1.618);
    TEST_ASSUME_NOT_CNULLPTR(double_array_tofu);
    fscl_tofu_erase(double_array_tofu);

    // Floating-point array type (float)
    ctofu* float_array_tofu = fscl_tofu_create_array(TOFU_FLOAT_TYPE, 3, 3.14f, 2.71f, 1.618f);
    TEST_ASSUME_NOT_CNULLPTR(float_array_tofu);
    fscl_tofu_erase(float_array_tofu);

    // String array type
    ctofu* string_array_tofu = fscl_tofu_create_array(TOFU_STRING_TYPE, 3, "apple", "banana", "cherry");
    TEST_ASSUME_NOT_CNULLPTR(string_array_tofu);
    fscl_tofu_erase(string_array_tofu);

    // Character array type
    ctofu* char_array_tofu = fscl_tofu_create_array(TOFU_CHAR_TYPE, 3, 'A', 'B', 'C');
    TEST_ASSUME_NOT_CNULLPTR(char_array_tofu);
    fscl_tofu_erase(char_array_tofu);

    // Boolean array type
    ctofu* boolean_array_tofu = fscl_tofu_create_array(TOFU_BOOLEAN_TYPE, 3, true, false, true);
    TEST_ASSUME_NOT_CNULLPTR(boolean_array_tofu);
    fscl_tofu_erase(boolean_array_tofu);

    // Quantum bit array type (64-bit)
    ctofu* qbit_array_tofu = fscl_tofu_create_array(TOFU_QBIT_TYPE, 3, 0b11011010, 0b10101010, 0b01010101);
    TEST_ASSUME_NOT_CNULLPTR(qbit_array_tofu);
    fscl_tofu_erase(qbit_array_tofu);

    // Null pointer array type
    ctofu* nullptr_array_tofu = fscl_tofu_create_array(TOFU_NULLPTR_TYPE, 3, NULL, NULL, NULL);
    TEST_ASSUME_NOT_CNULLPTR(nullptr_array_tofu);
    fscl_tofu_erase(nullptr_array_tofu);

    // Invalid array type (Unknown type)
    ctofu* invalid_array_tofu = fscl_tofu_create_array(TOFU_INVALID_TYPE, 3, NULL, NULL, NULL);
    TEST_ASSUME_CNULLPTR(invalid_array_tofu);

    // Unknown array type
    ctofu* unknown_array_tofu = fscl_tofu_create_array(TOFU_UNKNOWN_TYPE, 3, NULL, NULL, NULL);
    TEST_ASSUME_CNULLPTR(unknown_array_tofu);

    // Fixed point array type
    ctofu* fixed_array_tofu = fscl_tofu_create_array(TOFU_FIXED_TYPE, 3, 3.14, 2.71, 1.618);
    TEST_ASSUME_NOT_CNULLPTR(fixed_array_tofu);
}

XTEST(test_type_mismatch) {
    // Create a "tofu" structure with one type
    ctofu* tofu = fscl_tofu_create(TOFU_INT_TYPE, NULL);
    TEST_ASSUME_NOT_CNULLPTR(tofu);

    // Try to apply an operation with a different type
    ctofu* wrong_type = fscl_tofu_create(TOFU_FLOAT_TYPE, NULL);
    ctofu_error result = fscl_tofu_compare(tofu, wrong_type);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_INVALID_OPERATION, result);

    // Clean up
    fscl_tofu_erase(tofu);
    fscl_tofu_erase(wrong_type);
}

XTEST(test_accumulate) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test accumulate
    ctofu_error accumulate_result = fscl_tofu_accumulate(array);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, accumulate_result);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_transform) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test transform
    ctofu_error transform_result = fscl_tofu_transform(array, square_transform_function);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, transform_result);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_sort) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test sort
    ctofu_error sort_result = fscl_tofu_sort(array);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, sort_result);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_search) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test search
    ctofu* key = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 8});
    ctofu_error search_result = fscl_tofu_search(array, key);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, search_result);
    fscl_tofu_erase(key);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_filter) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test filter
    ctofu_error filter_result = fscl_tofu_filter(array, even_filter_function);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, filter_result);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_reverse) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test reverse
    ctofu_error reverse_result = fscl_tofu_reverse(array);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, reverse_result);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_swap) {
    // Create two "tofu" structures with initial values
    ctofu* tofu1 = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 5});
    ctofu* tofu2 = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 8});

    // Test swap
    ctofu_error swap_result = fscl_tofu_swap(tofu1, tofu2);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, swap_result);

    // Clean up
    fscl_tofu_erase(tofu1);
    fscl_tofu_erase(tofu2);
}

XTEST(test_compare) {
    // Create two "tofu" structures with initial values
    ctofu* tofu1 = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 5});
    ctofu* tofu2 = fscl_tofu_create(TOFU_INT_TYPE, &(ctofu_data){.int_type = 8});

    // Test compare
    ctofu_error compare_result = fscl_tofu_compare(tofu1, tofu2);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, compare_result);

    // Clean up
    fscl_tofu_erase(tofu1);
    fscl_tofu_erase(tofu2);
}

XTEST(test_reduce) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test reduce
    ctofu_error reduce_result = fscl_tofu_reduce(array, sum_reduce_function);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, reduce_result);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_shuffle) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test shuffle
    ctofu_error shuffle_result = fscl_tofu_shuffle(array);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, shuffle_result);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_for_each) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test for_each
    ctofu_error for_each_result = fscl_tofu_for_each(array, out_element_function);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, for_each_result);

    // Clean up
    fscl_tofu_erase_array(array);
}

XTEST(test_partition) {
    // Create a "tofu" array with initial values
    ctofu* array = fscl_tofu_create_array(TOFU_INT_TYPE, 5, 5, 3, 8, 1, 7);

    // Test partition
    ctofu* partitionedResults[2];
    ctofu_error partition_result = fscl_tofu_partition(array, even_partition_function, partitionedResults);
    TEST_ASSUME_EQUAL(FSCL_TOFU_ERROR_OK, partition_result);

    // Clean up
    fscl_tofu_erase_array(array);
}


//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(tofu_type_group) {
    XTEST_RUN_UNIT(test_create_and_erase);
    XTEST_RUN_UNIT(test_create_array_all_types);
    XTEST_RUN_UNIT(test_type_mismatch);
    XTEST_RUN_UNIT(test_accumulate);
    XTEST_RUN_UNIT(test_transform);
    XTEST_RUN_UNIT(test_sort);
    XTEST_RUN_UNIT(test_search);
    XTEST_RUN_UNIT(test_filter);
    XTEST_RUN_UNIT(test_reverse);
    XTEST_RUN_UNIT(test_swap);
    XTEST_RUN_UNIT(test_compare);
    XTEST_RUN_UNIT(test_reduce);
    XTEST_RUN_UNIT(test_shuffle);
    XTEST_RUN_UNIT(test_for_each);
    XTEST_RUN_UNIT(test_partition);

} // end of xdata_test_tofu_group
