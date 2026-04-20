/**
 * @file set_linked_list.c
 * 
 * @brief Provides an implementation of the ADT Set with a linked list as the underlying data structure.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2026
 * 
 * @bug No known bugs.
 */

#include "adt/set.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

typedef struct node node_t;

bool set_contains(set_t *set, set_elem_t elem);

typedef struct node {
    set_elem_t element;
    node_t *next, *prev;
} node_t;

typedef struct set {
    node_t *header, *trailer;
    int size;
} set_t;

set_t *set_create() {
    set_t *set = (set_t*) malloc(sizeof(set_t));
    if (set == NULL) return NULL;

    set->header = (node_t*)malloc(sizeof(node_t));
    set->trailer = (node_t*)malloc(sizeof(node_t));

    if (set->header == NULL || set->trailer == NULL) {
        free(set->header);
        free(set->trailer);
        free(set);
        return NULL;
    }

    set->header->next = set->trailer;
    set->header->prev = NULL;

    set->trailer->prev = set->header;
    set->trailer->next = NULL;

    set->size = 0;

    return set;
}

int set_add(set_t *set, set_elem_t elem) {
    if (set == NULL) return SET_NULL;
    if (set_contains(set, elem)) return SET_DUPLICATE;

    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) return SET_NO_MEMORY;

    new_node->element = elem;
    new_node->next = set->trailer;
    new_node->prev = set->trailer->prev;
    set->trailer->prev->next = new_node;
    set->trailer->prev = new_node;

    set->size++;

    return SET_OK;
}

int set_remove(set_t *set, set_elem_t elem){
    if (set == NULL) return SET_NULL;
    if (!set_contains(set, elem)) return SET_MISSING_ELEM;

    node_t *curr = set->header->next;
    while (curr != set->trailer && strcmp(curr->element.discipline_name, elem.discipline_name) != 0) {
        curr =  curr->next;
    }

    if (curr == set->trailer) return SET_MISSING_ELEM; 

    node_t *prev = curr->prev;
    node_t *next = curr->next;
    prev->next = next;
    next->prev = prev;

    free(curr);

    set->size--;

    return SET_OK;
}

bool set_contains(set_t *set, set_elem_t elem){
    if (set == NULL) return false;
    if (set->size == 0) return false;

    node_t *curr = set->header->next;
    while (curr != set->trailer) {
        if (strcmp(curr->element.discipline_name,elem.discipline_name) == 0) return true;
        curr = curr->next;
    }

    return false;
}

int set_size(set_t *set, int *size) {
    if (set == NULL) return SET_NULL;

    *size = set->size;

    return SET_OK;
}

bool set_subset(set_t *subset, set_t *set) {
    if (subset == NULL || set == NULL) return false;
    if (subset->size == 0) return true;
    if (set->size == 0) return false;

    node_t *sub_curr = subset->header->next;

    while (sub_curr != subset->trailer) {
        if (!set_contains(set, sub_curr->element)) return false;
        sub_curr = sub_curr->next;
    }

    return true;
}

bool is_set_empty(set_t *set){
    if (set == NULL) return true;

    return (set->size == 0);
}

int set_clear(set_t *set) {
    if (set == NULL) return SET_NULL;

    node_t *curr = set->header->next;
    while (curr != set->trailer) {
        node_t *to_free = curr;
        curr = curr->next;
        free(to_free);
    }

    set->header->next = set->trailer;
    set->trailer->prev = set->header;

    set->size = 0;

    return SET_OK;
}

set_elem_t *set_values(set_t *set){
    if (set == NULL || set->size == 0) return NULL;

    set_elem_t *array = (set_elem_t*)malloc(set->size * sizeof(set_elem_t));
    if (array == NULL) return NULL;

    int count = 0;

    node_t *curr = set->header->next;
    while (curr != set->trailer) {
        array[count] = curr->element;
        count++;
        curr = curr->next;
    }

    return array;
}

void set_print(set_t *set) {
    if (set == NULL) printf("SET NULL\n");
    else if (set->size == 0) printf("SET EMPTY\n");
    else {
        node_t *curr = set->header->next;
        while(curr != set->trailer) {
            set_elem_print(curr->element);
            printf("\n");
            curr = curr->next;
        }
    }
    printf("\n");
}

int set_destroy(set_t **set) {
    if(set == NULL || *set == NULL) return SET_NULL;

    node_t *curr = (*set)->header;
    while(curr != NULL) {
        node_t *remove = curr;
        curr = curr->next;
        free(remove);
    }

    free(set);

    *set = NULL;

    return SET_OK;
}