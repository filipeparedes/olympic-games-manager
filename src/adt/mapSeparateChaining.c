/**
 * @file mapSeparateChaining.c
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @brief ADT Map implementation with hash tables (separate chaining)
 * @version 1.0
 * @date 2024-06-15
 * 
 * @copyright Copyright (c) 2024
 * 
 * The size of the hash table is fixed and determined at compilation time.
 * This version does not keep track of the current load factor to rehash 
 * the table. This behavior should be implemented in a later version.
 * 
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

/* An entry is a node (of a singly linked list) */
struct entry;
typedef struct entry *PtEntry;

typedef struct entry {
    MapKey key;
    MapValue value;    
    PtEntry next;
} Entry;

/* Hash table consists of pointers to entries (linked lists), initially NULL. */
typedef struct mapImpl {
    PtEntry table[HASHTABLE_SIZE];
    int size;
} HashMap;

/* Auxiliary functions */
static int byteHashFunction(MapKey key, int table_size);
static void clearLinkedList(PtEntry *addrEntry);
static PtEntry findNodeWithKey(PtEntry bucket, MapKey key);

PtMap mapCreate() {
    PtMap newMap = (PtMap) calloc(1, sizeof(HashMap) ); 
    if( newMap == NULL ) { return NULL; }
    
    // calloc should set all bits to 0 (zero), hence size = 0 and all
    // buckets start with NULL pointer
    
    return newMap;
}

int mapDestroy(PtMap *ptMap) {
    PtMap curMap = *ptMap;
    
    if( curMap == NULL ) { return MAP_NULL; }

    // Free all nodes from linked lists
    for(int i=0; i < HASHTABLE_SIZE; i++) {
        clearLinkedList(&curMap->table[i]);
    }
    
    free(curMap);
        
    *ptMap = NULL;
    return MAP_OK;
}

int mapPut(PtMap map, MapKey key, MapValue newValue) {
    if(map == NULL) { return MAP_NULL; }
    
    int tableIndex = byteHashFunction(key, HASHTABLE_SIZE);

    PtEntry entry = findNodeWithKey( map->table[ tableIndex ], key );
    
    if( entry == NULL ) { // new key        
        PtEntry newEntry = (PtEntry)malloc(sizeof(Entry));
        if(newEntry == NULL) return MAP_NO_MEMORY;

        // Chain the new entry
        newEntry->key = key;
        newEntry->value = newValue;
        newEntry->next = map->table[ tableIndex ];

        map->table[ tableIndex ] = newEntry;
        
        map->size++;
    } else { // existing key
        entry->value = newValue;
    }
    
    return MAP_OK;
}

int mapGet(PtMap map, MapKey key, MapValue *ptValue) {
    if(map == NULL) { return MAP_NULL; }
    if(map->size == 0) return MAP_EMPTY;
    
    int tableIndex = byteHashFunction(key, HASHTABLE_SIZE);

    PtEntry entry = findNodeWithKey( map->table[ tableIndex ], key );
    
    if( entry == NULL ) { return MAP_UNKNOWN_KEY; }
    
    *(ptValue) = entry->value;       
    
    return MAP_OK;   
}

int mapRemove(PtMap map, MapKey key, MapValue *ptValue) {
    if(map == NULL) { return MAP_NULL; }
    if(map->size == 0) return MAP_EMPTY;
  
    int tableIndex = byteHashFunction(key, HASHTABLE_SIZE);

    // We traverse the linked list, keeping track of the previous
    // entry, so the linked list structure can be updated later.

    PtEntry entry = map->table[ tableIndex ];
    for(PtEntry prev = NULL; entry != NULL; prev = entry, entry = entry->next) {
        if( mapKeyCompare(key, entry->key) == 0) {
            PtEntry remove = entry;
            *ptValue = remove->value;

            if(prev != NULL) {                
                prev->next = entry->next;                
            } else {
                map->table[ tableIndex ] = entry->next;
            }
            
            free(remove);

            map->size--;

            return MAP_OK;
        }
    }

    return MAP_UNKNOWN_KEY;
}

int mapClear(PtMap map) {
    if( map == NULL ) { return MAP_NULL; }
   
    for(int i=0; i < HASHTABLE_SIZE; i++) {
        clearLinkedList( &map->table[i] );
    }
    
    map->size = 0;
    
    return MAP_OK;
}


bool mapContains(PtMap map, MapKey key) {
    if(map == NULL) { return MAP_NULL; }
       
    int tableIndex = byteHashFunction(key, HASHTABLE_SIZE);

    PtEntry node = findNodeWithKey( map->table[ tableIndex ], key );
    
    return ( node != NULL );
}

int mapSize(PtMap map, int *ptSize) {
    if(map == NULL) { return MAP_NULL; }
    
    (*ptSize) = map->size;
    return MAP_OK;
}

bool mapIsEmpty(PtMap map) {
    if(map == NULL) { return true; } 
    
    return (map->size == 0);
}

MapKey* mapKeys(PtMap map) {
	if (map == NULL || map->size == 0) return NULL;

	MapKey *keys = (MapKey*)calloc(map->size, sizeof(MapKey));

	int keyArrIndex = 0;
	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		PtEntry bucket = map->table[i];
		if (bucket != NULL) {			
			PtEntry current = bucket;
			while (current != NULL) {
				
				keys[keyArrIndex++] = current->key;
				current = current->next;
			}
		}
	}

	return keys;
}


MapValue* mapValues(PtMap map) {
	if (map == NULL || map->size == 0) return NULL;

	MapValue *values = (MapValue*)calloc(map->size, sizeof(MapValue));

	int valueArrIndex = 0;
	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		PtEntry bucket = map->table[i];
		if (bucket != NULL) {			
			PtEntry current = bucket;
			while (current != NULL) {

				values[valueArrIndex++] = current->value;
				current = current->next;
			}
		}
	}

	return values;
}

void mapPrint(PtMap map) {
	if (map == NULL) {
		printf("(MAP NULL)\n");
	}
	else if (mapIsEmpty(map)) {
		printf("(MAP EMPTY)\n");
	}
	else {
		printf("MAP CONTENTS: \n");
		/* Traverse all non-empty buckets */
		for (int i = 0; i < HASHTABLE_SIZE; i++) {
			PtEntry bucket = map->table[i];
            if (bucket != NULL) {			
                PtEntry current = bucket;
                while (current != NULL) {
					mapKeyPrint(current->key);
                    printf(":");
					mapValuePrint(current->value);
                    printf("\n");
					current = current->next;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// AUXILIARY FUNCTIONS

int byteHashFunction(MapKey key, int table_size) {
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

void clearLinkedList(PtEntry *addrEntry) {
    
    PtEntry current = *addrEntry;

    while(current != NULL) {
        PtEntry aux = current;
        current = current->next;
        free(aux);
    }
    
    *addrEntry = NULL;
}

PtEntry findNodeWithKey(PtEntry bucket, MapKey key) {
    if( bucket == NULL ) { return NULL; } //no entries

    PtEntry current = bucket;
    while (current != NULL) {
        if( mapKeyCompare(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL; // not found
}