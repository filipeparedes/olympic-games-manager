/**
 * @file disciplinestats.h
 * @author Filipe Paredes (202300257@estudantes.ips.pt)
 * 
 * @brief Auxiliary data type to store the statistics of a single discipline
 * 
 * @version 0.7
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
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