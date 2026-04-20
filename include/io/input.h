/**
 * @file input.h
 * 
 * @brief Provides simple standard inputs. Usage is similar to the scanf function.
 * 
 * @author Bruno Silva (bruno.silva@estsetubal.ips.pt) - Original Version
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2021 Bruno Silva
 * Modifications and Refactor (c) 2026 Filipe Paredes
 * 
 * @bug No known bugs.
 */

#pragma once

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Read an integer from standard input.
 * 
 * @param val [out] address of variable to hold the value
 * 
 * @return true if a valid integer was parsed
 * @return false otherwise
 */
bool read_integer(int *val);

/**
 * @brief Read a double from standard input.
 * 
 * @param val [out] address of variable to hold the value
 * 
 * @return true if a valid double was parsed
 * @return false otherwise
 */
bool read_double(double *val);

/**
 * @brief Read a char from standard input.
 * 
 * Only the first character is consumed.
 * 
 * @param val [out] address of variable to hold the value
 * 
 * @return true if a valid char was parsed
 * @return false otherwise
 */
bool read_char(char *val);

/**
 * @brief Reads a "string" from standard input.
 * 
 * @param char_arr [out] address of array to hold the text
 * @param max_size [in] maximum characters to read. 
 *                      char_arr must have at least this size.
 */
void read_string(char *char_arr, size_t max_size);

/**
 * @brief Splits a string given a delimiter.
 * 
 * This function modifies the parameter 'string', replacing
 * delimiter occurrences by '\0' and returns and array of pointers
 * to each invidual tokens.
 * 
 * This array must be free'd by the caller.
 * 
 * @param string [in] the string to split
 * @param n_tokens [in] number of required tokens. If there are
 *                      less tokens than specified, then NULL
 *                      is used for subsequent tokens.
 * @param delim [in] delimiter, usually a single character
 * @return char** pointer array (of size nFields) to string "tokens".
 */
char **split_string(char *string, int n_tokens, const char *delim);

