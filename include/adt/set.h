/**
 * @file set.h
 * 
 * @brief Definition of the ADT Set in C. Defines the type set_t and associated operations.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

// Error codes
#define SET_OK				0
#define SET_NULL			1
#define SET_NO_MEMORY		2
#define SET_EMPTY			3
#define SET_FULL			4
#define SET_DUPLICATE       5
#define SET_MISSING_ELEM    6

#include "adt/set_elem.h"
#include <string.h>
#include <stdbool.h>


typedef struct set set_t;

/**
 * @brief Creates a new empty set.
 * 
 * @return set_t pointer to allocated data structure
 * @return NULL if unsufficient memory for allocation
 */
set_t *set_create();

/**
 * @brief Adds an element to a set if it isn't already present
 * 
 * @param set pointer to the set
 * @param elem element to add
 * 
 * @return SET_OK if successful
 * @return SET_FULL if no capacity available
 * @return SET_NO_MEMORY if unsufficient memory for allocation
 * @return SET_NULL if set is null
 * @return SET_DUPLICATE if the element is already present in the set
 */
int set_add(set_t *set, set_elem_t elem);

/**
 * @brief Removes an object from a set if it exists
 * 
 ** @param set pointer to the set
 * @param elem element to remove
 * 
 * @return SET_OK if successful
 * @return SET_EMPTY if the set is empty
 * @return SET_NULL if set is null
 * @return SET_MISSING_ELEM if the element does not exist in the set
 */
int set_remove(set_t *set, set_elem_t elem);

/**
 * @brief Checks if a set contains a certain element
 * 
 * @param set pointer to the set
 * @param elem elem to look for
 * 
 * @return true if the set contains the element
 * @return false  if the set does not contain the element
 */
bool set_contains(set_t *set, set_elem_t elem);

/**
 * @brief Retrieves the size of a set
 * 
 * @param set pointer to the list
 * @param size [out] address of an integer variable to store the value
 * 
 * @return SET_OK if successful
 * @return SET_NULL if set is NULL
 */
int set_size(set_t *set, int *size);

/**
 * @brief Checks if a set is a subset of another set
 * 
 * @param subset pointer to the subset
 * @param set pointer to the set that could contain the subset
 * 
 * @return true if "subSet" is a subset of "set"
 * @return false if "subSet" is not a subset of "set"
 */
bool set_subset(set_t *subset, set_t *set);

/**
 * @brief Checks if a set is empty
 * 
 * @param set pointer to the set
 * 
 * @return true if set is empty or NULL
 * @return false if set is not empty
 */
bool is_set_empty(set_t *set);

/**
 * @brief Clears the content of a set.
 * 
 * @param set pointer to the set
 * 
 * @return SET_OK if successful
 * @return SET_NULL if set is NULL
 */
int set_clear(set_t *set);

/**
 * @brief Retrieves all the values of the set in an array
 * 
 * @param set pointer to the set
 * 
 * @return an array with the values
 * @return NULL if set is NULL
 */
set_elem_t *set_values(set_t *set);


/**
 * @brief Prints the content of a set
 * 
 * @param set pointer to the set
 */
void set_print(set_t *set);

/**
 * @brief Free all resources of a set.
 * 
 * @param set address of pointer to the set
 * 
 * @returns SET_OK if success
 * @returns SET_NULL if set is NULL
 */
int set_destroy(set_t *set);