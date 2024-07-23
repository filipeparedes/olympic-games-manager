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

/**
 * @brief Filters a map based on game participations.
 * Map includes all athletes with at least 'participations' participations
 * 
 * @param map the map of athletes to filter
 * @param participations a number of participations, to filter by
 * @return The filtered map
 */
PtMap filterMapByParticipations(PtMap athletes, int participations);

/**
 * @brief Filters a map based on the first participation's year
 * Map include all athletes whose first participation was at 'year' year.
 * 
 * @param athletes the map of athletes to filter
 * @param firstYear the year to filter map
 * @return The filtered map
 */
PtMap filterMapByFirstYear(PtMap athletes, char* firstYear);
