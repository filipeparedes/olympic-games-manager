/**
 * @file host.h
 * 
 * @brief Manages and represents host countries. 
 * Header file containing type definition for Host and related functions.
 * 
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @version 2.0.0
 * @date 2026-04-20
 * 
 * @bug No known bugs.
 */

#pragma once

#include "utils/date.h"

#define MAX_GAME_LOCATION_LENGTH 50
#define MAX_GAME_NAME_LENGTH 50
#define MAX_GAME_SEASON_LENGTH 20

/**
 * @brief Structure representing a host of the games.
 */
typedef struct host {
         
    date_t game_end_date;
    date_t game_start_date;
    char location[MAX_GAME_LOCATION_LENGTH];
    char game_name[MAX_GAME_NAME_LENGTH];    
    char season[MAX_GAME_SEASON_LENGTH];    
    int game_year;                         
    
} host_t;