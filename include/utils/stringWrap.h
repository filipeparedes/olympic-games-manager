/**
 * @file stringWrap.h
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * @brief Header file for string wrapping operations.
 * 
 * This file contains the declaration of the StringWrap struct and the function
 * for creating a wrapped string.
 */
#pragma once
#define STRING_MAX_LEN 50

/**
 * @brief Struct to wrap a string.
 * 
 * This struct holds a single string and is used to encapsulate string operations.
 * 
 */
typedef struct stringWrap {
    char text[STRING_MAX_LEN];
} StringWrap;

/**
 * @brief Creates a wrapped string.
 * 
 * @param str Pointer to the input string to be wrapped. The input string length
 *            must be less than STRING_MAX_LEN.
 * 
 * @return StringWrap The initialized StringWrap struct containing the input string.
 */
StringWrap stringWrapCreate(char *str);
