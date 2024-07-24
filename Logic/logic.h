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



