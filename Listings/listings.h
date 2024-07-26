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
#include "../ADTSet/set.h"
#include "../ADTList/list.h"

/**
 * @brief Displays all athlete information in the list.
 * 
 * This function prints information of all athletes stored in the list. Information is sorted by athlete name.
 * 
 * @param athletes Pointer to the list of athletes.
 */
void paginate(PtList athletes);

/**
 * @brief Displays a set of statistics about a certain edition.
 * 
 * @param statistics a set of statistics
 */
void paginateSet(PtSet statistics); 

/**
 * @brief Displays the data of a specific host
 * 
 * @param hostData an array of strings, containing the data
 */
void printHostDetails(char** hostData);

/**
 * @brief Sorts the athletes list in alphabetical order based on the athlete's name.
 * 
 * @param athletes Pointer to the list of athletes.
 * 
 * @returns A list of the sorted Map Values.
 */
PtList sortList(PtList athletes);


/**
 * @brief 
 * 
 * @param medalsStatistics 
 * @param medalsStatsSize 
 * @param country 
 * @param athleteID 
 * @param participations 
 * @param birthYear 
 */
void printAthleteInfo(char** medalsStatistics, int medalsStatsSize, char* country, char* athleteID, int participations, int birthYear);
