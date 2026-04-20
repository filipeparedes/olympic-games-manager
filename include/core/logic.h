/**
 * @file logic.h
 * 
 * @brief Header file containing filtering functions that can be performed on several ADT.
 * like filtering.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.1.1
 * @date 2026-04-21
 * 
 * @bug No known bugs.
 */

#pragma once

#include "adt/map.h"
#include "adt/set.h"
#include "adt/list.h"
#include "domain/host.h"
#include "domain/medal.h"
#include "domain/top_n_stats.h"

/**
 * @brief Filters a list based on game participations.
 * List includes all athletes with at least 'participations' participations
 * 
 * @param athletes the list of athletes to filter
 * @param participations a number of participations, to filter by
 * @return The filtered list
 */
list_t *filter_list_by_participations(list_t *athletes, int participations);

/**
 * @brief Filters a list based on the first participation's year
 * List include all athletes whose first participation was at 'year' year.
 * 
 * @param athletes the list of athletes to filter
 * @param first_year the year to filter map
 * @return The filtered list
 */
list_t *filter_list_by_first_year(list_t *athletes, char *first_year);


/**
 * @brief Retrieves data from hosts, given a specific edition
 * 
 * @param host a map of hosts
 * @param edition_name the name of the edition
 * @return An array with the data
 */
char **get_host_data(map_t *host, char *edition_name);


/**
 * @brief Retrieves data from medals, given a specific edition
 * 
 * @param medals an array of medals
 * @param medals_size the size of the array
 * @param hosts a map of hosts
 * @param edition_name the name of the edition to look for
 * @return A set of distinct disciplines in a single edition, and statistics for each of them
 */
set_t *get_discipline_statistics(medal_t *medals, int medals_size, map_t *hosts, char *edition_name);

/**
 * @brief Rerieves info about a certain athlete.
 * 
 * @param medals [IN] an array of medals
 * @param medals_size [IN] the size of the array
 * @param athletes [IN] a list of athletes
 * @param hosts [IN] a map of hosts
 * @param athlete_id [IN] the ID of the athlete to search for
 * @param country [OUT] a pointer to an array of characters, to store the country
 * @param participations [OUT] a pointer to an int, to store the participations
 * @param birth_year [OUT] a pointer to an int, to store the birth year
 * @param size [OUT] a pointer to an int, to store the size of the returned array of strings
 * @return an array of strings, containing statistics for each of the medals won
 */
char **get_athlete_info(medal_t *medals, int medals_size, list_t *athletes, map_t *hosts, char *athlete_id, char *country, int *participations, int *birth_year, int *size);

/**
 * @brief Retrieves top countries in a certain criteria
 * 
 * @param medals an array of medals
 * @param medals_size the size of the array
 * @param hosts a map of hosts
 * @param athletes a list of athletes
 * @param game_season the season of the game to be used as a criteria
 * @param start_year the starting year to be used in the year gap criteria
 * @param end_year the ending year to be used in the year gap criteria
 * @param size [OUT] a pointer to an int, to store the size of the returned array
 * 
 * @return An array of the results
 */
top_n_stats_t *get_top_n_countries(medal_t *medals, int medals_size, map_t *hosts, list_t *athletes, char game_season[10], int start_year, int end_year, int *size);

/**
 * @brief Shows all medals won by a country from a given year onwards in a given season.
 *
 * Iterates over the medals array and prints each medal where the country matches,
 * the game season matches, and the game year is >= start_year.
 *
 * @param medals      Array of medals
 * @param medals_size Number of medals in the array
 * @param hosts       Map of hosts (used to resolve game year and season)
 * @param country     Country name to filter by
 * @param start_year  Minimum year (inclusive)
 * @param season      Season to filter by ("Summer" or "Winter")
 */
void get_medals_won(medal_t *medals, int medals_size, map_t *hosts, char *country, int start_year, char *season);

