/**
 * @file discipline_stats.h
 * 
 * @brief Auxiliary data type to store the statistics of a single discipline
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#define MAX_DISCIPLINE_SIZE 30
#define MAX_COUNTRY_SIZE 25

/**
 * @brief Structure representing a host of the games.   
 */
typedef struct discipline_stats {
         
    char discipline_name[MAX_DISCIPLINE_SIZE];
    char top_medals_country[MAX_COUNTRY_SIZE];   
    float women_tatio;                      
    
} discipline_stats_t;