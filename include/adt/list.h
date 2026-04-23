/**
 * @file list.h
 * @brief Definition of the ADT List in C.
 * 
 * Defines the type list_t and associated operations.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com) - Original Version
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.1.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

// Error codes
#define LIST_OK				0
#define LIST_NULL			1
#define LIST_NO_MEMORY		2
#define LIST_EMPTY			3
#define LIST_FULL			4
#define LIST_INVALID_RANK	5

#include "list_elem.h"
#include <stdbool.h>

typedef struct list list_t;

/**
 * @brief Creates a new empty list.
 * 
 * @return list_t pointer to allocated data structure, or
 * @return NULL if unsufficient memory for allocation
 */
list_t *list_create();

/**
 * @brief Free all resources of a list.
 * 
 * @param list [in] ADDRESS OF pointer to the list
 * 
 * @return LIST_OK if success, or
 * @return LIST_NULL if '*ptList' is NULL 
 */
int list_destroy(list_t **list);

/**
 * @brief Add an element to a list.
 * 
 * The specified rank must be in [0, size].
 * 
 * @param list [in] pointer to the list
 * @param rank [in] rank for insertion
 * @param elem  [in] element to add
 * 
 * @return LIST_OK if successful, or
 * @return LIST_INVALID_RANK if 'rank' is invalid, or
 * @return LIST_FULL if no capacity available, or
 * @return LIST_NO_MEMORY if unsufficient memory for allocation, or
 * @return LIST_NULL if 'list' is NULL 
 */
int list_add(list_t *list, int rank, list_elem_t elem);

/**
 * @brief Removes an element from a list.
 * 
 * The specified rank must be in [0, size - 1].
 * 
 * @param list [in] pointer to the list
 * @param rank [in] rank for removal
 * @param elem [out] address of variable to hold the value
 * 
 * @return LIST_OK if successful and value in 'elem', or
 * @return LIST_INVALID_RANK if 'rank' is invalid, or
 * @return LIST_EMPTY if the list is empty, or
 * @return LIST_NULL if 'list' is NULL 
 */
int list_remove(list_t *list, int rank, list_elem_t *elem);

/**
 * @brief Retrieves an element from a list.
 * 
 * The specified rank must be in [0, size - 1].
 * 
 * @param list [in] pointer to the list
 * @param rank [in] rank for retrieval
 * @param elem [out] address of variable to hold the value
 * 
 * @return LIST_OK if successful and value in 'elem', or
 * @return LIST_INVALID_RANK if 'rank' is invalid, or
 * @return LIST_EMPTY if the list is empty, or
 * @return LIST_NULL if 'list' is NULL 
 */
int list_get(list_t *list, int rank, list_elem_t *elem);

/**
 * @brief Replaces an element from a list.
 * 
 * The specified rank must be in [0, size - 1].
 * This function replaces an element in the specified rank
 * and returns the previous element at that rank.
 * 
 * @param list [in] pointer to the list
 * @param rank [in] rank for replacement
 * @param elem  [in] element to put at the specified tank
 * @param old_elem [out] address of variable to hold the previous element
 * 
 * @return LIST_OK if successful and previous value in 'old_elem', or
 * @return LIST_INVALID_RANK if 'rank' is invalid, or
 * @return LIST_EMPTY if the list is empty, or
 * @return LIST_NULL if 'list' is NULL 
 */
int list_set(list_t *list, int rank, list_elem_t elem, list_elem_t *old_elem);

/**
 * @brief Retrieves the size of a list.
 * 
 * @param list [in] pointer to the list
 * @param size [out] address of variable to hold the value
 * 
 * @return LIST_OK if successful and value in 'ptSize', or
 * @return LIST_NULL if 'list' is NULL 
 */
int list_size(list_t *list, int *size);

/**
 * @brief Checks whether a list is empty.
 * 
 * @param list [in] pointer to the list
 * 
 * @return 'true' if empty or if 'list' is NULL, or
 * @return 'false' it not empty
 */
bool list_is_empty(list_t *list);

/**
 * @brief Clears the contents of a list.
 * 
 * This operation will remove all current elements in the list,
 * returning to an empty state.
 * 
 * @param list [in] pointer to the list
 * 
 * @return LIST_OK if successful, or
 * @return LIST_NULL if 'list' is NULL 
 */
int list_clear(list_t *list);

/**
 * @brief Sort the list using qsort()
 * 
 * @param athletes the list to sort
 * @return list_t the sorted ist
 */
list_t *list_sort(list_t *athletes);

/**
 * @brief Prints the contents of a list.
 * 
 * @param list [in] pointer to the list
 */
void list_print(list_t *list);

