/**
 * @file logic.h
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * 
 * @brief Header file containing filtering functions that can be performed on several ADT.
 * like filtering.
 *  
 * @version 0.4
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "../ADTMap/map.h"
#include "../ADTSet/set.h"
#include "../ADTList/list.h"
#include "../Host/host.h"
#include "../Medal/medal.h"
#include "../TopNStats/topnstats.h"

/**
 * @brief Filters a list based on game participations.
 * List includes all athletes with at least 'participations' participations
 * 
 * @param athletes the list of athletes to filter
 * @param participations a number of participations, to filter by
 * @return The filtered list
 */
PtList filterListByParticipations(PtList athletes, int participations);

/**
 * @brief Filters a list based on the first participation's year
 * List include all athletes whose first participation was at 'year' year.
 * 
 * @param athletes the list of athletes to filter
 * @param firstYear the year to filter map
 * @return The filtered list
 */
PtList filterListByFirstYear(PtList athletes, char* firstYear);


/**
 * @brief Retrieves data from hosts, given a specific edition
 * 
 * @param host a map of hosts
 * @param editionName the name of the edition
 * @return An array with the data
 */
char** getHostData(PtMap host, char* editionName);


/**
 * @brief Retrieves data from medals, given a specific edition
 * 
 * @param medals an array of medals
 * @param medalsSize the size of the array
 * @param hosts a map of hosts
 * @param editionName the name of the edition to look for
 * @return A set of distinct disciplines in a single edition, and statistics for each of them
 */
PtSet getDisciplineStatistics(PtMedal medals, int medalsSize, PtMap hosts, char* editionName);

/**
 * @brief Rerieves info about a certain athlete.
 * 
 * @param medals [IN] an array of medals
 * @param medalsSize [IN] the size of the array
 * @param athletes [IN] a list of athletes
 * @param hosts [IN] a map of hosts
 * @param athleteID [IN] the ID of the athlete to search for
 * @param country [OUT] a pointer to an array of characters, to store the country
 * @param participations [OUT] a pointer to an int, to store the participations
 * @param birthYear [OUT] a pointer to an int, to store the birth year
 * @param size [OUT] a pointer to an int, to store the size of the returned array of strings
 * @return an array of strings, containing statistics for each of the medals won
 */
char** getAthleteInfo(PtMedal medals, int medalsSize, PtList athletes, PtMap hosts, char* athleteID, char* country, int* participations, int* birthYear, int* size);

/**
 * @brief Retrieves top countries in a certain criteria
 * 
 * @param medals an array of medals
 * @param medalsSize the size of the array
 * @param hosts a map of hosts
 * @param athletes a list of athletes
 * @param gameSeason the season of the game to be used as a criteria
 * @param startYear the starting year to be used in the year gap criteria
 * @param endYear the ending year to be used in the year gap criteria
 * @param size [OUT] a pointer to an int, to store the size of the returned array
 * 
 * @return An array of the results
 */
PtTopN getTopNCountries(PtMedal medals, int medalsSize, PtMap hosts, PtList athletes, char gameSeason[10], int startYear, int endYear, int* size);



