/**
 * @file disciplinestats.h
 * @author Filipe Paredes (filipeparedes3@gmail.com)
 * 
 * @brief Auxiliary data type to store the statistics of a single discipline
 */

#pragma once

#define MAX_DISCIPLINE_SIZE 30
#define MAX_COUNTRY_SIZE 25

/**
 * @brief Structure representing a host of the games.   
 */
typedef struct disciplineStats {
         
    char disciplineName[MAX_DISCIPLINE_SIZE];
    char topMedalsCountry[MAX_COUNTRY_SIZE];   
    float womenRatio;                      
    
} DisciplineStats;