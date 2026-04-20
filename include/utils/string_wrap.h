/**
 * @file string_wrap.h
 * 
 * @brief Header file for string wrapping operations.
 * 
 * This file contains the declaration of the string_wrap_t struct and the function
 * for creating a wrapped string.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */
#pragma once
#define STRING_MAX_LEN 50

/**
 * @brief Struct to wrap a string.
 * 
 * This struct holds a single string and is used to encapsulate string operations.
 * 
 */
typedef struct string_wrap {
    char text[STRING_MAX_LEN];
} string_wrap_t;

/**
 * @brief Creates a wrapped string.
 * 
 * @param str Pointer to the input string to be wrapped. The input string length
 *            must be less than STRING_MAX_LEN.
 * 
 * @return string_wrap_t The initialized string_wrap_t struct containing the input string.
 */
string_wrap_t string_wrap_create(char *str);
