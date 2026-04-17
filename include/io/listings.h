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
#include "../TopNStats/topnstats.h"

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
 * @brief  Prints the athlete info.
 * 
 * @param medalsStatistics medals statistics array of strings
 * @param medalsStatsSize the size of the array of strings
 * @param country the country of the athlete
 * @param athleteID the id of the athlete
 * @param participations the number of participations
 * @param birthYear the athlete's birth year.
 */
void printAthleteInfo(char** medalsStatistics, int medalsStatsSize, char* country, char* athleteID, int participations, int birthYear);


/**
 * @brief Prints a TopN array.
 * 
 * @param topNList topN array to print
 * @param n the number of results to print
 * @param topNSize the size of the array
 * 
 */
void printTopN(PtTopN topNList, int topNSize, int n);


/**
 * @brief Sorts a topN array by totalMedals in descending order, and by country name in case of tie
 * 
 * @param topNList the array to sort
 * @param topNSize the size of the array
 * @return the sorted array
 */
PtTopN sortTopN(PtTopN topNList, int topNSize);
