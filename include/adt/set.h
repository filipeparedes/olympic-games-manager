/**
 * @file set.h
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Definition of the ADT Set in C. Defines the type PtSet and associated operations.
 * @version 0.3
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#define SET_OK				0
#define SET_NULL			1
#define SET_NO_MEMORY		2
#define SET_EMPTY			3
#define SET_FULL			4
#define SET_DUPLICATE       5
#define SET_MISSING_ELEM    6

#include "adt/setElem.h"
#include <string.h>
#include <stdbool.h>

/** Forward declaration of the data structure. */
struct setImpl;

/** Definition of pointer to the  data stucture. */
typedef struct setImpl *PtSet;

/**
 * @brief Creates a new empty set.
 * 
 * @return PtSet pointer to allocated data structure
 * @return NULL if unsufficient memory for allocation
 */
PtSet setCreate();

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
int setAdd(PtSet set, SetElem elem);

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
int setRemove(PtSet set, SetElem elem);

/**
 * @brief Checks if a set contains a certain element
 * 
 * @param set pointer to the set
 * @param elem elem to look for
 * 
 * @return true if the set contains the element
 * @return false  if the set does not contain the element
 */
bool setContains(PtSet set, SetElem elem);

/**
 * @brief Retrieves the size of a set
 * 
 * @param set pointer to the list
 * @param ptSize [out] address of an integer variable to store the value
 * 
 * @return SET_OK if successful
 * @return SET_NULL if set is NULL
 */
int setSize(PtSet set, int *ptSize);

/**
 * @brief Checks if a set is a subset of another set
 * 
 * @param subSet pointer to the subSet
 * @param set pointer to the set that could contain the subSet
 * 
 * @return true if "subSet" is a subset of "set"
 * @return false if "subSet" is not a subset of "set"
 */
bool setSubset(PtSet subSet, PtSet set);

/**
 * @brief Checks if a set is empty
 * 
 * @param set pointer to the set
 * 
 * @return true if set is empty or NULL
 * @return false if set is not empty
 */
bool isSetEmpty(PtSet set);

/**
 * @brief Clears the content of a set.
 * 
 * @param set pointer to the set
 * 
 * @return SET_OK if successful
 * @return SET_NULL if set is NULL
 */
int setClear(PtSet set);

/**
 * @brief Retrieves all the values of the set in an array
 * 
 * @param set pointer to the set
 * 
 * @return an array with the values
 * @return NULL if set is NULL
 */
SetElem* setValues(PtSet set);


/**
 * @brief Prints the content of a set
 * 
 * @param set pointer to the set
 */
void setPrint(PtSet set);

/**
 * @brief Free all resources of a set.
 * 
 * @param ptSet address of pointer to the set
 * 
 * @returns SET_OK if success
 * @returns SET_NULL if set is NULL
 */
int setDestroy(PtSet *ptSet);