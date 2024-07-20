/**
 * @file host.h
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * @brief Manages and represents host countries. Header file containing type definition for Host and related functions.
 * 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "../Date/date.h"

#define MAX_GAMESLUG_LENGTH 50 
#define MAX_GAME_LOCATION_LENGTH 50
#define MAX_GAME_NAME_LENGTH 50
#define MAX_GAME_SEASON_LENGTH 20

/**
 * @brief Structure representing a host of the games.
 */
typedef struct host {

    char game[MAX_GAMESLUG_LENGTH];           
    Date gameEndDate;
    Date gameStartDate;
    char location[MAX_GAME_LOCATION_LENGTH];
    char gameName[MAX_GAME_NAME_LENGTH];    
    char season[MAX_GAME_SEASON_LENGTH];    
    int gameYear;                         
    
} Host;