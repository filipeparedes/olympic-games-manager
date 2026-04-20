/**
 * @file map_elem.c
 * @brief Implements operations for types map_key_t and map_value_t.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com) - Original Version
 * @author Filipe Paredes (filipeparedes3@gmail.com) - Refactor & Maintenance
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#include "adt/map_elem.h"
#include <stdio.h>
#include <string.h>

void map_key_print(map_key_t key) {
	printf("ID: %s\n", key.text);
}

void map_value_print(map_value_t value) {
	printf("%20d-%d-%d", value.game_end_date.year, value.game_end_date.month, value.game_end_date.day);
	printf("%20d-%d-%d", value.game_start_date.year, value.game_start_date.month, value.game_start_date.day);
	printf("%30s", value.location);
	printf("%30s", value.game_name);
	printf("%12s", value.season);
	printf("%12d\n", value.game_year);
}

int map_key_compare(map_key_t key1, map_key_t key2) {
	return strcmp(key1.text, key2.text);
}