/**
 * @file map_elem.h
 * @brief Defines the types map_key_t and map_value_t.
 * 
 * The map_key_t is an alias to the type of keys 
 * held by an instance of the ADT Map (map_t).
 * 
 * The map_value_t is an alias to the type of values 
 * held by an instance of the ADT Map (map_t).
 *  
 * These aliases must be changed according to the use-case.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com) - Original Version
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#include <stdbool.h>

#include "domain/host.h"
#include "utils/string_wrap.h"

/** Key type definition. Change according to the use-case. */
typedef string_wrap_t map_key_t;

/** Value type definition. Change according to the use-case. */
typedef host_t map_value_t;

/**
 * @brief Prints a key.
 * 
 * Must be implemented according to the concrete
 * type of MapKey.
 * 
 * @param key [in] key to print
 */
void map_key_print(map_key_t key);

/**
 * @brief Prints a value.
 * 
 * Must be implemented according to the concrete
 * type of map_value_t.
 * 
 * @param value [in] value to print
 */
void map_value_print(map_value_t value);

/**
 * @brief Compares two keys.
 * 
 * This function provides the comparison criteria
 * between two keys.
 * 
 * @param key1 [in] a key
 * @param key2 [in] another key
 * @return 0 if they are equal.
 * @return value less than 0, if 'key1' is less than 'key2' 
 * @return value greater than 0 if 'key1' is greater than 'key2' 
 */
int map_key_compare(map_key_t key1, map_key_t key2);

