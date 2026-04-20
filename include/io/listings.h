/**
 * @file listings.h
 *
 * @brief Provides various listing functions for different ADTs.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#define LISTINGS_PAGE_SIZE 20

#include "adt/map.h"
#include "adt/map_elem.h"
#include "adt/set.h"
#include "adt/list.h"
#include "domain/top_n_stats.h"

/**
 * @brief Displays all athlete information in the list.
 * 
 * This function prints information of all athletes stored in the list. 
 * Information is sorted by athlete name.
 * 
 * @param athletes Pointer to the list of athletes.
 */
void paginate(list_t *athletes);

/**
 * @brief Displays a set of statistics about a certain edition.
 * 
 * @param statistics a set of statistics
 */
void paginate_set(set_t *statistics); 

/**
 * @brief Displays the data of a specific host
 * 
 * @param host_data an array of strings, containing the data
 */
void print_host_details(char **host_data);

/**
 * @brief Sorts the athletes list in alphabetical order based on the athlete's name.
 * 
 * @param athletes Pointer to the list of athletes.
 * 
 * @returns A list of the sorted Map Values.
 */
list_t *sort_list(list_t *athletes);


/**
 * @brief  Prints the athlete info.
 * 
 * @param medals_statistics medals statistics array of strings
 * @param medals_stats_size the size of the array of strings
 * @param country the country of the athlete
 * @param athlete_id the id of the athlete
 * @param participations the number of participations
 * @param birth_year the athlete's birth year.
 */
void print_athlete_info(char **medals_statistics, int medals_stats_size, char *country, char *athlete_id, int participations, int birth_year);


/**
 * @brief Prints a top_n array.
 * 
 * @param top_n_list topN array to print
 * @param n the number of results to print
 * @param top_n_size the size of the array
 * 
 */
void print_top_n(top_n_stats_t *top_n_list, int top_n_size, int n);


/**
 * @brief Sorts a top_n array by total_medals in descending order, 
 * and by country name in case of tie
 * 
 * @param top_n_list the array to sort
 * @param top_n_size the size of the array
 * @return the sorted array
 */
top_n_stats_t *sort_top_n(top_n_stats_t *topNList, int topNSize);
