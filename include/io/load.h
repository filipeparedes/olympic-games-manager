/**
 * @file load.h
 * 
 * @brief Imports data from medals, athletes and hosts
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
#define FILE_NOT_FOUND 3
#define ARRAY_NULL 4
#define LOAD_OK 5

#define FILE_LINE_SIZE 200

#include "adt/list.h"
#include "adt/map.h"
#include "domain/medal.h"
#include "io/input.h"
#include "utils/date.h"
#include "utils/string_wrap.h"

/**
 * @brief Loads the medal.csv file into a list
 * 
 * @param array An array to load the file into
 * @param size an address to an integer, where it will store the length of the array
 * 
 * @returns Error code, LOAD_OK if load was successful
 */
int import_medals(medal_t *array, int* size);

/**
 * @brief Loads the athletes.csv file into a list
 * 
 * @param list A list to load the file into
 * @param size an address to an integer, where it will store the size of the list
 * 
 * @return Error code, LOAD_OK if load was successful
 */
int import_athletes(list_t *list, int* size);

/**
 * @brief Reads the hosts.csv file
 * 
 * @return Error code, LOAD_OK if load was successful
 * 
 * @param size an address to an integer, where it will store the size of the map
 * @param map An array to load the file into
 */
int import_hosts(map_t *map, int* size);

/**
 * @brief Counts the lines in a csv file
 * 
 * @param file An address to the file
 * 
 * @returns FILE_NOT_FOUND if file was not found
 * @returns The number of lines in the file
 */
int count_file_lines(FILE* file);