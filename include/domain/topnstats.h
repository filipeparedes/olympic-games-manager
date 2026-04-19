/**
 * @file disciplinestats.h
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @brief Auxiliary data type to store the statistics of  the athletes
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