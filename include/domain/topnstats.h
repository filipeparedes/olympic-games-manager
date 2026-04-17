/**
 * @file disciplinestats.h
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * 
 * @brief Auxiliary data type to store the statistics of  the athletes
 * 
 * @version 0.86
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#define MAX_COUNTRY_TOPN_SIZE 30
#define MAX_ATHLETE_ID_TOPN_SIZE 35

typedef struct topNStats TopNStats;
typedef TopNStats* PtTopN;

/**
 * @brief Structure representing a host of the games.   
 */
typedef struct topNStats {
         
    char athleteID[MAX_ATHLETE_ID_TOPN_SIZE];
    char country[MAX_COUNTRY_TOPN_SIZE];   
    int totalMedals;
    int totalDays;
    float avgMedalsEdition;
    float avgMedalsGameDays;                  
    
} TopNStats;