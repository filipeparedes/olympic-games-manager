/**
 * @file top_n_stats.h
 * 
 * @brief Auxiliary data type to store the statistics of  the athletes
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#define MAX_COUNTRY_TOPN_SIZE 30
#define MAX_ATHLETE_ID_TOPN_SIZE 35

/**
 * @brief Structure representing some stats about an athlete.   
 */
typedef struct top_n_stats {
         
    char athlete_id[MAX_ATHLETE_ID_TOPN_SIZE];
    char country[MAX_COUNTRY_TOPN_SIZE];   
    int total_medals;
    int total_days;
    float avg_medals_edition;
    float avg_medals_game_days;                  
    
} top_n_stats_t;