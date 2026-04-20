/**
 * @file list_array_list.c
 * 
 * @brief Provides an implementation of the ADT List with an array list
 * as the underlying data structure.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com) - Original Version
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#include "adt/list.h"
#include "adt/list_elem.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 20

typedef struct list {
	list_elem_t* elements;
	int size; 
	int capacity;
} list_t;


static bool ensure_capacity(list_t *list) {
	if (list->size == list->capacity) {
		int newCapacity = list->capacity * 2;
		list_elem_t* newArray = (list_elem_t*) realloc( list->elements, 
								newCapacity * sizeof(list_elem_t) );
		
		if(newArray == NULL) return false;

		list->elements = newArray;
		list->capacity = newCapacity;
	}
	
	return true;
}

list_t *list_create() {
	list_t *list = (list_t*)malloc(sizeof(list_t));
	if (list == NULL) return NULL;

	list->elements = (list_elem_t*)calloc(INITIAL_CAPACITY,
										sizeof(list_elem_t));

	if (list->elements == NULL) {
		free(list);
		return NULL;	
	}

	list->size = 0;
	list->capacity = INITIAL_CAPACITY;

	return list;
}

int list_destroy(list_t **list) {
	if (list == NULL || *list == NULL) return LIST_NULL;

	free((*list)->elements);
	free(list);

	*list = NULL;

	return LIST_OK;
}

int list_add(list_t *list, int rank, list_elem_t elem) {
	if (list == NULL) return LIST_NULL;
	if (rank < 0 || rank > list->size) return LIST_INVALID_RANK;

	if(!ensureCapacity(list)) return LIST_NO_MEMORY;

	/* make room for new element at index 'rank' */
	for(int i = list->size; i > rank; i--) {
		list->elements[i] = list->elements[i-1];
	}

	list->elements[rank] = elem;

	list->size++;

	return LIST_OK;
}

int list_remove(list_t *list, int rank, list_elem_t *elem) {
	if (list == NULL) return LIST_NULL;
	if (list->size == 0) return LIST_EMPTY;
	if (rank < 0 || rank > list->size - 1) return LIST_INVALID_RANK;

	*elem = list->elements[rank];

	/* close the gap at this rank */
	for(int i = rank; i< list->size - 1; i++) {
		list->elements[i] = list->elements[i+1];
	}

	list->size--;

	return LIST_OK;
}

int list_get(list_t *list, int rank, list_elem_t *elem) {
	if (list == NULL) return LIST_NULL;
	if (rank < 0 || rank > list->size - 1) return LIST_INVALID_RANK;

	*elem = list->elements[rank];

	return LIST_OK;
}

int list_set(list_t *list, int rank, list_elem_t elem, list_elem_t *old_elem) {
	if (list == NULL) return LIST_NULL;
	if (rank < 0 || rank > list->size - 1) return LIST_INVALID_RANK;

	*old_elem = list->elements[rank];

	list->elements[rank] = elem;

	return LIST_OK;
}

int list_size(list_t *list, int *size) {
	if (list == NULL) return LIST_NULL;

	*size = list->size;

	return LIST_OK;
}

bool list_is_empty(list_t *list) {
	if (list == NULL) return 1;

	return (list->size == 0);
}

int list_clear(list_t *list) {
	if (list == NULL) return LIST_NULL;

	list->size = 0;

	return LIST_OK;
}
void list_print(list_t *list) {
	if (list == NULL) {
		printf("(List NULL)\n");
	}
	else if (list->size == 0) {
		printf("(List EMPTY)\n");
	}
	else {
		printf("List contents (by rank): \n");
		for(int rank = 0; rank < list->size; rank++) {
			printf("Rank %d: \n", rank);
			list_elem_print(list->elements[rank]);
			printf("\n");
		}
	}
	printf("\n");
}