/**
 * @file listings.h
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Provides various listing functions for different ADTs.
 * @version 0.4
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#define LISTINGS_PAGE_SIZE 20

#include "../ADTMap/map.h"
#include "../ADTMap/mapElem.h"

/**
 * @brief Displays all athlete information in the map.
 * 
 * This function prints information of all athletes stored in the map. Information is sorted by athlete name.
 * 
 * @param athletes Pointer to the map of athletes.
 */
void paginate(PtMap athletes);

/**
 * @brief Displays the data of a specific host
 * 
 * @param hostData an array of strings, containing the data
 */
void printHostDetails(char** hostData);

/**
 * @brief Sorts the values in the map in alphabetical order based on the athlete's name.
 * 
 * @param athletes Pointer to the map of athletes.
 * 
 * @returns An array of the sorted Map Values.
 */
MapValue* sortMapValues(PtMap athletes);

