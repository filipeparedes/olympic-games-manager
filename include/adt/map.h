/**
 * @file map.h
 * @brief Definition of the ADT Map in C.
 * 
 * Defines the type map_t and associated operations.
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

// Error codes
#define MAP_OK            0
#define MAP_NULL          1
#define MAP_NO_MEMORY     2
#define MAP_EMPTY         3
#define MAP_FULL          4
#define MAP_UNKNOWN_KEY	  5

#include "adt/map_elem.h"
#include <stdbool.h>

typedef struct map map_t;

/**
 * @brief Creates a new empty map.
 * 
 * @return map_t pointer to allocated data structure, or
 * @return NULL if unsufficient memory for allocation
 */
map_t *map_create();

/**
 * @brief Free all resources of a map.
 * 
 * @param map [in] ADDRESS OF pointer to the map
 * 
 * @return MAP_OK if success, or
 * @return MAP_NULL if 'map' is NULL 
 */
int map_destroy(map_t **map);

/**
 * @brief Add a key-value mapping to a map.
 * 
 * If 'key' already exists, the currently
 * mapped value is silently replaced by 'value'
 * 
 * @param map [in] pointer to the map
 * @param key [in] key 
 * @param value  [in] value
 * 
 * @return MAP_OK if successful, or
 * @return MAP_UNKNOWN_KEY if 'key' doesn't exist, or
 * @return MAP_FULL if no capacity available, or
 * @return MAP_NO_MEMORY if unsufficient memory for allocation, or
 * @return MAP_NULL if 'map' is NULL 
 */
int map_put(map_t *map, map_key_t key, map_value_t value);

/**
 * @brief Removes a mapping from a map.
 * 
 * The function returns the value associated with 'key'
 * and removes 'key' from the map if the operation is
 * successful.
 * 
 * The specified key must exist.
 * 
 * @param map [in] pointer to the map
 * @param key [in] key for removal
 * @param value [out] address of variable to hold the value
 * 
 * @return MAP_OK if successful and value in 'value', or
 * @return MAP_UNKNOWN_KEY if 'key' doesn't exist, or
 * @return MAP_EMPTY if the map is empty, or
 * @return MAP_NULL if 'map' is NULL 
 */
int map_remove(map_t *map, map_key_t key, map_value_t *value);

/**
 * @brief Retrieves ther value associated with
 * a key from a map.
 * 
 * The specified key must exist.
 * 
 * @param map [in] pointer to the map
 * @param key [in] key for retrieval
 * @param value [out] address of variable to hold the value
 * 
 * @return MAP_OK if successful and value in 'value', or
 * @return MAP_UNKNOWN_KEY if 'key' doesn't exist, or
 * @return MAP_EMPTY if the map is empty, or
 * @return MAP_NULL if 'map' is NULL 
 */
int map_get(map_t *map, map_key_t key, map_value_t *value);

/**
 * @brief Checks whether a map contains a key.
 * 
 * @param map [in] pointer to the map
 * @param key [in] key to check
 * 
 * @return 'true' if 'key' exists, or
 * @return 'false' if 'key' doesn't exist or 'map' is NULL
 */
bool map_contains(map_t *map, map_key_t key);

/**
 * @brief Retrieves the set of keys of a map.
 * 
 * This function returns a dynamically allocated array
 * with length equal to the size of the map, containing
 * the keys of the map in no particular order.
 * 
 * The caller is responsible for deallocating 
 * (freeing) the array. 
 * 
 * @param map [in] pointer to the map
 * 
 * @return array containing the keys
 * @return NULL if 'map' is empty or NULL
 */
map_key_t *map_keys(map_t *map);

/**
 * @brief Retrieves the set of values of a map.
 * 
 * This function returns a dynamically allocated array
 * with length equal to the size of the map, containing
 * the values of the map in no particular order.
 * 
 * The caller is responsible for deallocating 
 * (freeing) the array. 
 * 
 * @param map [in] pointer to the map
 * 
 * @return array containing the values
 * @return NULL if 'map' is empty or NULL
 */
map_value_t* map_values(map_t *map);

/**
 * @brief Retrieves the size of a map.
 * 
 * @param map [in] pointer to the map
 * @param size [out] address of variable to hold the value
 * 
 * @return MAP_OK if successful and value in 'ptSize', or
 * @return MAP_NULL if 'map' is NULL 
 */
int map_size(map_t *map, int *size);

/**
 * @brief Checks whether a map is empty.
 * 
 * @param map [in] pointer to the map
 * 
 * @return 'true' if empty or if 'map' is NULL, or
 * @return 'false' it not empty
 */
bool map_is_empty(map_t *map);

/**
 * @brief Clears the contents of a map.
 * 
 * This operation will remove all current valueents in the map,
 * returning to an empty state.
 * 
 * @param map [in] pointer to the map
 * 
 * @return MAP_OK if successful, or
 * @return MAP_NULL if 'map' is NULL 
 */
int map_clear(map_t *map);

/**
 * @brief Prints the contents of a map.
 * 
 * @param map [in] pointer to the map
 */
void map_print(map_t *map);

