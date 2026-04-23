/**
 * @file map_separate_chaining.c
 * 
 * @brief ADT Map implementation with hash tables (separate chaining)
 * 
 * The size of the hash table is fixed and determined at compilation time.
 * This version does not keep track of the current load factor to rehash 
 * the table. This behavior should be implemented in a later version.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com) - Original Version 
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.0.1
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2024 Bruno silva
 * Modifications and Refactor (c) 2026 Filipe Paredes
 * 
 * @bug No known bugs.
 */

#include "adt/map.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

// Useful prime numbers for setting table size:
// 53, 107, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
// 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917,
// 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741

/* Hash table size and hash function multiplier */
#define HASHTABLE_SIZE  53
#define MULTIPLIER  7

//Forward declaration
typedef struct entry entry_t;

/* An entry is a node (of a singly linked list) */
typedef struct entry {
    map_key_t key;
    map_value_t value;    
    entry_t *next;
} entry_t;

/* Hash table consists of pointers to entries (linked lists), initially NULL. */
typedef struct map {
    entry_t *table[HASHTABLE_SIZE];
    int size;
} map_t;

/* Auxiliary functions */
static int byte_hash_function(map_key_t key, int table_size);
static void clear_linked_list(entry_t **addr_entry);
static entry_t *find_node_with_key(entry_t *bucket, map_key_t key);

map_t *map_create() {
    map_t *new_map = (map_t*)calloc(1, sizeof(map_t)); 
    if(new_map == NULL) { return NULL; }
    
    // calloc should set all bits to 0 (zero), hence size = 0 and all
    // buckets start with NULL pointer
    
    return new_map;
}

int map_destroy(map_t **map) {
    map_t *cur_map = *map;
    
    if(cur_map == NULL) { return MAP_NULL; }

    // Free all nodes from linked lists
    for(int i=0; i < HASHTABLE_SIZE; i++) {
        clear_linked_list(&cur_map->table[i]);
    }
    
    free(cur_map);
        
    *map = NULL;
    return MAP_OK;
}

int map_put(map_t *map, map_key_t key, map_value_t new_value) {
    if(map == NULL) { return MAP_NULL; }
    
    int table_index = byte_hash_function(key, HASHTABLE_SIZE);

    entry_t *entry = find_node_with_key(map->table[table_index], key);
    
    if( entry == NULL ) { // new key        
        entry_t *new_entry = (entry_t*)malloc(sizeof(entry_t));
        if(new_entry == NULL) return MAP_NO_MEMORY;

        // Chain the new entry
        new_entry->key = key;
        new_entry->value = new_value;
        new_entry->next = map->table[table_index];

        map->table[table_index] = new_entry;
        
        map->size++;
    } else { // existing key
        entry->value = new_value;
    }
    
    return MAP_OK;
}

int map_get(map_t *map, map_key_t key, map_value_t *value) {
    if(map == NULL) { return MAP_NULL; }
    if(map->size == 0) return MAP_EMPTY;
    
    int table_index = byte_hash_function(key, HASHTABLE_SIZE);

    entry_t *entry = find_node_with_key(map->table[table_index], key);
    
    if(entry == NULL) { return MAP_UNKNOWN_KEY; }
    
    *(value) = entry->value;       
    
    return MAP_OK;   
}

int map_remove(map_t *map, map_key_t key, map_value_t *value) {
    if(map == NULL) { return MAP_NULL; }
    if(map->size == 0) return MAP_EMPTY;
  
    int table_index = byte_hash_function(key, HASHTABLE_SIZE);

    // We traverse the linked list, keeping track of the previous
    // entry, so the linked list structure can be updated later.

    entry_t *entry = map->table[table_index];
    for(entry_t *prev = NULL; entry != NULL; prev = entry, entry = entry->next) {
        if(map_key_compare(key, entry->key) == 0) {
            entry_t *remove = entry;
            *value = remove->value;

            if(prev != NULL) {                
                prev->next = entry->next;                
            } else {
                map->table[table_index] = entry->next;
            }
            
            free(remove);

            map->size--;

            return MAP_OK;
        }
    }

    return MAP_UNKNOWN_KEY;
}

int map_clear(map_t *map) {
    if(map == NULL) { return MAP_NULL; }
   
    for(int i=0; i < HASHTABLE_SIZE; i++) {
        clear_linked_list(&map->table[i]);
    }
    
    map->size = 0;
    
    return MAP_OK;
}


bool map_contains(map_t *map, map_key_t key) {
    if(map == NULL) { return MAP_NULL; }
       
    int table_index = byte_hash_function(key, HASHTABLE_SIZE);

    entry_t *node = find_node_with_key(map->table[table_index] , key);
    
    return (node != NULL);
}

int map_size(map_t *map, int *size) {
    if(map == NULL) { return MAP_NULL; }
    
    (*size) = map->size;
    return MAP_OK;
}

bool map_is_empty(map_t *map) {
    if(map == NULL) { return true; } 
    
    return (map->size == 0);
}

map_key_t *map_keys(map_t *map) {
	if (map == NULL || map->size == 0) return NULL;

	map_key_t *keys = (map_key_t*)calloc(map->size, sizeof(map_key_t));

	int key_arr_index = 0;
	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		entry_t *bucket = map->table[i];
		if (bucket != NULL) {			
			entry_t *current = bucket;
			while (current != NULL) {
				
				keys[key_arr_index++] = current->key;
				current = current->next;
			}
		}
	}

	return keys;
}


map_value_t *map_values(map_t *map) {
	if (map == NULL || map->size == 0) return NULL;

	map_value_t *values = (map_value_t*)calloc(map->size, sizeof(map_value_t));

	int value_arr_index = 0;
	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		entry_t *bucket = map->table[i];
		if (bucket != NULL) {			
			entry_t *current = bucket;
			while (current != NULL) {

				values[value_arr_index++] = current->value;
				current = current->next;
			}
		}
	}

	return values;
}

void map_print(map_t *map) {
	if (map == NULL) {
		printf("(MAP NULL)\n");
	}
	else if (map_is_empty(map)) {
		printf("(MAP EMPTY)\n");
	}
	else {
		printf("MAP CONTENTS: \n");
		/* Traverse all non-empty buckets */
		for (int i = 0; i < HASHTABLE_SIZE; i++) {
			entry_t *bucket = map->table[i];
            if (bucket != NULL) {			
                entry_t *current = bucket;
                while (current != NULL) {
					map_key_print(current->key);
                    printf(":");
					map_value_print(current->value);
                    printf("\n");
					current = current->next;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// AUXILIARY FUNCTIONS

int byte_hash_function(map_key_t key, int table_size) {
    /* convert memory content of 'key' to an int */
    int len_bytes = sizeof(key);
    char *byte = (char*)&key;

    unsigned long hash = 5381;
    int c;

    for(int i=0; i<len_bytes; i++) {
        c = *byte++;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }        

    return (hash * MULTIPLIER) % table_size;
}

void clear_linked_list(entry_t **addr_entry) {
    
    entry_t *current = *addr_entry;

    while(current != NULL) {
        entry_t *aux = current;
        current = current->next;
        free(aux);
    }
    
    *addr_entry = NULL;
}

entry_t *find_node_with_key(entry_t *bucket, map_key_t key) {
    if(bucket == NULL) { return NULL; } //no entries

    entry_t *current = bucket;
    while (current != NULL) {
        if(map_key_compare(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL; // not found
}